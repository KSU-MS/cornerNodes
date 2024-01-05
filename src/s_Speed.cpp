#include "s_Speed.hpp"

// Local vars
uint8_t speed_PIN;
uint8_t speed_msg[8];
double sum;
int count;
float freq;

// Tells the lib to start reading pin 13 on the micro
void init_WSPD() { FreqMeasure.begin(); }

void speed_Up() {
  // Read value from PIN
  if (FreqMeasure.available()) {
    sum += FreqMeasure.read();
    count++;

    if (count > 30) {
      // Use FreqMeasure built in converions funcs
      freq = FreqMeasure.countToFrequency(sum / count);

      // Reset working vars
      sum = 0;
      count = 0;
    }
  }
}

// Function to actually read the boi
uint8_t *speed_Val() {
#ifdef DEBUG
  // Print the raw value
  Serial.print("Freq: ");
  Serial.println(freq);
#endif // DEBUG

  // Cast the float to a byte array
  memcpy(speed_msg, &freq, sizeof(freq));

  // Return the calculated value or last value
  return speed_msg;
}
