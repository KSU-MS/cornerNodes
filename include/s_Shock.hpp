#ifndef s_shock_HPP
#define s_shock_HPP

// Imports
#include "main.hpp"
#include <Arduino.h>

// Function defs
void shock_AVR(uint8_t pin); // Any Analog in pin on the pro micro works
void shock_ADC(uint8_t pin); // 0-3 are your options
uint8_t *shock_Val();        // returns a CAN friendly value from the sensor

#endif
