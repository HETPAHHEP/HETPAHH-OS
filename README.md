# HETPAHH OS v0.5 — Core scaffold

This is a source project scaffold for ESP32-WROOM-32 + ILI9341 240x320 (no touch)
and five active-low buttons. It adds:
- shared SPI bus initialization and FreeRTOS mutex wrapper;
- button debounce and UP/DOWN key repeat;
- display manager and scrolling menu;
- NVS settings storage via Preferences;
- a deliberately disabled battery measurement stub.

## Important hardware status

The GPIO table in `include/pins.h` and `platformio.ini` is provisional, not approved
for wiring. Verify the exact ESP32 dev board, TFT module, button wiring, and radio
breakouts before connecting anything. Some ESP32 development boards reserve pins
or expose different labels.

Battery ADC is intentionally disabled. Never connect a Li-Po cell directly to an
ESP32 GPIO. Select a protected cell/charger/power-path solution and calculate a
divider using the actual ADC limits and board design before enabling measurement.

NRF24 PA/LNA needs a separate stable 3.3 V supply sized for its peak current,
local bulk + ceramic decoupling close to the module, and common ground with ESP32.
Do not power a PA/LNA module from an unverified weak 3.3 V regulator. Confirm
the module's voltage limits and pinout from its documentation.

All SPI devices must share SCK/MOSI/MISO but have separate chip-select lines.
Only one device may be selected at a time. This version supplies a mutex wrapper;
device-specific drivers must acquire it and configure SPI settings for each device.
TFT_eSPI uses the global SPI object on the selected ESP32 Arduino target, so verify
the library configuration and bus behavior before adding concurrent radio tasks.

## Build

1. Install VS Code + PlatformIO.
2. Open this folder as a PlatformIO project.
3. Build environment `esp32dev`.
4. If the exact board differs, change `board = esp32dev`.
5. Verify the TFT_eSPI setup against the actual display breakout.

## Not yet implemented / not verified

No Wi-Fi/BLE/NRF24/CC1101 radio driver is active. Battery sensing and backlight
PWM are not enabled. No firmware upload or physical hardware test has been done.
The project has not been compiled in this environment.

## Intended next stage

Confirm the exact ESP32 board and the power/charger module. Then validate the
display and buttons on the bench, followed by SPI device transactions and
passive-only radio receive/observation features for owned/authorized devices.
