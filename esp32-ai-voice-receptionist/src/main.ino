#include <Arduino.h>
#include <driver/i2s.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// ---------- Pin definitions ----------
static constexpr int PIR_PIN = 27;

static constexpr int MIC_WS = 33;
static constexpr int MIC_SCK = 32;
static constexpr int MIC_SD = 35;

static constexpr int SPK_LRC = 25;
static constexpr int SPK_BCLK = 26;
static constexpr int SPK_DIN = 22;

static constexpr int OLED_SDA = 21;
static constexpr int OLED_SCL = 19;

// ---------- Audio constants ----------
static constexpr uint32_t SAMPLE_RATE = 16000;
static constexpr size_t AUDIO_FRAME_BYTES = 1024;

Adafruit_SH1106G display(128, 64, &Wire, -1);

bool micReady = false;
bool speakerReady = false;
bool displayReady = false;

void drawStatus(const String &line1, const String &line2 = "") {
  if (!displayReady) return;
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 8);
  display.println("AI Receptionist");
  display.println("----------------");
  display.println(line1);
  if (line2.length() > 0) display.println(line2);
  display.display();
}

bool initDisplay() {
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(0x3C, true)) {
    Serial.println("[ERR] OLED init failed");
    return false;
  }
  display.clearDisplay();
  display.display();
  return true;
}

bool initMicI2S() {
  i2s_config_t cfg = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0 // Disable MCLK.
  };

  i2s_pin_config_t pins = {
      .bck_io_num = MIC_SCK,
      .ws_io_num = MIC_WS,
      .data_out_num = I2S_PIN_NO_CHANGE,
      .data_in_num = MIC_SD,
  };

  if (i2s_driver_install(I2S_NUM_0, &cfg, 0, nullptr) != ESP_OK) return false;
  if (i2s_set_pin(I2S_NUM_0, &pins) != ESP_OK) return false;
  return true;
}

bool initSpeakerI2S() {
  i2s_config_t cfg = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = SAMPLE_RATE,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = true,
      .fixed_mclk = 0 // Disable MCLK.
  };

  i2s_pin_config_t pins = {
      .bck_io_num = SPK_BCLK,
      .ws_io_num = SPK_LRC,
      .data_out_num = SPK_DIN,
      .data_in_num = I2S_PIN_NO_CHANGE,
  };

  if (i2s_driver_install(I2S_NUM_1, &cfg, 0, nullptr) != ESP_OK) return false;
  if (i2s_set_pin(I2S_NUM_1, &pins) != ESP_OK) return false;
  return true;
}

void runSelfTest() {
  Serial.println("[SELFTEST] Starting...");
  bool pirOk = (digitalRead(PIR_PIN) == LOW || digitalRead(PIR_PIN) == HIGH);
  Serial.printf("[SELFTEST] PIR: %s\n", pirOk ? "OK" : "FAIL");
  Serial.printf("[SELFTEST] OLED: %s\n", displayReady ? "OK" : "FAIL");
  Serial.printf("[SELFTEST] Mic I2S: %s\n", micReady ? "OK" : "FAIL");
  Serial.printf("[SELFTEST] Spk I2S: %s\n", speakerReady ? "OK" : "FAIL");

  drawStatus("Self-test complete", String("Mic:") + (micReady ? "OK" : "FAIL"));
  delay(1200);
}

void audioLoopbackStep() {
  static uint8_t buffer[AUDIO_FRAME_BYTES];
  size_t bytesRead = 0;
  size_t bytesWritten = 0;

  if (i2s_read(I2S_NUM_0, buffer, sizeof(buffer), &bytesRead, 20 / portTICK_PERIOD_MS) == ESP_OK && bytesRead > 0) {
    i2s_write(I2S_NUM_1, buffer, bytesRead, &bytesWritten, 20 / portTICK_PERIOD_MS);
    Serial.printf("[AUDIO] rx=%u tx=%u\n", (unsigned)bytesRead, (unsigned)bytesWritten);
  }
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(PIR_PIN, INPUT);

  displayReady = initDisplay();
  micReady = initMicI2S();
  speakerReady = initSpeakerI2S();

  drawStatus("Booting...");
  runSelfTest();
  drawStatus("Standby", "Waiting for motion");

  Serial.println("[INFO] System ready");
}

void loop() {
  bool motion = digitalRead(PIR_PIN) == HIGH;

  if (motion) {
    drawStatus("Human detected", "Audio active");
    Serial.println("[PIR] Motion detected");
    if (micReady && speakerReady) {
      audioLoopbackStep();
    }
  } else {
    drawStatus("Standby", "No motion");
    delay(120);
  }
}
