#pragma once

#include "TelemetryData.h"

class ITelemetrySource {
 public:
  virtual ~ITelemetrySource() = default;
  virtual TelemetryData read() = 0;
};
