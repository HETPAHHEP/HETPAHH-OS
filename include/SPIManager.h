#pragma once
#include <Arduino.h>
#include <SPI.h>
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"

class SPIManager {
public:
  bool begin(int sck, int miso, int mosi);
  bool lock(TickType_t timeout = portMAX_DELAY);
  void unlock();
  SPIClass& bus();

private:
  SPIClass* spi_ = nullptr;
  SemaphoreHandle_t mutex_ = nullptr;
};
