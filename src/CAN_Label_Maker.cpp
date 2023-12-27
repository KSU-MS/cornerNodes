// Basic set of functions to generate CAN ID's for each node

#include "CAN_Label_Maker.hpp"

// Base vars, due to how I've incremented these, its only possiable for 16 of
// each type of sensor before shit starts to break, but thankfully we don't have
// enough money for this to be an issue, and CAN id's are an 11 bit system
int shockBase = 1728; // 0x6C0
int steerBase = 1712; // 0x6B0
int speedBase = 1696; // 0x6A0
int tempOBase = 1984; // 0x7C0
int tempMBase = 1968; // 0x7B0
int tempIBase = 1952; // 0x7C0

CIs calc_IDs(uint8_t offset) {
  // Define a holder
  CIs ci_out;

  // Set the feilds for the holder
  ci_out.shockID = shockBase + offset;
  ci_out.steerID = steerBase + offset;
  ci_out.speedID = speedBase + offset;
  ci_out.tempOID = tempOBase + offset;
  ci_out.tempMID = tempMBase + offset;
  ci_out.tempIID = tempIBase + offset;

  // Spit out results from the holder
  return ci_out;
}
