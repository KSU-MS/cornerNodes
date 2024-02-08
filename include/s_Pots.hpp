#ifndef s_Pots_hpp
#define s_Pots_hpp

// Imports
#include "main.h"
#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

#ifdef POT
// Global vars
uint8_t pots_msg[8];
Adafruit_ADS1115 ads; // Class assigment for the 16 bit ADC

// Helper functions for the pointer
uint16_t avr_helper(uint8_t pin) { return (uint16_t)analogRead(pin); }
uint16_t adc_helper(uint8_t pin) { return ads.readADC_SingleEnded(pin); }

// Class for initiating a pot and reading it out
class Pot {
  uint16_t (*reader)(uint8_t);
  uint8_t pin;

public:
  Pot(int set_pin, bool set_ADC);
  uint8_t *getMessage();
};

Pot::Pot(int set_pin, bool set_ADC) {
  if (set_ADC) {
    // Start the ADC
    ads.begin();

    if (!ads.begin()) {
      Serial.println("Failed to init ADC on pin ");
      Serial.println(set_pin);
    } else {
      reader = &adc_helper;
      Serial.print("Set ADC on pin ");
      Serial.println(set_pin);
    }
  } else {
    reader = &avr_helper;
    Serial.print("Set AVR on pin ");
    Serial.println(set_pin);
  }
}

uint8_t *Pot::getMessage() {
  // Vars to hold some data
  uint8_t *out;
  uint16_t v = reader(pin);

  // Copy the value into a uint8_t array for CAN
  memcpy(out, v, sizeof(v));

  return out;
}

#endif // POT
#endif // s_Pots_hpp
