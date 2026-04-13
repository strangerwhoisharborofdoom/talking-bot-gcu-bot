#include <Arduino.h>
#include <driver/i2s.h>

void setup() {
  Serial.begin(115200);
  i2s_config_t cfg = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
      .sample_rate = 16000,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = false,
      .fixed_mclk = 0
  };
  i2s_pin_config_t pin = {.bck_io_num = 32, .ws_io_num = 33, .data_out_num = I2S_PIN_NO_CHANGE, .data_in_num = 35};
  i2s_driver_install(I2S_NUM_0, &cfg, 0, nullptr);
  i2s_set_pin(I2S_NUM_0, &pin);
}

void loop() {
  uint8_t buf[512];
  size_t n = 0;
  i2s_read(I2S_NUM_0, buf, sizeof(buf), &n, 100 / portTICK_PERIOD_MS);
  Serial.printf("Mic bytes: %u\n", (unsigned)n);
}
