#include "main.hpp"

// Some globals
Metro uPot = 50;   // Shock Pot pol rate
Metro uSpeed = 50; // speed speed pol rate
Metro uTemps = 50; // Tire Temp pol rate
CIs ID;

// If you want to add a new sensor, create a hpp file with your defs, libs and
// its logic, you'll also have to add the sensor to the CIs class in
// "CAN_Label_Maker.hpp" and define how you want that to generate its IDs
Pot pot;
Wheel_Spd speed;
// Tire_Temp temp;

void setup() {
  // Get IDs after calcs
  ID.calc_IDs(node_fl); // SET OFFSET HERE

  // Start serial
  Serial.begin(9600);

  // Start sensors
  pot.init(0, true, 0);
  speed.init(9, 0);
  // temp.init();

  // Setup whatever CAN coms
  init_CAN();
}

void loop() {
  // Update our fellows
  pot.update();
  speed.update();

  if (uPot.check()) {
    send_CAN(ID.apotsID, sizeof(pot.value.b), pot.value.b);
  }

  if (uSpeed.check()) {
    send_CAN(ID.speedID, sizeof(speed.value.b), speed.value.b);
  }

  // if (uTemps.check()) {
  // send_CAN(ID.ttempID, temp.getMessage());
  // }
}
