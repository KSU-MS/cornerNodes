#ifndef s_speed_hpp
#define s_speed_hpp

#include "main.h"

#ifdef WHEEL_SPD
// Imports
#include <Arduino.h>
#include <FreqMeasureMulti.h>
#include <Metro.h>

class Wheel_Spd {
private:
  int count;
  float sum;
  uint8_t offset;
  FreqMeasureMulti ws;
  Metro timeout = 100;

public:
  void init(uint8_t pin, uint8_t offset);
  void update();

  union {
    uint16_t in;
    byte b[2];
  } value;
};

// Tells the lib to start reading pin X. Look at FreqMeasureMulti repo for what
// pins/controllers are supported
void Wheel_Spd::init(uint8_t set_pin, uint8_t set_offset) {
  offset = set_offset;

  ws.begin(set_pin);
  Serial.printf("Set pin %d for wheel speed with offset %d\n", set_pin, offset);
}

void Wheel_Spd::update() {
  // Read value from WS
  if (ws.available()) {
    sum = sum + ws.read();
    count = count + 1;
  }

  // If car has moved update value
  if (count > 1) {
    value.in = ws.countToFrequency(sum / count) * 60 / 18;
    Serial.println(value.in);

    // Reset working vars
    sum = 0;
    count = 0;
  } else {
    if (timeout.check()) {
      value.in = 0;
    }
  }

#ifdef DEBUG
  // Print the raw value
  Serial.printf("RPM: %d\n", value.in);
#endif // DEBUG
}

#endif // WHEEL_SPD
#endif // s_speed_hpp
