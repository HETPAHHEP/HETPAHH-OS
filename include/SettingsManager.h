#pragma once
#include <Arduino.h>

class SettingsManager {
public:
  bool begin();
  uint8_t getBrightness() const { return brightness_; }
  bool setBrightness(uint8_t value);
  uint8_t getLastMenuIndex() const { return lastMenuIndex_; }
  bool setLastMenuIndex(uint8_t value);

private:
  uint8_t brightness_ = 100; // logical setting; backlight PWM not wired yet
  uint8_t lastMenuIndex_ = 0;
};
