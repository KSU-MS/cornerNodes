#include "s_Steer.hpp"

// Local vars
uint8_t steer_PIN;
uint8_t steer_msg[8];

// Function to set pin for other shit
void steer_Pin(uint8_t pin) {
  steer_PIN = pin;
#ifdef DEBUG
  Serial.println("Steering enabled");
#endif
}

// Function to actually read the boi
uint8_t *steer_Val() {
  // Read value from PIN
  uint32_t v = analogRead(steer_PIN);

  // Copy the value into a uint8_t array for CAN
  memcpy(steer_msg, &v, sizeof(v));

// Print the raw value and uint8_t array value
#ifdef DEBUG
  Serial.println(steer_msg);
  Serial.println(v);
#endif

  // Return that value
  return steer_msg;
}
