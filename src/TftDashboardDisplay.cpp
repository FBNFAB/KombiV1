#include "TftDashboardDisplay.h"

#include <SPI.h>
#include <stdio.h>

#include "DisplayConfig.h"

namespace {
constexpr uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue) {
  return static_cast<uint16_t>(((red & 0xF8U) << 8) |
                               ((green & 0xFCU) << 3) | (blue >> 3));
}

constexpr uint16_t kBackground = rgb565(0x58, 0x22, 0x2F);
constexpr uint16_t kRed = rgb565(0xBF, 0x1B, 0x2A);
constexpr uint16_t kDimRed = rgb565(0x8A, 0x2A, 0x38);
constexpr int16_t kHeaderDividerY = 44;
constexpr int16_t kSpeedAreaTop = 58;
constexpr int16_t kSpeedAreaHeight = 112;
constexpr int16_t kUnitTop = 183;
constexpr int16_t kFooterDividerY = 224;
constexpr int16_t kFooterTop = 250;
}  // namespace

TftDashboardDisplay::TftDashboardDisplay()
    : _tft(DisplayConfig::kChipSelectPin, DisplayConfig::kDataCommandPin,
           DisplayConfig::kResetPin) {}

void TftDashboardDisplay::begin() {
  pinMode(DisplayConfig::kBacklightPin, OUTPUT);
  digitalWrite(DisplayConfig::kBacklightPin, HIGH);

  SPI.begin(DisplayConfig::kClockPin, DisplayConfig::kMisoPin,
            DisplayConfig::kMosiPin, DisplayConfig::kChipSelectPin);
  _tft.begin();
  _tft.setRotation(0);
  _tft.invertDisplay(true);
  _tft.setTextWrap(false);
  _tft.fillScreen(kBackground);

  _tft.setTextColor(kRed);
  _tft.setTextSize(2);
  _tft.setCursor(14, 14);
  _tft.print(F("BORDCOMPUTER"));

  _tft.drawFastHLine(14, kHeaderDividerY, DisplayConfig::kWidth - 28, kDimRed);
  _tft.drawFastHLine(14, kFooterDividerY, DisplayConfig::kWidth - 28, kDimRed);

  _tft.setTextSize(2);
  _tft.setCursor(14, kFooterTop);
  _tft.print(F("GESCHWINDIGKEIT"));

  int16_t x1;
  int16_t y1;
  uint16_t textWidth;
  uint16_t textHeight;
  _tft.getTextBounds("km/h", 0, 0, &x1, &y1, &textWidth, &textHeight);
  const int16_t unitX = (DisplayConfig::kWidth - textWidth) / 2 - x1;
  const int16_t unitY = kUnitTop - y1;
  _tft.setCursor(unitX, unitY);
  _tft.print(F("km/h"));

  _lastSpeedKmh = UINT16_MAX;
}

void TftDashboardDisplay::render(const TelemetryData& data) {
  if (data.speedKmh != _lastSpeedKmh) {
    drawSpeed(data.speedKmh);
    _lastSpeedKmh = data.speedKmh;
  }
}

void TftDashboardDisplay::drawSpeed(uint16_t speedKmh) {
  _tft.setTextSize(8);

  const auto drawCentered = [this](const char* text) {
    int16_t x1;
    int16_t y1;
    uint16_t textWidth;
    uint16_t textHeight;
    _tft.getTextBounds(text, 0, 0, &x1, &y1, &textWidth, &textHeight);
    const int16_t x = (DisplayConfig::kWidth - textWidth) / 2 - x1;
    const int16_t y =
        kSpeedAreaTop + (kSpeedAreaHeight - textHeight) / 2 - y1;
    _tft.setCursor(x, y);
    _tft.print(text);
  };

  if (_lastSpeedKmh != UINT16_MAX) {
    char previousText[6];
    if (_lastSpeedKmh <= 999U) {
      snprintf(previousText, sizeof(previousText), "%u",
               static_cast<unsigned int>(_lastSpeedKmh));
    } else {
      snprintf(previousText, sizeof(previousText), "---");
    }
    _tft.setTextColor(kBackground, kBackground);
    drawCentered(previousText);
  }

  char text[4];
  if (speedKmh <= 999U) {
    snprintf(text, sizeof(text), "%u", static_cast<unsigned int>(speedKmh));
  } else {
    snprintf(text, sizeof(text), "---");
  }
  _tft.setTextColor(kRed, kBackground);
  drawCentered(text);
}
