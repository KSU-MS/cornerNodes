#ifndef s_temps_HPP
#define s_temps_HPP

// Imports
#include "main.hpp"
#include <Adafruit_MLX90640.h>
#include <Arduino.h>
#include <SPI.h>

// Function defs
void temps_I2C(uint8_t SDA, uint8_t SDL);
uint8_t *temps_IMO();

#endif
