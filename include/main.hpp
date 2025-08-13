#pragma once

// Arduino stuffs
#include <Arduino.h>
// timers
#include <Metro.h>
Metro hz_20(50, true);
Metro hz_50(20, true);

// Pot things
#include <adc.hpp>
adc steering_pot(avr, 21);
adc left_shock_pot(avr, 20);
adc right_shock_pot(avr, 15);
adc rear_brake(avr, 14);
adc front_brake(avr, 16);

// Can stuffs
#include "can_tools.hpp"
#include <car.h>
can_obj_car_h_t kms_dbc;
canMan inv_can(TEENSY_CAN1, 500000);
canMan daq_can(TEENSY_CAN2, 1000000);

can_message left_shock_msg = {.id = CAN_ID_CORNERNODE_FL_SHOCKPOT};
can_message right_shock_msg = {.id = CAN_ID_CORNERNODE_FR_SHOCKPOT};
can_message front_brake_msg = {.id = CAN_ID_CORNERNODE_FRONT_BRAKEPRESSURE};
can_message rear_brake_msg = {.id = CAN_ID_CORNERNODE_REAR_BRAKEPRESSURE};
can_message steering_pot_msg = {.id = CAN_ID_CORNERNODE_STEERINGPOT};
