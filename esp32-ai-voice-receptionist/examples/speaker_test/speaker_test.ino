#include <Arduino.h>
#include <driver/i2s.h>

void setup() {
  Serial.begin(115200);
  i2s_config_t cfg = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = 16000,
      .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
      .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
      .communication_format = I2S_COMM_FORMAT_STAND_I2S,
      .intr_alloc_flags = 0,
      .dma_buf_count = 4,
      .dma_buf_len = 256,
      .use_apll = false,
      .tx_desc_auto_clear = true,
      .fixed_mclk = 0
  };
  i2s_pin_config_t pin = {.bck_io_num = 26, .ws_io_num = 25, .data_out_num = 22, .data_in_num = I2S_PIN_NO_CHANGE};
  i2s_driver_install(I2S_NUM_1, &cfg, 0, nullptr);
  i2s_set_pin(I2S_NUM_1, &pin);
}

void loop() {
  static int16_t frame[256];
  for (int i = 0; i < 256; ++i) frame[i] = ((i % 64) < 32) ? 2000 : -2000;
  size_t written = 0;
  i2s_write(I2S_NUM_1, frame, sizeof(frame), &written, 100 / portTICK_PERIOD_MS);
  Serial.printf("Wrote: %u\n", (unsigned)written);
  delay(20);
}
