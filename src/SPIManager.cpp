#include "SPIManager.h"

bool SPIManager::begin(int sck, int miso, int mosi) {
  if (!mutex_) mutex_ = xSemaphoreCreateMutex();
  if (!mutex_) return false;

  // ESP32 Arduino default VSPI bus. TFT_eSPI also uses global SPI on this target.
  spi_ = &SPI;
  spi_->begin(sck, miso, mosi);
  return true;
}

bool SPIManager::lock(TickType_t timeout) {
  return mutex_ && xSemaphoreTake(mutex_, timeout) == pdTRUE;
}

void SPIManager::unlock() {
  if (mutex_) xSemaphoreGive(mutex_);
}

SPIClass& SPIManager::bus() {
  return *spi_;
}
