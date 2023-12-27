#include "s_Shock.hpp"
#include "ADC.hpp"
#include "Arduino.h"

// Local vars
int (*shock_PIN)(uint8_t); // Pointer to whatever read function is needed
uint8_t SHOCK_PIN;         // tracks what pin to read
uint8_t shock_msg[8];

// Sets shock_PIN to the AVR read function
void shock_AVR(uint8_t pin) {
  SHOCK_PIN = pin;
  shock_PIN = &analogRead;
#ifdef DEBUG
  Serial.println("shock AVR enabled");
#endif
}

// Sets shock_PIN to the ADC read function
void shock_ADC(uint8_t pin) {
  SHOCK_PIN = pin;
#ifdef DEBUG
  Serial.println("shock ADC enabled");
#endif
}

// Function to actually read the boi
uint8_t *shock_Val() {
  // Read value from PIN
  uint32_t v = (*shock_PIN)(SHOCK_PIN);

  // Copy the value into a uint8_t array for CAN
  memcpy(shock_msg, &v, sizeof(v));

// Print the raw value and uint8_t array value
#ifdef DEBUG
  Serial.print("Shock raw: ");
  Serial.print(v);
  Serial.print(", Shock CAN: ");
  // Serial.println(shock_msg);
#endif

  // Return that value
  return shock_msg;
}
