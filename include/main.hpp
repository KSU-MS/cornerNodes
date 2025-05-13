#pragma once

// Arduino stuffs
#include <Arduino.h>
// timers
#include <Metro.h>
Metro uSteer(20, true);

// Can stuffs
#include "can_tools.hpp"
#include <car.h>
can_obj_car_h_t kms_dbc;
canMan can(TEENSY_CAN2, 1000000);

// Pot things
#include <adc.hpp>
adc steering_pot(avr, 15);
can_message steer_pot_msg;
