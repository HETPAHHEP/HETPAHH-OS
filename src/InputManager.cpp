#include "InputManager.h"
#include "pins.h"

void InputManager::begin() {
  const uint8_t pins[5] = {
    (uint8_t)Pins::BTN_UP, (uint8_t)Pins::BTN_DOWN,
    (uint8_t)Pins::BTN_LEFT, (uint8_t)Pins::BTN_RIGHT,
    (uint8_t)Pins::BTN_OK
  };
  const uint8_t masks[5] = {
    KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_OK
  };

  const uint32_t now = millis();
  for (int i = 0; i < 5; ++i) {
    buttons_[i].pin = pins[i];
    buttons_[i].mask = masks[i];
    pinMode(pins[i], INPUT_PULLUP);
    const bool level = digitalRead(pins[i]);
    buttons_[i].stableHigh = level;
    buttons_[i].rawHigh = level;
    buttons_[i].changedAt = now;
    buttons_[i].pressedAt = 0;
    buttons_[i].repeatedAt = 0;
    buttons_[i].longPressSent = false;
  }
}

uint8_t InputManager::poll() {
  uint8_t events = KEY_NONE;
  const uint32_t now = millis();

  for (auto &b : buttons_) {
    const bool raw = digitalRead(b.pin);

    if (raw != b.rawHigh) {
      b.rawHigh = raw;
      b.changedAt = now;
    }

    if (raw != b.stableHigh && now - b.changedAt >= DEBOUNCE_MS) {
      b.stableHigh = raw;

      if (!raw) {
        events |= b.mask;               // one event on press
        b.pressedAt = now;
        b.repeatedAt = now;
        b.longPressSent = false;
      } else {
        b.pressedAt = 0;
        b.longPressSent = false;
      }
    }

    // Repeat only navigation keys; OK is deliberately non-repeating.
    if (!b.stableHigh && (b.mask == KEY_UP || b.mask == KEY_DOWN)) {
      if (now - b.pressedAt >= REPEAT_START_MS &&
          now - b.repeatedAt >= REPEAT_INTERVAL_MS) {
        events |= b.mask;
        b.repeatedAt = now;
      }
    }
  }
  return events;
}
