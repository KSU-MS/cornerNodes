// All the toggles are in the "main.hpp" file
#include "main.h"
#include "CAN_Handle.hpp"
#include "WProgram.h"

// If you want to add a new sensor, create a hpp file with your defs, libs and
// its logic, you'll also have to add the sensor to the CIs class in
// "CAN_Label_Maker.hpp" and define how you want that to generate its IDs

// Get IDs after calcs
CIs ID = calc_IDs(node_fl); // SET OFFSET HERE

// Init pots
Pot fl = Pot(1, true);
Pot fr = Pot(2, true);
Pot steer = Pot(16, false);

Metro uPot = 50;   // Shock Pot pol rate
Metro uSpeed = 50; // Wheel speed pol rate
Metro uTemps = 50; // Tire Temp pol rate
Metro uART = 3000; // Timeout for waiting on user to connect

void setup() {
  // Setup whatever can (defined in the main.h)
  init_CAN();

  // Init wheel speed
  init_ws();

  // Init temp sensor
  init_ts();

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
  if (uPot.check()) {
    // TODO: Make this not stupid maybe
    uint8_t *msg;
    msg[0] = fl.getMessage()[0];
    msg[1] = fl.getMessage()[1];
    msg[2] = fr.getMessage()[0];
    msg[3] = fr.getMessage()[1];
    msg[4] = steer.getMessage()[0];
    msg[5] = steer.getMessage()[1];

    send_CAN(ID.apotsID, msg);
  }

  if (uTemps.check()) {
    send_CAN(ID.ttempID, temps_IMO());
  }

  if (uSpeed.check()) {
    send_CAN(ID.speedID, ws_Val());
  }

  // Update our fellows
  ws_Update();
}
