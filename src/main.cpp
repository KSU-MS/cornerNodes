#include "car.h"
#include "core_pins.h"
#include <main.hpp>
#include <math.h>

void setup() {
  // Start serial
  Serial.begin(9600);

  // Init the pins
  pinMode(20, INPUT);
  pinMode(15, INPUT);
  pinMode(19, INPUT);

  // rearRight.init(15, &rearRightISR, &rr_pulseCount);
}

void loop() {
  // Update our fellows
  left_shock_pot.update();
  right_shock_pot.update();
  motor_temp.update();
  coolant_temp.update();
  // rearRight.update_rpms(millis());

  adjusted_motor_temp =
      (-14.2502 +
       sqrt(19.188 +
            (0.11148 * ((1503500 / float(motor_temp.value.in)) - 970)))) /
      0.05574;

  adjusted_coolant_temp =
      (-23.98808153477 *
       log(((0.00322265625 * coolant_temp.value.in) * 0.0321241830065) /
           (3.3 - (0.00322265625 * coolant_temp.value.in))));

  if (hz_50.check()) {
    encode_can_0x386_cornernode_rl_shockpot(&kms_dbc, left_shock_pot.value.in);
    left_shock_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_RL_SHOCKPOT, &left_shock_msg.buf.val);

    encode_can_0x387_cornernode_rr_shockpot(&kms_dbc, right_shock_pot.value.in);
    right_shock_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_RR_SHOCKPOT, &right_shock_msg.buf.val);

    encode_can_0x392_cornernode_motor_temp(&kms_dbc, adjusted_motor_temp);
    motor_temp_msg.length = pack_message(&kms_dbc, CAN_ID_CORNERNODE_MOTOR_TEMP,
                                         &motor_temp_msg.buf.val);

    encode_can_0x393_cornernode_coolant_temp(&kms_dbc, adjusted_coolant_temp);
    coolant_temp_msg.length = pack_message(
        &kms_dbc, CAN_ID_CORNERNODE_COOLANT_TEMP, &coolant_temp_msg.buf.val);

    // encode_can_0x38b_cornernode_rr_wheelspeed(&kms_dbc,
    // rearRight.get_rpms()); rr_wheelspeed_msg.length = pack_message(
    //     &kms_dbc, CAN_ID_CORNERNODE_RR_WHEELSPEED,
    //     &rr_wheelspeed_msg.buf.val);

    daq_can.send_controller_message(left_shock_msg);
    daq_can.send_controller_message(right_shock_msg);
    daq_can.send_controller_message(motor_temp_msg);
    daq_can.send_controller_message(coolant_temp_msg);
    // daq_can.send_controller_message(rr_wheelspeed_msg);

    // Serial.printf("left shock: %i\n\r", left_shock_pot.value.in);
    // Serial.printf("right shock: %i\n\r", right_shock_pot.value.in);
    // Serial.printf("motor temp: %f\n\r", adjusted_motor_temp);
    // Serial.printf("coolant temp: %f\n\r", adjusted_coolant_temp);
    // Serial.printf("right wheelspeed: %i\n\r", rearRight.get_rpms());

    hz_50.reset();
  }
}
