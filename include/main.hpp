#ifndef main_HPP
#define main_HPP

// Toggles for diffrent features
#define ADC_READS // enables use of the ADC instead of the AVR analog read
#define SHOCK_POT // enables reading and sending of shock pot values
#define STEER_POT // enables reading and sending of steering values
#define TIRE_TEMP // enables reading and sending of tire temps values
// #define WHEEL_SPD // enables reading and sending of wheel speed values
#define DEBUG

// Always needed imports
#include "CAN_Handle.hpp"
#include "CAN_Label_Maker.hpp"
#include <Arduino.h>
#include <Metro.h>

// Pot things
#ifdef SHOCK_POT
#include "s_Pots.hpp"
#endif
#ifdef STEER_POT
#include "s_Pots.hpp"
#endif

// Wheel speed things
#ifdef WHEEL_SPD
#include "s_Speed.hpp"
#endif

// Tire temp things
#ifdef TIRE_TEMP
#include "s_Temps.hpp"
#endif

#endif
