// All the toggles are in the "main.hpp" file
#include "main.h"
#include <AA_MCP2515.h>
// #include "CAN_Handle.hpp"
// #include <CAN_MCP2515.h>

// If you want to add a new sensor, create a hpp file with your defs, libs and
// its logic, you'll also have to add the sensor to the CIs class in
// "CAN_Label_Maker.hpp" and define how you want that to generate its IDs

const CANBitrate::Config CAN_BITRATE = CANBitrate::Config_8MHz_500kbps;
const uint8_t CAN_PIN_CS = CSP;
const int8_t CAN_PIN_INT = 2;

CANConfig config(CAN_BITRATE, CAN_PIN_CS, CAN_PIN_INT);
CANController CAN(config);

// Some globals
Metro uPot = 50;   // Shock Pot pol rate
Metro uSpeed = 50; // Wheel speed pol rate
Metro uTemps = 50; // Tire Temp pol rate
Metro uART = 3000; // Timeout for waiting on user to connect
CIs ID;

// The sensors
Pot fl_pt;
Wheel_Spd fl_ws;
// Tire_Temp fl_tt;

void setup() {
  // Get IDs after calcs
  ID = calc_IDs(node_fl); // SET OFFSET HERE

  // Start serial
  Serial.begin(9600);

  fl_pt.init(0, true, 0);
  fl_ws.init(9, 0);
  // fl_tt.init();

  // Setup whatever CAN coms
  // init_CAN();
  while(CAN.begin(CANController::Mode::Normal) != CANController::OK) {
    Serial.println("CAN begin FAIL - delaying for 1 second");
    delay(1000);
  }
  Serial.println("CAN begin OK");

#ifdef DEBUG
  // Wait for user to connect to see all output
  while (!Serial) {
    // Break on timeout
    if (uART.check()) {
      break;
    }
    delay(10);
  }

  Serial.println("Debug enabled");
#endif

  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  // Update our fellows
  fl_pt.update();
  fl_ws.update();

  if (uPot.check()) {
    CANFrame frame(ID.apotsID,fl_pt.value.b,sizeof(fl_pt.value.b));
    CAN.write(frame);
    frame.print("Shockpot out");
    // send_CAN(ID.apotsID, fl_pt.value.b);
  }

  if (uSpeed.check()) {
    CANFrame frame(ID.speedID,fl_ws.value.b,sizeof(fl_ws.value.b));
    CAN.write(frame);
    frame.print("Shockpot out");
    // send_CAN(ID.speedID, fl_ws.value.b);
  }

  // if (uTemps.check()) {
  // send_CAN(ID.ttempID, fl_tt.getMessage());
  // }
}
