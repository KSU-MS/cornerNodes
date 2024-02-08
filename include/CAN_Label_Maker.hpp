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

// Base vars, due to how I've incremented these, its only possiable for 16 of
// each type of sensor before shit starts to break, but thankfully we don't have
// enough money for this to be an issue, and CAN id's are an 11 bit system
int apotsBase = 1728; // 0x6C0
int speedBase = 1696; // 0x6A0
int tTempBase = 1984; // 0x7C0

CIs calc_IDs(corner offset) {
  // Define a holder
  CIs ci_out;

  // Set the feilds for the holder
  ci_out.apotsID = apotsBase + offset;
  ci_out.speedID = speedBase + offset;
  ci_out.ttempID = tTempBase + offset;

  // Spit out results from the holder
  return ci_out;
}

#endif
