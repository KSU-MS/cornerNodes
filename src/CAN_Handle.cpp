#include "CAN_Handle.hpp"
#include "CAN_MCP2515.hpp"

// Initializes the SPI pins, CAN, and CS
void init_CAN() {
  SPI.begin();
  CAN.begin(CAN_BPS_500K);
}

// Sends through SPI.
void send_CAN(uint16_t id, uint8_t buf[]) {

  // Create new CAN message called "msg"
  CAN_Frame msg;

  // This if statement just prevents the auto generated ids from fucking shit up
  // 2047 is the max ID for CAN messages btw
  if (id <= 2047) {
    // Configure "msg"
    msg.id = id;
    msg.extended = false;
    msg.length = 8;

    // Load data into msg's buffer
    for (uint8_t i = 0; i < 8; i++) {
      msg.data[i] = buf[i];
    }

    // Send the messages through CAN
    CAN.write(msg);
  }
}
