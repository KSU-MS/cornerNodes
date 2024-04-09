#ifndef _CAN_Label_Maker_H_
#define _CAN_Label_Maker_H_

// Imports
#include <Arduino.h>

const int apotsBase = 900;
const int speedBase = 904;
const int tTempBase = 908;

enum corner {
  node_fl = 0,
  node_fr = 1,
  node_rl = 2,
  node_rr = 3,
};

// Struct to hold all IDs
class CIs {
public:
  uint16_t apotsID; // All pots ID
  uint16_t speedID; // wheel speed ID
  uint16_t ttempID; // Tire temp outer ID

  void calc_IDs(corner offset);
};

void CIs::calc_IDs(corner offset) {
  apotsID = apotsBase + offset;
  speedID = speedBase + offset;
  ttempID = tTempBase + offset;
}

#endif
