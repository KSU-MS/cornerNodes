#include "s_Speed.hpp"

// Local vars
uint8_t speed_PIN;
uint8_t speed_msg[8];

// Function to set pin for other shit
void speed_Pin(uint8_t pin) {
  speed_PIN = pin;
#ifdef DEBUG
  Serial.println("Wheel speed enabled");
#endif
}

// Function to actually read the boi
uint8_t *speed_Val() {
  // Read value from PIN
  uint32_t v = digitalRead(speed_PIN);

  // Copy the value into a uint8_t array for CAN
  memcpy(speed_msg, &v, sizeof(v));

// Print the raw value and uint8_t array value
#ifdef DEBUG
  Serial.println(speed_msg);
  Serial.println(v);
#endif

  // Return that value
  return speed_msg;
}
