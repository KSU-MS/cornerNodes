// All the toggles are in the "main.hpp" file
#include "main.hpp"

// If you want to add a new sensor, create a header file with your defs and libs
// then make a cpp for its logic, you'll also have to add the sensor to the CIs
// class in "CAN_Label_Maker.hpp" and define how you want that to generate its
// IDs in "CAN_Label_Maker.cpp".

CIs ID = calc_IDs(0); // IDs after calcs SET OFFSET HERE

#ifdef SHOCK_POT
Metro uShock = 50; // Shock Pot pol rate
#endif
#ifdef STEER_POT
Metro uSteer = 50; // Steering Pot pol rate
#endif
#ifdef WHEEL_SPD
Metro uSpeed = 50; // Wheel speed pol rate
#endif
#ifdef TIRE_TEMP
Metro uTemps = 50; // Tire Temp pol rate
#endif

// Debug things
#ifdef DEBUG
Metro uART = 1000; // Timeout for waiting on user to connect
#endif

void setup() {

  init_CAN();

#ifdef SHOCK_POT
#ifdef ADC
  shock_ADC(0);
#else
  shock_AVR(18);
#endif
#endif

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
#ifdef SHOCK_POT
  if (uShock.check()) {
    send_CAN(ID.shockID, shock_Val());
  }
#endif

#ifdef STEER_POT
  if (uSteer.check()) {
  }
#endif

#ifdef TIRE_TEMP
  if (uTemps.check()) {
  }
#endif

#ifdef WHEEL_SPD
  if (uSpeed.check()) {
  }
#endif
}
