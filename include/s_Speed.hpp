#ifndef s_speed_hpp
#define s_speed_hpp

#include "main.h"

#ifdef WHEEL_SPD
// Imports
#include <Arduino.h>
#include <FreqMeasureMulti.h>

class Wheel_Spd {
  int count;
  float sum;
  uint8_t offset;
  FreqMeasureMulti ws;

  union {
    uint16_t in;
    byte b[2];
  } value;

public:
  void init(uint8_t pin, uint8_t offset);
  void update();
  uint8_t *getMessage();
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
}

uint8_t *Wheel_Spd::getMessage() {
  // Holder for the byte array
  uint8_t *spd_msg;

  // If car has moved update value
  if (count > 0) {
    value.in = (int)((ws.countToFrequency(sum / count) * 60 / 18) * 100);

    // Reset working vars
    sum = 0;
    count = 0;
  }

  // Copy the value into a uint8_t array for CAN
  spd_msg[offset] = value.b[0];
  spd_msg[offset + 1] = value.b[1];

#ifdef DEBUG
  // Print the raw value
  Serial.printf("RPM: %d\n", value.in);
#endif // DEBUG

  // Return the calculated value or last value
  return spd_msg;
}

#endif // WHEEL_SPD
#endif // s_speed_hpp
