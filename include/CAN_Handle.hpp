#ifndef CAN_Handle_hpp
#define CAN_Handle_hpp
#include "main.hpp"
#include "mcp_can_dfs.h"

#ifdef BLUECAN
#include <SPI.h>
#include <mcp_can.h>

// Start the MCP with CS pin 6
#define CSP 6
MCP_CAN CAN(CSP);

void init_CAN() {
  pinMode(CSP, OUTPUT);
  digitalWrite(CSP, HIGH);

  Serial.printf("Init MCP2515 on pin %d\n", CSP);
  CAN.begin(MCP_ANY, CAN_1000KBPS, MCP_8MHZ);
  // Change to normal mode to allow messages to be transmitted
  CAN.setMode(MCP_NORMAL);
}

// For some fucking reason if I try to use size of in this function it will
// return a straight up fucking false number and I have no fucking clue why
void send_CAN(uint16_t id, int len, uint8_t buf[]) {
  CAN.sendMsgBuf(id, len, buf);
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
