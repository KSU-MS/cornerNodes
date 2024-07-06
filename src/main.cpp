#include "main.hpp"
#include "CAN_Handle.hpp"

// Some globals
Metro uBrake = 20;

Analog RL_shock;
Analog RR_shock;
Wheel_Spd RL_ws;
Wheel_Spd RR_ws;

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the ADC
  init_adc();

  // Start sensors
  RL_shock.init(0, true);
  RR_shock.init(2, true);

  RL_ws.init(9, 0);
  RR_ws.init(22, 0);

  // Setup whatever CAN coms
  init_CAN();
}

void loop() {
  // Update our fellows
  RL_shock.update();
  RR_shock.update();

  RL_ws.update();
  RR_ws.update();

  if (uBrake.check()) {
    send_CAN(SHOCK_RL, sizeof(RL_shock.value), RL_shock.value.b);
    send_CAN(SHOCK_RR, sizeof(RR_shock.value), RR_shock.value.b);

    send_CAN(WHEELSPEED_RL, sizeof(RL_ws.value), RL_ws.value.b);
    send_CAN(WHEELSPEED_RR, sizeof(RR_ws.value), RR_ws.value.b);
  }
}
