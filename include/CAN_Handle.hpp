#ifndef CAN_Handle_hpp
#define CAN_Handle_hpp

// Imports
#include "main.h"

#ifdef BLUECAN
// MCP Imports
#include "CAN_MCP2515.h"

#define CSP 6

// Create CAN message struct called "msg"
// Init class with pin 6
CAN_MCP2515 guy(CSP);

// Initializes the SPI pins, CAN, and CS
void init_CAN() {
  Serial.println("Setting up MCP with CS pin " + String(CSP));
  SPI.begin();
  guy.begin(CAN_BPS_1000K);
}

// Sends through SPI
void send_CAN(uint16_t id, uint8_t *buf) {
  // This if statement just prevents the auto generated ids from fucking shit up
  if (id < 2048) {
    // This also doesn't work, so probably not related to how the message is
    // being sent here? Maybe wiring issue? Too stupid rn uint8_t
    // FUCK_THIS_BUF[8] = {0, 1, 2, 3, 254, 254, 0, 0}; guy.write(id, 0, 8,
    // FUCK_THIS_BUF);

    guy.write(id, 0, 8, buf);
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
  for (int i = 0; i < 4; i++) {
    fCAN.setMB((FLEXCAN_MAILBOX)i, RX, STD);
  }

  // Set every other mailbox to TX
  for (int i = 4; i < 64; i++) {
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
