#pragma once

#include "ITelemetrySource.h"

class DemoTelemetrySource final : public ITelemetrySource {
 public:
  TelemetryData read() override;
};
