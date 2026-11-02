#include "DemoTelemetrySource.h"

#include <Arduino.h>

TelemetryData DemoTelemetrySource::read()
{
  constexpr uint32_t kMaxSpeedKmh = 110;
  const uint32_t step = (millis() / 100U) % (2U * kMaxSpeedKmh);
  const uint16_t speed = static_cast<uint16_t>(
      step <= kMaxSpeedKmh ? step : 2U * kMaxSpeedKmh - step);
  return {speed};
}
