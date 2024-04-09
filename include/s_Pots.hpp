#ifndef s_Pots_hpp
#define s_Pots_hpp

#include "main.hpp"

#ifdef POT

// Imports
#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

Adafruit_ADS1115 ads; // Class assigment for the 16 bit ADC

// Helper functions for the pointer
uint16_t avr_helper(uint8_t pin) { return (uint16_t)analogRead(pin); }
uint16_t adc_helper(uint8_t pin) { return ads.readADC_SingleEnded(pin); }

// Class for initiating a pot and reading it out
class Pot {
private:
  uint8_t pin;
  uint8_t offset;
  uint16_t (*reader)(uint8_t);

public:
  void init(uint8_t set_pin, bool set_ADC, uint8_t set_offset);
  void update();

  union {
    uint16_t in;
    byte b[2];
  } value;
};

// The constructor for the class
void Pot::init(uint8_t set_pin, bool set_ADC, uint8_t set_offset) {
  Serial.println("Setting up pin " + String(set_pin));
  pin = set_pin;
  offset = set_offset;

  if (set_ADC) {
    // Start the ADC
    ads.begin();
    delay(200);

    if (ads.begin(0x48, &Wire1)) {
      reader = &adc_helper;
      Serial.println("Set ADC on pin " + String(set_pin));
    } else {
      Serial.println("Failed to init ADC on pin " + String(set_pin));
    }
  } else {
    reader = &avr_helper;
    Serial.println("Set AVR on pin " + String(set_pin));
  }
}

void Pot::update() {
  // Vars to hold some data
  value.in = reader(pin);

#ifdef DEBUG
  Serial.println("Pot pin: " + String(pin) + " - Val: " + String(value.in));
#endif // DEBUG
}

#endif // POT
#endif // s_Pots_hpp
