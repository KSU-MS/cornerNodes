#ifndef s_Pots_HPP
#define s_Pots_HPP

// Imports
#include "main.hpp"
#include <Arduino.h>

// Data out function
uint8_t *pots_Data();

#ifdef ADC_READS
// More imports
#include <Adafruit_ADS1X15.h>

// Function defs
void init_ADC(); // Basic function for setup
#endif

#ifdef SHOCK_POT
// Function defs
void shock_AVR(uint8_t pin); // Any Analog in pin on the pro micro works
void shock_ADC(uint8_t pin); // 0-3 are your options
uint8_t *shock_Val();        // returns a CAN friendly value from the sensor
#endif

#ifdef STEER_POT
// Function defs
void steer_AVR(uint8_t pin); // Any Analog in pin on the pro micro works
void steer_ADC(uint8_t pin); // 0-3 are your options
uint8_t *steer_Val();        // returns a CAN friendly value from the sensor
#endif

#endif
