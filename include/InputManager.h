#pragma once
#include <Arduino.h>

enum KeyEvent : uint8_t {
  KEY_NONE  = 0,
  KEY_UP    = 1 << 0,
  KEY_DOWN  = 1 << 1,
  KEY_LEFT  = 1 << 2,
  KEY_RIGHT = 1 << 3,
  KEY_OK    = 1 << 4
};

class InputManager {
public:
  void begin();
  uint8_t poll();

private:
  struct Button {
    uint8_t pin;
    uint8_t mask;
    bool stableHigh;
    bool rawHigh;
    uint32_t changedAt;
    uint32_t pressedAt;
    uint32_t repeatedAt;
    bool longPressSent;
  };

  static constexpr uint32_t DEBOUNCE_MS = 25;
  static constexpr uint32_t REPEAT_START_MS = 450;
  static constexpr uint32_t REPEAT_INTERVAL_MS = 130;
  Button buttons_[5] = {};
};
