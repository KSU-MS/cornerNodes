#ifndef s_Analogs_hpp
#define s_Analogs_hpp

#include "main.hpp"

#ifdef ANALOGS

// Imports
#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

Adafruit_ADS1115 ads; // Class assigment for the 16 bit ADC

void init_adc() {
  // Start the ADC
  ads.begin();
  ads.setGain(GAIN_TWOTHIRDS);
  ads.setDataRate(RATE_ADS1115_860SPS);
}

// Helper functions for the pointer
uint16_t avr_helper(uint8_t pin) { return (uint16_t)analogRead(pin); }
uint16_t adc_helper(uint8_t pin) { return ads.readADC_SingleEnded(pin); }

// Class for initiating a pot and reading it out
class Analog {
private:
  uint8_t pin;
  uint16_t (*reader)(uint8_t);
  uint16_t rawval;
  double alpha;
  bool is_filtered;

public:
  void init(uint8_t set_pin, bool set_ADC);
  void init(uint8_t set_pin, bool set_ADC, uint16_t cutoff_freq);
  void update();

  union {
    uint16_t in;
    byte b[2];
  } value;
};

// The constructor for the class
void Analog::init(uint8_t set_pin, bool set_ADC) {
  pin = set_pin;
  is_filtered = false;

  Serial.println("Setting up pin " + String(set_pin));

  if (set_ADC) {
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

void Analog::init(uint8_t set_pin, bool set_ADC, uint16_t cutoff_freq) {
  pin = set_pin;
  is_filtered = true;
  alpha = 2 * 3.14 * cutoff_freq / (1 + 2 * 3.14 * cutoff_freq);

  Serial.println("Pin " + String(set_pin) + " with alpha " + String(alpha));

  if (set_ADC) {
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

void Analog::update() {
  // Vars to hold some data
  if (is_filtered) {
    rawval = reader(pin);
    value.in = alpha * value.in + (1 - alpha) * rawval;
  } else {
    value.in = reader(pin);
  }

#ifdef DEBUG
  Serial.println("Analog pin: " + String(pin) + " - Val: " + String(value.in));
#endif // DEBUG
}

#endif // ANALOG
#endif // s_Analogs_hpp
