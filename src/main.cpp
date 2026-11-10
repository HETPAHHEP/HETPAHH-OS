#include <Arduino.h>
#include "pins.h"
#include "SPIManager.h"
#include "InputManager.h"
#include "DisplayManager.h"
#include "SettingsManager.h"
#include "PowerManager.h"

enum class Page : uint8_t {
  MENU, WIFI, BLE, NRF24, CC1101, SIGNAL, POWER, SETTINGS
};

static const char* const menuLabels[] = {
  "Wi-Fi Analyzer",
  "Bluetooth / BLE",
  "NRF24 Analyzer",
  "CC1101 433 MHz",
  "Signal Monitor",
  "Power Manager",
  "Settings"
};
static constexpr uint8_t MENU_COUNT = sizeof(menuLabels) / sizeof(menuLabels[0]);

SPIManager spiManager;
InputManager input;
DisplayManager display;
SettingsManager settings;
PowerManager power;

Page page = Page::MENU;
uint8_t selected = 0;

void render() {
  if (page == Page::MENU) {
    display.drawMenu(menuLabels, MENU_COUNT, selected);
    return;
  }

  switch (page) {
    case Page::WIFI: {
      const char* lines[] = {"Passive AP discovery", "Status: driver pending", "No scan started"};
      display.drawInfo("WI-FI ANALYZER", lines, 3); break;
    }
    case Page::BLE: {
      const char* lines[] = {"BLE advertisements", "Status: driver pending", "No scan started"};
      display.drawInfo("BLE ANALYZER", lines, 3); break;
    }
    case Page::NRF24: {
      const char* lines[] = {"2.4 GHz channel activity", "Status: driver pending", "RX monitor: inactive"};
      display.drawInfo("NRF24 ANALYZER", lines, 3); break;
    }
    case Page::CC1101: {
      const char* lines[] = {"433 MHz receive monitor", "Status: driver pending", "RSSI: unavailable"};
      display.drawInfo("CC1101 ANALYZER", lines, 3); break;
    }
    case Page::SIGNAL: {
      const char* lines[] = {"Passive signal observation", "No transmission functions", "Driver: pending"};
      display.drawInfo("SIGNAL MONITOR", lines, 3); break;
    }
    case Page::POWER: {
      const char* lines[] = {"Li-Po: 3.7 V nominal", "ADC measurement disabled", "Hardware design: pending"};
      display.drawInfo("POWER MANAGER", lines, 3); break;
    }
    case Page::SETTINGS: {
      char line[32];
      snprintf(line, sizeof(line), "Brightness setting: %u%%", settings.getBrightness());
      const char* lines[] = {"NVS storage: initialized", line, "Backlight PWM: not mapped"};
      display.drawInfo("SETTINGS", lines, 3); break;
    }
    case Page::MENU: break;
  }
}

void setup() {
  Serial.begin(115200);

  // Initialize the shared bus before TFT_eSPI. No radio devices are activated yet.
  if (!spiManager.begin(Pins::SPI_SCK, Pins::SPI_MISO, Pins::SPI_MOSI)) {
    Serial.println("ERROR: SPI mutex initialization failed");
  }

  input.begin();
  display.begin();
  const bool settingsOK = settings.begin();

  display.bootScreen();
  if (!settingsOK) Serial.println("WARNING: NVS settings initialization failed");

  selected = settings.getLastMenuIndex();
  if (selected >= MENU_COUNT) selected = 0;
  render();

  Serial.println("HETPAHH OS v0.5 core started (hardware unverified)");
}

void loop() {
  const uint8_t events = input.poll();

  if (page == Page::MENU) {
    if (events & KEY_UP) {
      selected = (selected + MENU_COUNT - 1) % MENU_COUNT;
      settings.setLastMenuIndex(selected);
      render();
    } else if (events & KEY_DOWN) {
      selected = (selected + 1) % MENU_COUNT;
      settings.setLastMenuIndex(selected);
      render();
    } else if (events & KEY_OK) {
      page = static_cast<Page>(selected + 1);
      render();
    }
  } else if (events & KEY_LEFT) {
    page = Page::MENU;
    render();
  }

  delay(2);
}
