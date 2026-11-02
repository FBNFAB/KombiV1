#pragma once

#include <Adafruit_ILI9341.h>

#include "IDashboardDisplay.h"

class TftDashboardDisplay final : public IDashboardDisplay {
 public:
  TftDashboardDisplay();

  void begin() override;
  void render(const TelemetryData& data) override;

 private:
  Adafruit_ILI9341 _tft;
  uint16_t _lastSpeedKmh = UINT16_MAX;

  void drawSpeed(uint16_t speedKmh);
};
