#include "main.hpp"
#include "CAN_Handle.hpp"

// Some globals
Metro uSend = 20;

Analog FL_shock;
Analog FR_shock;

Analog F_Brake;
Analog R_Brake;

Wheel_Spd FL_ws;
Wheel_Spd FR_ws;

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the ADC
  init_adc();

  // Start sensors
  FL_shock.init(0, true);
  FR_shock.init(1, true);

  F_Brake.init(2, true);
  R_Brake.init(3, true);

  FL_ws.init(9, 0);
  FR_ws.init(22, 0);

  // Setup whatever CAN coms
  init_CAN();
}

void loop() {
  // Update our fellows
  FL_shock.update();
  FR_shock.update();

  F_Brake.update();
  R_Brake.update();

  FL_ws.update();
  FR_ws.update();

  if (uSend.check()) {
    send_CAN(SHOCK_FL, sizeof(FL_shock.value), FL_shock.value.b);
    send_CAN(SHOCK_FR, sizeof(FR_shock.value), FR_shock.value.b);

    send_CAN(BRAKEPRESSURE_F, sizeof(F_Brake.value), F_Brake.value.b);
    send_CAN(BRAKEPRESSURE_R, sizeof(R_Brake.value), R_Brake.value.b);

    send_CAN(WHEELSPEED_FL, sizeof(FL_ws.value), FL_ws.value.b);
    send_CAN(WHEELSPEED_FR, sizeof(FR_ws.value), FR_ws.value.b);
  }
}
