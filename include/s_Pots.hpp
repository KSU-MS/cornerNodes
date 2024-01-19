#ifndef s_Pots_HPP
#define s_Pots_HPP

// Imports
#include "main.hpp"
#include <Adafruit_ADS1X15.h>
#include <Arduino.h>

// Function defs
void init_ADC();      // Basic function for starting the ADC
uint8_t *pots_Data(); // Yeets data out

#ifdef SHOCK_POT
// Function defs
void init_shock(String method, uint8_t pin); // Sets the source
void shock_Update();                         // updates the pot
#endif

#ifdef STEER_POT
// Function defs
void init_steer(String method, uint8_t pin); // Sets the source
void steer_Update();                         // updates the pot
#endif

#endif
