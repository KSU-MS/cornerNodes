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

enum corner {
  node_fl = 0,
  node_fr = 1,
  node_fm = 2,
  node_rl = 3,
  node_rr = 4,
  node_rm = 5,
};

// Function to make IDs
CIs calc_IDs(corner offset);

#endif
