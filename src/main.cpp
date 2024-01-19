// All the toggles are in the "main.hpp" file
#include "main.hpp"
#include "s_Pots.hpp"

// If you want to add a new sensor, create a header file with your defs and libs
// then make a cpp for its logic, you'll also have to add the sensor to the CIs
// class in "CAN_Label_Maker.hpp" and define how you want that to generate its
// IDs in "CAN_Label_Maker.cpp".

// Get IDs after calcs
CIs ID = calc_IDs(node_fl); // SET OFFSET HERE

Metro uaPots = 50; // Shock Pot pol rate
Metro uSpeed = 50; // Wheel speed pol rate
Metro uTemps = 50; // Tire Temp pol rate
Metro uART = 3000; // Timeout for waiting on user to connect

void setup() {
  // Setup blue can chip
  init_CAN();

  // Setup ADC for 16 bit reads
  init_ADC();

  // Init wheel speed
  init_ws();

  // Init temp sensor
  init_ts();

  // Init shock pot with ADC
  init_shock("ADC", 0);

  // Init steer pot with AVR
  init_steer("AVR", 23);

  // Start serial
  Serial.begin(9600);

#ifdef DEBUG
  // Wait for user to connect to see all output
  while (!Serial) {
    // Break on timeout
    if (uART.check()) {
      break;
    }
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

  if (uSpeed.check()) {
    send_CAN(ID.speedID, ws_Val());
  }

  // Update our fellows
  shock_Update();
  steer_Update();
  ws_Update();
}
