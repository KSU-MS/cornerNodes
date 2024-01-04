// All the toggles are in the "main.hpp" file
#include "main.hpp"

// If you want to add a new sensor, create a header file with your defs and libs
// then make a cpp for its logic, you'll also have to add the sensor to the CIs
// class in "CAN_Label_Maker.hpp" and define how you want that to generate its
// IDs in "CAN_Label_Maker.cpp".

CIs ID = calc_IDs(0); // IDs after calcs SET OFFSET HERE

Metro uaPots = 50; // Shock Pot pol rate
Metro uSpeed = 50; // Wheel speed pol rate
Metro uTemps = 50; // Tire Temp pol rate
Metro uART = 1000; // Timeout for waiting on user to connect

void setup() {

  init_CAN();

  init_ADC();
  shock_ADC(0);
  // shock_AVR(18);
  steer_ADC(1);

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

  if (uTemps.check()) {
    send_CAN(ID.ttempID, temps_IMO());
  }

  // if (uSpeed.check()) {
  // }
}
