#include "s_Pots.hpp"

// Global vars
uint8_t pots_msg[8];
Adafruit_ADS1115 ads; // Class assigment for the 16 bit ADC

// Helper functions for the pointer
uint16_t avr_helper(uint8_t pin) { return (uint16_t)analogRead(pin); }
uint16_t adc_helper(uint8_t pin) { return ads.readADC_SingleEnded(pin); }

void init_ADC() {
  ads.begin();

  if (!ads.begin()) {
    Serial.println("Failed to init ADC");
  } else {
    Serial.println("ADC enabled");
  }
}

#ifdef SHOCK_POT
// Local vars
uint16_t (*shock_s)(uint8_t); // Pointer to whatever read function is needed
uint8_t SHOCK_PIN;            // tracks what pin to read
uint8_t shock_msg[2];         // Hold our value for later

void init_shock(String method, uint8_t pin) {
  SHOCK_PIN = pin;

  if (method == "ADC") {
    // Sets shock_PIN pointer to the ADC read function
    shock_s = &adc_helper;
    Serial.println("shock ADC enabled");
  } else if (method == "AVR") {
    // Sets shock_PIN pointer to the AVR read function
    shock_s = &avr_helper;
    Serial.println("shock AVR enabled");
  }
}

// Function to actually read the boi
void shock_Update() {
  // Read value from PIN
  uint16_t v = (*shock_s)(SHOCK_PIN);

// Print the raw value
#ifdef DEBUG
  Serial.print("Shock raw: ");
  Serial.println(v);
#endif // DEBUG

  // Copy the value into a uint8_t array for CAN
  memcpy(shock_msg, &v, sizeof(v));
}
#endif // SHOCK_POT

#ifdef STEER_POT
// Local vars
uint16_t (*steer_s)(uint8_t); // Pointer to whatever read function is needed
uint8_t STEER_PIN;            // tracks what pin to read
uint8_t steer_msg[2];         // Hold our value for later

void init_steer(String method, uint8_t pin) {
  STEER_PIN = pin;

  if (method == "ADC") {
    // Sets steer_PIN pointer to the ADC read function
    steer_s = &adc_helper;
    Serial.println("steer ADC enabled");
  } else if (method == "AVR") {
    // Sets steer_PIN pointer to the AVR read function
    steer_s = &avr_helper;
    Serial.println("steer AVR enabled");
  }
}

// Function to actually read the boi
void steer_Update() {
  // Read value from PIN
  uint16_t v = (*steer_s)(STEER_PIN);

// Print the raw value
#ifdef DEBUG
  Serial.print("Steer raw: ");
  Serial.println(v);
#endif // DEBUG

  // Copy the value into a uint8_t array for CAN
  memcpy(steer_msg, &v, sizeof(v));
}
#endif // SHOCK_POT

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
