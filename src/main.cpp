#include "main.hpp"
#include "CAN_Handle.hpp"

// Some globals
Metro uBrake = 20;

Analog f_brake;
Analog r_brake;
Analog FL_shock;
Analog FR_shock;

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the ADC
  init_adc();

  // Start sensors
  f_brake.init(0, true);
  r_brake.init(1, true);
  FL_shock.init(3, true);
  FR_shock.init(2, true);

  // Setup whatever CAN coms
  init_CAN();
}

void loop() {
  // Update our fellows
  f_brake.update();
  r_brake.update();
  FL_shock.update();
  FR_shock.update();

  if (uBrake.check()) {
    send_CAN(BRAKEPRESSURE_F, sizeof(f_brake.value), f_brake.value.b);
    send_CAN(BRAKEPRESSURE_R, sizeof(r_brake.value), r_brake.value.b);
    send_CAN(SHOCK_FL, sizeof(FL_shock.value), FL_shock.value.b);
    send_CAN(SHOCK_FR, sizeof(FR_shock.value), FR_shock.value.b);
  }
}
