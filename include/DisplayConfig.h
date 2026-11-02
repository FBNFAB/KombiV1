#pragma once

#include <Arduino.h>

namespace DisplayConfig {
constexpr uint8_t kChipSelectPin = 27;
constexpr uint8_t kDataCommandPin = 22;
constexpr uint8_t kResetPin = 4;
constexpr uint8_t kBacklightPin = 21;

constexpr uint8_t kClockPin = 18;
constexpr uint8_t kMisoPin = 19;
constexpr uint8_t kMosiPin = 23;

constexpr uint16_t kWidth = 240;
constexpr uint16_t kHeight = 320;
}  // namespace DisplayConfig
