#include "DemoTelemetrySource.h"

#include <Arduino.h>

TelemetryData DemoTelemetrySource::read() {
  const uint32_t step = (millis() / 100U) % 320U;
  const uint16_t speed = static_cast<uint16_t>(step <= 160U ? step : 320U - step);
  return {speed};
}
