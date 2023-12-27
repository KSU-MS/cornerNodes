#ifndef _CAN_Label_Maker_H_
#define _CAN_Label_Maker_H_

// Imports
#include <Arduino.h>

// Struct to hold all IDs
struct CIs {
  uint16_t shockID; // shock pot ID
  uint16_t steerID; // steering pot ID
  uint16_t speedID; // wheel speed ID
  uint16_t tempOID; // Tire temp outer ID
  uint16_t tempMID; // Tire temp mid ID
  uint16_t tempIID; // Tire temp inner ID
};

// Function to make IDs
CIs calc_IDs(uint8_t offset);

#endif
