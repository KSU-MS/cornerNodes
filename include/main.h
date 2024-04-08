#ifndef main_h
#define main_h

// Toggles for diffrent features
// #define FLEXCAN // sets CAN provider to the teensy's onboard CAN controller
#define BLUECAN   // sets CAN provider to the MCP2515
#define POT       // enables reading and sending of pot values
#define WHEEL_SPD // enables reading and sending of wheel speed values
// #define TIRE_TEMP // enables reading and sending of tire temp values
// #define DEBUG // enables debug prints for when shit doesn't look right

// Always needed imports
// #include "CAN_Handle.hpp"
#include "CAN_Label_Maker.hpp"
#include <Arduino.h>
#include <Metro.h>

// Pot things
#ifdef POT
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
