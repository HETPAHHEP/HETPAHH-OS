#include "SettingsManager.h"
#include <Preferences.h>

static Preferences prefs;

bool SettingsManager::begin() {
  if (!prefs.begin("hetpanh", false)) return false;
  brightness_ = prefs.getUChar("brightness", 100);
  lastMenuIndex_ = prefs.getUChar("menu_idx", 0);
  if (brightness_ > 100) brightness_ = 100;
  return true;
}

bool SettingsManager::setBrightness(uint8_t value) {
  if (value > 100) return false;
  brightness_ = value;
  return prefs.putUChar("brightness", brightness_) > 0;
}

bool SettingsManager::setLastMenuIndex(uint8_t value) {
  lastMenuIndex_ = value;
  return prefs.putUChar("menu_idx", lastMenuIndex_) > 0;
}
