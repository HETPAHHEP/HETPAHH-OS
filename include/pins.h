#pragma once
#include <Arduino.h>

// PROVISIONAL PIN MAP ONLY.
// Verify the exact ESP32 board, TFT breakout and radio modules before wiring.
// Do not connect the Li-Po cell directly to an ESP32 GPIO.

namespace Pins {
  constexpr int SPI_SCK  = 18;
  constexpr int SPI_MISO = 19;
  constexpr int SPI_MOSI = 23;

  constexpr int TFT_CS  = 13;
  constexpr int TFT_DC  = 26;
  constexpr int TFT_RST = 4;

  constexpr int NRF_CE  = 17;
  constexpr int NRF_CSN = 16;

  constexpr int CC_CS   = 27;
  constexpr int CC_GDO0 = 34;
  constexpr int CC_GDO2 = 35;

  constexpr int BTN_UP    = 32;
  constexpr int BTN_DOWN  = 33;
  constexpr int BTN_LEFT  = 25;
  constexpr int BTN_RIGHT = 22;
  constexpr int BTN_OK    = 21;

  // Disabled until a verified battery divider/protection/charger design exists.
  constexpr int BATTERY_ADC = 39;
}
