#ifndef CAN_Handle_hpp
#define CAN_Handle_hpp

// Imports
#include "CAN_Defs.hpp"
#include "CAN_MCP2515.hpp"
#include <Arduino.h>

// The pin used for CS on the blue (un)can(ny) boi
#define CHIPSELECT 6

// Functions for SPI
void init_CAN();
void send_CAN(uint16_t id, uint8_t buf[]);

#endif
