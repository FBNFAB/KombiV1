#include <Arduino.h>

#include "BoardComputer.h"
#include "DemoTelemetrySource.h"
#include "TftDashboardDisplay.h"

namespace {
DemoTelemetrySource telemetrySource;
TftDashboardDisplay display;
BoardComputer boardComputer(telemetrySource, display);
}  // namespace

void setup() {
  boardComputer.begin();
}

void loop() {
  boardComputer.update();
}
