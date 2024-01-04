#ifndef _CAN_Label_Maker_H_
#define _CAN_Label_Maker_H_

// Imports
#include <Arduino.h>

// Struct to hold all IDs
struct CIs {
  uint16_t apotsID; // All pots ID
  uint16_t speedID; // wheel speed ID
  uint16_t ttempID; // Tire temp outer ID
};

// Function to make IDs
CIs calc_IDs(uint8_t offset);

#endif
