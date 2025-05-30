#pragma once

// Arduino stuffs
#include <Arduino.h>
// timers
#include <Metro.h>
Metro hz_20(50, true);
Metro hz_50(20, true);

// Pot things
#include <adc.hpp>
adc left_shock_pot(avr, 15);
adc right_shock_pot(avr, 16);
adc front_brake(mcp, 0);
adc rear_brake(mcp, 1);

// Can stuffs
#include "can_tools.hpp"
#include <car.h>
can_obj_car_h_t kms_dbc;
canMan can(TEENSY_CAN2, 1000000);

can_message left_shock_msg;
can_message right_shock_msg;
can_message front_brake_msg;
can_message rear_brake_msg;
