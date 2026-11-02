#pragma once

#include <stdint.h>

#include "IDashboardDisplay.h"
#include "ITelemetrySource.h"

class BoardComputer {
 public:
  BoardComputer(ITelemetrySource& telemetrySource,
                IDashboardDisplay& display);

  void begin();
  void update();

 private:
  static constexpr uint32_t kRefreshIntervalMs = 200;

  ITelemetrySource& _telemetrySource;
  IDashboardDisplay& _display;
  uint32_t _lastRefreshMs = 0;
};
