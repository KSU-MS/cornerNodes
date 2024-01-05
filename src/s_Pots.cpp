#include "s_Pots.hpp"

// Global vars
uint8_t pots_msg[8];
uint16_t avr_helper(uint8_t pin) {
  return (uint16_t)analogRead(pin); // Wacky cast shit
}

#ifdef ADC_READS
Adafruit_ADS1115 ads; // Class assigment for the 16 bit ADC

void init_ADC() {
  ads.begin(); // Start

#ifdef DEBUG
  if (!ads.begin()) {
    Serial.println("Failed to init ADC");
  } else {
    Serial.println("ADC enabled");
  }
#endif // DEBUG
}

// Wacky cast shit
uint16_t adc_helper(uint8_t pin) {
  return (uint16_t)ads.readADC_SingleEnded(pin);
}
#endif // ADC READ

#ifdef SHOCK_POT
// Local vars
uint16_t (*shock_PIN)(uint8_t); // Pointer to whatever read function is needed
uint8_t SHOCK_PIN;              // tracks what pin to read
uint8_t shock_msg[2];           // Hold our value for later

#ifdef ADC_READS
// Sets shock_PIN to the ADC read function
void shock_ADC(uint8_t pin) {
  SHOCK_PIN = pin;
  shock_PIN = &adc_helper;
#ifdef DEBUG
  Serial.println("shock ADC enabled");
#endif // DEBUG
}
#endif // ADC_READS

// Sets shock_PIN to the AVR read function
void shock_AVR(uint8_t pin) {
  SHOCK_PIN = pin;
  shock_PIN = &avr_helper;
#ifdef DEBUG
  Serial.println("shock AVR enabled");
#endif // DEBUG
}

// Function to actually read the boi
uint8_t *shock_Val() {
  // Read value from PIN
  uint16_t v = (*shock_PIN)(SHOCK_PIN);

  // Copy the value into a uint8_t array for CAN
  memcpy(shock_msg, &v, sizeof(v));

// Print the raw value and uint8_t array value
#ifdef DEBUG
  Serial.print("Shock raw: ");
  Serial.println(v);
#endif // DEBUG

  // Return that value
  return shock_msg;
}
#endif // SHOCK_POT

#ifdef STEER_POT
// Local vars
uint16_t (*steer_PIN)(uint8_t); // Pointer to whatever read function is needed
uint8_t STEER_PIN;              // tracks what pin to read
uint8_t steer_msg[2];           // Hold our value for later

#ifdef ADC_READS
// Sets steer_PIN to the ADC read function
void steer_ADC(uint8_t pin) {
  STEER_PIN = pin;
  steer_PIN = &adc_helper;

#ifdef DEBUG
  Serial.println("steer ADC enabled");
#endif // DEBUG
}
#endif // ADC_READS

// Sets steer_PIN to the AVR read function
void steer_AVR(uint8_t pin) {
  STEER_PIN = pin;
  steer_PIN = &avr_helper;

#ifdef DEBUG
  Serial.println("steer AVR enabled");
#endif // DEBUG
}

// Function to actually read the boi
uint8_t *steer_Val() {
  // Read value from PIN
  uint16_t v = (*steer_PIN)(STEER_PIN);

// Print the raw value
#ifdef DEBUG
  Serial.print("Steer raw: ");
  Serial.println(v);
#endif // DEBUG

  // Copy the value into a uint8_t array for CAN
  memcpy(steer_msg, &v, sizeof(v));

  // Return that value
  return steer_msg;
}
#endif // STEER_POT

uint8_t *pots_Data() {
#ifdef SHOCK_POT
  pots_msg[0] = shock_msg[0];
  pots_msg[1] = shock_msg[1];
#endif

#ifdef STEER_POT
  pots_msg[2] = steer_msg[0];
  pots_msg[3] = steer_msg[1];
#endif

  return pots_msg;
}
