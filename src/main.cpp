#include "main.hpp"

// Some globals
Metro uPot = 50;   // Shock Pot pol rate
Metro uSpeed = 50; // speed speed pol rate

Analog fl_pot;
Analog fr_pot;
Analog f_brake;
Analog r_brake;
Wheel_Spd fl_speed;
Wheel_Spd fr_speed;
// Tire_Temp temp;

void setup() {
  // Start serial
  Serial.begin(9600);

  // Start sensors
  fl_pot.init(0, true, 10);
  fr_pot.init(2, true, 10);
  f_brake.init(1, true);
  r_brake.init(3, true);
  fl_speed.init(9, 0);
  fr_speed.init(22, 0);

  // Setup whatever CAN coms
  init_CAN();
}

void loop() {
  // Update our fellows
  fl_pot.update();
  fr_pot.update();
  f_brake.update();
  r_brake.update();
  fl_speed.update();
  fr_speed.update();

  if (uPot.check()) {
    send_CAN(SHOCK_FL, sizeof(fl_pot.value.b), fl_pot.value.b);
    send_CAN(SHOCK_FR, sizeof(fr_pot.value.b), fr_pot.value.b);
    send_CAN(BRAKEPRESSURE_F, sizeof(f_brake.value.b), f_brake.value.b);
    send_CAN(BRAKEPRESSURE_R, sizeof(r_brake.value.b), r_brake.value.b);
  }

  if (uSpeed.check()) {
    send_CAN(WHEELSPEED_FL, sizeof(fl_speed.value.b), fl_speed.value.b);
    send_CAN(WHEELSPEED_FR, sizeof(fr_speed.value.b), fr_speed.value.b);
  }
}
