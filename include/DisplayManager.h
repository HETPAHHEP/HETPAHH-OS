#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

class DisplayManager {
public:
  void begin();
  void bootScreen();
  void drawMenu(const char* const* labels, uint8_t count, uint8_t selected);
  void drawInfo(const char* title, const char* const* lines, uint8_t lineCount);
  void drawMessage(const char* title, const char* message);

private:
  TFT_eSPI tft_;
  void header(const char* title);
};
