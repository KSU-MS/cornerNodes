#include "main.hpp"
#include "CAN_Handle.hpp"

// Some globals
Metro uBrake = 20;

Analog f_brake;
Analog r_brake;

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the ADC
  init_adc();

  // Start sensors
  f_brake.init(0, true, 20);
  r_brake.init(1, true, 20);

  // Setup whatever CAN coms
  init_CAN();
}

void loop() {
  // Update our fellows
  f_brake.update();
  r_brake.update();

  if (uBrake.check()) {
    send_CAN(BRAKEPRESSURE_F, sizeof(f_brake.value), f_brake.value.b);
    send_CAN(BRAKEPRESSURE_R, sizeof(r_brake.value), r_brake.value.b);
  }
}
