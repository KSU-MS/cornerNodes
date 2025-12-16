#include "car.h"
#include "core_pins.h"
#include <main.hpp>

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the pins
  pinMode(21, INPUT);
  pinMode(20, INPUT);
  pinMode(16, INPUT);
  pinMode(15, INPUT);
  pinMode(14, INPUT);

  // frontLeft.init(2, &frontLeftISR, &pulseCount);
}

void loop() {
  // Update our fellows
  left_shock_pot.update();
  right_shock_pot.update();
  front_brake.update();
  rear_brake.update();
  steering_pot.update();
  // frontLeft.update_rpms(millis());

  if (hz_50.check()) {
    encode_can_0x384_cornernode_fl_shockpot(&kms_dbc, left_shock_pot.value.in);
    left_shock_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_FL_SHOCKPOT, &left_shock_msg.buf.val);

    encode_can_0x385_cornernode_fr_shockpot(&kms_dbc, right_shock_pot.value.in);
    right_shock_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_FR_SHOCKPOT, &right_shock_msg.buf.val);

    // encode_can_0x388_cornernode_fl_wheelspeed(&kms_dbc,
    // frontLeft.get_rpms()); front_left_ws_msg.length = pack_message(
    //     &kms_dbc, CAN_ID_CORNERNODE_FL_WHEELSPEED,
    //     &front_left_ws_msg.buf.val);
    //
    // Serial.printf("Left wheelspeed: %i\n\r", frontLeft.get_rpms());

    daq_can.send_controller_message(left_shock_msg);
    daq_can.send_controller_message(right_shock_msg);
    // daq_can.send_controller_message(front_left_ws_msg);

    hz_50.reset();
  }

  if (hz_20.check()) {
    encode_can_0x390_cornernode_front_brakepressure(&kms_dbc,
                                                    front_brake.value.in);
    front_brake_msg.length =
        pack_message(&kms_dbc, CAN_ID_CORNERNODE_FRONT_BRAKEPRESSURE,
                     &front_brake_msg.buf.val);

    encode_can_0x391_cornernode_rear_brakepressure(&kms_dbc,
                                                   rear_brake.value.in);
    rear_brake_msg.length =
        pack_message(&kms_dbc, CAN_ID_CORNERNODE_REAR_BRAKEPRESSURE,
                     &rear_brake_msg.buf.val);

    encode_can_0x383_cornernode_steeringpot(&kms_dbc, steering_pot.value.in);
    steering_pot_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_STEERINGPOT, &steering_pot_msg.buf.val);

    Serial.printf("Front: %i\n\r", front_brake.value.in);
    Serial.printf("Rear: %i\n\r", rear_brake.value.in);
    Serial.printf("steer: %i\n\r", steering_pot.value.in);

    daq_can.send_controller_message(front_brake_msg);
    daq_can.send_controller_message(rear_brake_msg);
    daq_can.send_controller_message(steering_pot_msg);

    hz_20.reset();
  }
}
