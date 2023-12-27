#ifndef CAN_Handle_hpp
#define CAN_Handle_hpp

// Imports
#include <Arduino.h>

// The pin used for CS on the blue (un)can(ny) boi
#define CHIPSELECT 10

// Functions for SPI
void init_CAN();
void send_CAN(uint16_t id, uint8_t buf[]);

#endif
