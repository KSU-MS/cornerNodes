#ifndef s_speed_HPP
#define s_speed_HPP

// Imports
#include "main.hpp"
#include <Arduino.h>
#include <FreqMeasureMulti.h>

// Pin for wheel speed sensor
#define WSP 9

// Function defs
void init_ws();
void ws_Update();
uint8_t *ws_Val();

#endif
