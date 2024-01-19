#include "s_Speed.hpp"

// Local vars
uint8_t speed_msg[8];
uint8_t sum;
uint8_t count;
uint32_t out_rpm;
float rpm;
unsigned long current_rpm_ROC;

// Wheel speed class
FreqMeasureMulti ws;

// Tells the lib to start reading pin 13 on the micro
void init_ws() { ws.begin(WSP); }

void ws_Update() {
  // Read value from PIN
  if (ws.available()) {
    // Read all the times it passed a tooth
    sum = sum + ws.read();

    //
    count = count + 1;

    // Get elapsed time
    current_rpm_ROC = millis();

    if (count > 1) {
      rpm = ws.countToFrequency(sum / count) * 60 / 18;

      // Reset working vars
      sum = 0;
      count = 0;
    }
  }

  out_rpm = (int)(rpm * 100);
}

// Function to actually read the boi
uint8_t *ws_Val() {
#ifdef DEBUG
  // Print the raw value
  Serial.print("RPM: ");
  Serial.println(out_rpm);
#endif // DEBUG

  // Cast the float to a byte array
  memcpy(speed_msg, &out_rpm, sizeof(out_rpm));

  // Return the calculated value or last value
  return speed_msg;
}
