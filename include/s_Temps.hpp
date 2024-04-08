#ifndef Temps_hpp
#define Temps_hpp

#include "main.hpp"

#ifdef TIRE_TEMP
// Imports
#include <Adafruit_MLX90640.h>
#include <Arduino.h>

class Tire_Temp {
  // uint8_t offset;
  uint8_t temp_msg[8];
  float frame[32 * 24];
  Adafruit_MLX90640 mlx;

  union {
    uint16_t in;
    byte b[2];
  } average;

public:
  void init();
  // void update();
  uint8_t *getMessage();
};

void Tire_Temp::init() {
  // Set wire speed to increase data rates
  Wire.setClock(1000000);

  // Start the boi
  if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire1)) {
    Serial.println("Temp module wants to die");
  }

  // Set the wire speed again because the adafruit library is wacky
  Wire.setClock(1000000);

  // Configure the boi
  mlx.setMode(MLX90640_CHESS);           // scanning mode
  mlx.setResolution(MLX90640_ADC_16BIT); // per cell depth
  mlx.setRefreshRate(MLX90640_32_HZ);    // refreshrate

  Serial.println("Tire temps enabled & configured");
}

// void Tire_Temp::update() {}

uint8_t *Tire_Temp::getMessage() {
  // Grab frame and check for valid data, or return last frame as fallback
  if (mlx.getFrame(frame) != 0) {
#ifdef DEBUG
    Serial.println("Failed to grab temps");
#endif // DEBUG

    return temp_msg;
  }

  // Get a verticle strip of values of width 8 and height 32
  for (uint8_t w = 0; w < 9; w++) {
    for (uint8_t h = 0; h < 32; h++) {
      average.in += frame[w * 8 + h];
    }
  }
  // Average out the values
  average.in /= 256;

  // Copy the value of the array into the return message
  temp_msg[0] = average.b[0];
  temp_msg[1] = average.b[1];
  // Reset hold_plz
  average.in = 0;

  // And do it all again
  // I could try to cut down the amount of code by doing another for loop but
  // honestly with the amount of things akwardly incrementing and the time
  // crunch already, this will have to do... Please forgive me for thy sins
  for (uint8_t w = 9; w < 17; w++) {
    for (uint8_t h = 0; h < 32; h++) {
      average.in += frame[w * 8 + h];
    }
  }
  temp_msg[2] = average.b[0];
  temp_msg[3] = average.b[1];
  average.in = 0;

  // And one last time
  for (uint8_t w = 17; w < 25; w++) {
    for (uint8_t h = 0; h < 32; h++) {
      average.in += frame[w * 8 + h];
    }
  }
  temp_msg[4] = average.b[0];
  temp_msg[5] = average.b[1];
  average.in = 0;

  return temp_msg;
}

#endif // TIRE_TEMP
#endif // Temps_hpp
