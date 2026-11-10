#include "DisplayManager.h"

void DisplayManager::begin() {
  tft_.init();
  tft_.setRotation(0); // portrait: 240x320
  tft_.fillScreen(TFT_BLACK);
}

void DisplayManager::header(const char* title) {
  tft_.fillScreen(TFT_BLACK);
  tft_.fillRect(0, 0, 240, 34, TFT_DARKCYAN);
  tft_.setTextColor(TFT_WHITE, TFT_DARKCYAN);
  tft_.drawString("HETPAHH OS", 8, 7, 2);
  tft_.setTextColor(TFT_CYAN, TFT_BLACK);
  tft_.drawString(title, 8, 43, 2);
  tft_.drawFastHLine(8, 65, 224, TFT_DARKGREY);
}

void DisplayManager::bootScreen() {
  tft_.fillScreen(TFT_BLACK);
  tft_.setTextColor(TFT_CYAN, TFT_BLACK);
  tft_.drawCentreString("HETPAHH OS", 120, 105, 4);
  tft_.setTextColor(TFT_WHITE, TFT_BLACK);
  tft_.drawCentreString("CORE v0.5", 120, 150, 2);
  tft_.drawCentreString("INITIALIZING", 120, 178, 2);
  tft_.drawRoundRect(20, 215, 200, 12, 3, TFT_DARKGREY);
  for (int x = 0; x < 196; x += 4) {
    tft_.fillRect(22, 217, x, 8, TFT_CYAN);
    delay(8);
  }
}

void DisplayManager::drawMenu(const char* const* labels, uint8_t count, uint8_t selected) {
  header("SYSTEM MENU");
  const uint8_t visible = 7;
  uint8_t first = 0;
  if (selected >= visible) first = selected - visible + 1;

  for (uint8_t row = 0; row < visible && first + row < count; ++row) {
    const uint8_t idx = first + row;
    const int y = 75 + row * 29;
    const bool active = idx == selected;
    if (active) tft_.fillRoundRect(7, y - 2, 226, 25, 4, TFT_DARKCYAN);
    tft_.setTextColor(active ? TFT_WHITE : TFT_LIGHTGREY,
                      active ? TFT_DARKCYAN : TFT_BLACK);
    tft_.drawString(labels[idx], 14, y, 2);
  }
  tft_.setTextColor(TFT_DARKGREY, TFT_BLACK);
  tft_.drawString("UP/DOWN: MOVE", 8, 294, 1);
  tft_.drawString("OK: OPEN", 158, 294, 1);
}

void DisplayManager::drawInfo(const char* title, const char* const* lines, uint8_t lineCount) {
  header(title);
  tft_.setTextColor(TFT_WHITE, TFT_BLACK);
  for (uint8_t i = 0; i < lineCount; ++i) {
    tft_.drawString(lines[i], 10, 84 + i * 31, 2);
  }
  tft_.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft_.drawString("LEFT: BACK", 10, 285, 2);
}

void DisplayManager::drawMessage(const char* title, const char* message) {
  const char* lines[] = { message };
  drawInfo(title, lines, 1);
}
