#pragma once

// Arduino stuffs
#include <Arduino.h>
// timers
#include <Metro.h>
Metro hz_20(50, true);
Metro hz_50(20, true);

// Pot things
#include <adc.hpp>
adc left_shock_pot(avr, 20);
adc right_shock_pot(avr, 15);
adc motor_temp(avr, 19);
adc coolant_temp(avr, 17);

// Can stuffs
#include "can_tools.hpp"
#include <car.h>
can_obj_car_h_t kms_dbc;
canMan inv_can(TEENSY_CAN1, 500000);
canMan daq_can(TEENSY_CAN2, 1000000);

can_message left_shock_msg = {.id = CAN_ID_CORNERNODE_RL_SHOCKPOT};
can_message right_shock_msg = {.id = CAN_ID_CORNERNODE_RR_SHOCKPOT};
can_message motor_temp_msg = {.id = CAN_ID_CORNERNODE_MOTOR_TEMP};
can_message coolant_temp_msg = {.id = CAN_ID_CORNERNODE_COOLANT_TEMP};
can_message rr_wheelspeed_msg = {.id = CAN_ID_CORNERNODE_RR_WHEELSPEED};

double adjusted_motor_temp;
double adjusted_coolant_temp;

// #include "ws.hpp"
// uint64_t rr_pulseCount;
//
// void rearRightISR() { rr_pulseCount++; }
//
// wheel_speed rearRight;
