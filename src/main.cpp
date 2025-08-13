#include <main.hpp>

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the pins
  pinMode(20, INPUT);
  pinMode(15, INPUT);
}

void loop() {
  // Update our fellows
  left_shock_pot.update();
  right_shock_pot.update();

  if (hz_50.check()) {
    encode_can_0x386_cornernode_rl_shockpot(&kms_dbc, left_shock_pot.value.in);
    left_shock_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_RL_SHOCKPOT, &left_shock_msg.buf.val);

    encode_can_0x387_cornernode_rr_shockpot(&kms_dbc, right_shock_pot.value.in);
    right_shock_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_RR_SHOCKPOT, &right_shock_msg.buf.val);

    daq_can.send_controller_message(left_shock_msg);
    daq_can.send_controller_message(right_shock_msg);

    Serial.printf("left shock: %i\n\r", left_shock_pot.value.in);
    Serial.printf("right shock: %i\n\r", right_shock_pot.value.in);

    hz_50.reset();
  }
}
