#pragma once
#include <Arduino.h>

// Battery ADC is intentionally disabled until the exact charger/protection
// board and resistor-divider values are selected and verified.
class PowerManager {
public:
  void begin() {}
  bool isMeasurementConfigured() const { return false; }
  float voltage() const { return NAN; }
  int percentage() const { return -1; }
};
