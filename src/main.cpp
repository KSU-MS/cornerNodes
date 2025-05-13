#include <main.hpp>

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the pins
  pinMode(15, INPUT);

  // Set up the can msg
  steer_pot_msg.id = CAN_ID_OMNI_STEERING_DATA;
}

void loop() {
  // Update our fellows
  steering_pot.update();

  if (uSteer.check()) {
    steer_pot_msg.length = pack_message(&kms_dbc, CAN_ID_OMNI_STEERING_DATA,
                                        &steer_pot_msg.buf.val);
    can.send_controller_message(steer_pot_msg);
  }
}
