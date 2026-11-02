#pragma once

#include "TelemetryData.h"

class IDashboardDisplay {
 public:
  virtual ~IDashboardDisplay() = default;
  virtual void begin() = 0;
  virtual void render(const TelemetryData& data) = 0;
};
