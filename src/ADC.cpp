#include "ADC.hpp"

// Local vars
Adafruit_ADS1115 ads; // Class for the 16 bit version

void init_ADC() {
  if (!ads.begin()) {
#ifdef DEBUG
    Serial.println("Failed to init ADC");
#endif
  }

#ifdef DEBUG
  Serial.println("ADC enabled");
#endif
}
