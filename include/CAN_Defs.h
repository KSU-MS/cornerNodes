#ifndef CAN_Defs_h
#define CAN_Defs_h

#include <Arduino.h>

// From the spec
#define CAN_DOMINANT 0
#define CAN_RECESSIVE 1

// Standard and Extended ID defines
#define CAN_STANDARD_FRAME 0
#define CAN_EXTENDED_FRAME 1

// For an 11 bit standard frame ID within a 16 bit variable, the first 5
// bits [15:11] are ignored
#define CAN_STANDARD_ID_MASK 0x07FF

// For a 29 bit extended frame ID within a 32 bit variable, the first 3
// bits [31:29] are ignored
#define CAN_EXTENDED_ID_MASK 0x1FFFFFFF

// Define the typical bitrate for CAN communication in kbps.
#define CAN_BPS_1M 1000000
#define CAN_BPS_1000K 1000000
#define CAN_BPS_800K 800000
#define CAN_BPS_500K 500000
#define CAN_BPS_250K 250000
#define CAN_BPS_200K 200000
#define CAN_BPS_125K 125000
#define CAN_BPS_100K 100000
#define CAN_BPS_83K 83333 // According to ARINC 825, this is a thing
#define CAN_BPS_80K 80000
#define CAN_BPS_50K 50000
#define CAN_BPS_40K 40000
#define CAN_BPS_33333 33333
#define CAN_BPS_31K25 31250
#define CAN_BPS_25K 25000
#define CAN_BPS_20K 20000
#define CAN_BPS_10K 10000
#define CAN_BPS_5K 5000

// ISO 11783-3:2014
// Section 5.13.3
// Controller response time and timeout defaults
#define CAN_TIMEOUT_TR 200
#define CAN_TIMEOUT_TH 500
#define CAN_TIMEOUT_T1 750
#define CAN_TIMEOUT_T2 1250
#define CAN_TIMEOUT_T3 1250
#define CAN_TIMEOUT_T4 1050

// The Blue CAN chip controller
#define CAN_CONTROLLER_MCP2515

typedef struct __attribute__((__packed__)) {
  uint32_t id : 29; // if (ide == CAN_RECESSIVE) { extended ID }
  //   else { standard ID }
  uint8_t valid : 1;     // To avoid passing garbage frames around
  uint8_t rtr : 1;       // Remote Transmission Request Bit (RTR)
  uint8_t extended : 1;  // Identifier Extension Bit (IDE)
  uint32_t fid;          // family ID
  uint8_t priority : 4;  // Priority but only important for TX frames and then
                         // only for special uses.
  uint8_t length : 8;    // Data Length
  uint16_t timeout;      // milliseconds, zero will disable waiting
  uint8_t data[8] = {0}; // Message data
} CAN_Frame;             // suffix of '_t' is reserved by POSIX for future use

typedef struct __attribute__((__packed__)) {
  uint32_t id : 29; // if (ide == CAN_RECESSIVE) { extended ID }
  //   else { standard ID }
  uint8_t rtr : 1;      // Remote Transmission Request Bit (RTR)
  uint8_t extended : 1; // Identifier Extension Bit (IDE)
  uint8_t data[2];      // Filter / Mask for message data
} CAN_Filter;           // suffix of '_t' is reserved by POSIX for future use

class CANClass // Can't inherit from Stream
{
public:
  virtual void begin(uint32_t bitrate);
  virtual void end();
  virtual uint8_t available();
  virtual CAN_Frame read();
  virtual void flush();
  virtual uint8_t write(const CAN_Frame &);

  // CAN_Frame& operator=(const CAN_Frame&);
};

#endif // _CAN_H_
