#include "BoardComputer.h"

#include <Arduino.h>

BoardComputer::BoardComputer(ITelemetrySource& telemetrySource,
                             IDashboardDisplay& display)
    : _telemetrySource(telemetrySource), _display(display) {}

void BoardComputer::begin() {
  _display.begin();
  _lastRefreshMs = millis() - kRefreshIntervalMs;
}

void BoardComputer::update() {
  const uint32_t now = millis();
  if (static_cast<uint32_t>(now - _lastRefreshMs) < kRefreshIntervalMs) {
    return;
  }

  _lastRefreshMs = now;
  _display.render(_telemetrySource.read());
}
