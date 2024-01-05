// All the toggles are in the "main.hpp" file
#include "main.hpp"
#include "CAN_Handle.hpp"

// If you want to add a new sensor, create a header file with your defs and libs
// then make a cpp for its logic, you'll also have to add the sensor to the CIs
// class in "CAN_Label_Maker.hpp" and define how you want that to generate its
// IDs in "CAN_Label_Maker.cpp".

CIs ID = calc_IDs(node_fl); // IDs after calcs SET OFFSET HERE

Metro uaPots = 50; // Shock Pot pol rate
Metro uSpeed = 50; // Wheel speed pol rate
Metro uTemps = 50; // Tire Temp pol rate
Metro uART = 1000; // Timeout for waiting on user to connect

void setup() {
  // Setup blue can chip
  init_CAN();

  // Setup ADC for 16 bit reads
  init_ADC();

  // Set pins for the pots
  shock_ADC(0);
  // shock_AVR(18);
  steer_ADC(1);

  // Init wheel speed shit also it only works on pin 13 for the micro
  init_WSPD();

#ifdef DEBUG
  Serial.begin(9600);
  // Wait for user to connect to see all output
  while (!Serial) {
    // Break on timeout
    if (uART.check()) {
      break;
    }
    // To not murder the boi
    delay(10);
  }
#endif
}

void loop() {
  if (uaPots.check()) {
    send_CAN(ID.apotsID, pots_Data());
  }

  // if (uTemps.check()) {
  //   send_CAN(ID.ttempID, temps_IMO());
  // }

  speed_Up();

  if (uSpeed.check()) {
    send_CAN(ID.speedID, speed_Val());
  }
}
