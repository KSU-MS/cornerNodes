#ifndef CAN_Handle_hpp
#define CAN_Handle_hpp

// Imports
#include "main.h"
#include <Arduino.h>

#ifdef BLUECAN
// MCP Imports
#include "CAN_Defs.h"
#include "CAN_MCP2515.h"

// The pin used for CS on the blue (un)can(ny) boi
#define CHIPSELECT 6

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

#endif // BLUECAN

#ifdef FLEXCAN
// FLEXCAN Imports
#include <FlexCAN_T4.h>

// FLEXCAN Defs
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> fCAN;
static CAN_message_t msg;

void init_CAN() {
  // Start talking
  fCAN.begin();
  fCAN.setBaudRate(500000);

#ifdef DEBUG
  fCAN.mailboxStatus();
#endif // DEBUG

  // Configure mail boxes, we only need like 4 RX mailboxes because odds are we
  // never have to send this guy anything, but if we have to its still there
  // the number for this is found at the end of the FlexCAN_T4 readme.md
  for (int i = 0; i <= 3; i++) {
    fCAN.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }

  // Set every other mailbox to TX
  for (int i = 4; i <= 63; i++) {
    fCAN.setMB((FLEXCAN_MAILBOX)i, TX, STD);
  }

#ifdef DEBUG
  fCAN.mailboxStatus();
#endif // DEBUG
}

void send_CAN(uint16_t id, uint8_t *buf) {
  // Set ID
  msg.id = id;

  // Load data
  for (uint8_t i = 0; i < 8; i++) {
    msg.buf[i] = buf[i];
  }

  // Send
  fCAN.write(msg);
}
#endif // FLEXCAN
#endif // CAN_Handle_hpp
