#include "s_Temps.hpp"

#ifdef TIRE_TEMP
// Local vars
Adafruit_MLX90640 mlx;
float frame[32 * 24];  // buffer for full frame of temperatures
uint8_t temp_msg[8];   // hold data for to return
uint16_t hold_plz;     // hold data for averaging
uint8_t other_hold[2]; // another hold for wacky array casting shit

// Function to set pin for other shit
void temps_I2C(uint8_t SDA, uint8_t SDL) {
  // Set wire speed to increase data rates
  Wire.setClock(1000000);

  // Start the boi
  mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire);

#ifdef DEBUG
  Serial.println("Tire temps enabled");
  if (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire)) {
    Serial.println("Temp module wants to die");
  }
#endif // DEBUG

  // Set the wire speed again because the adafruit library is wacky
  Wire.setClock(1000000);

  // Configure the boi
  mlx.setMode(MLX90640_CHESS);           // scanning mode
  mlx.setResolution(MLX90640_ADC_16BIT); // per cell depth
  mlx.setRefreshRate(MLX90640_32_HZ);    // refreshrate

#ifdef DEBUG
  Serial.println("Tire temps set");
#endif // DEBUG
}

// Function to actually read the boi
uint8_t *temps_IMO() {
  // Grab frame and check for valid data
  if (mlx.getFrame(frame) != 0) {
#ifdef DEBUG
    Serial.println("Failed to grab temps");
#endif // DEBUG
    // return last frame as fallback
    return temp_msg;
  }

  // Get a verticle strip of values of width 8 and height 32
  for (uint8_t w = 0; w < 8; w++) {
    for (uint8_t h = 0; h < 32; h++) {
      hold_plz += frame[w * 8 + h];
    }
  }
  // Average out the values
  hold_plz = hold_plz / 256;
  // Copy the value into an array of uint8_t's
  memcpy(other_hold, &(hold_plz), sizeof(hold_plz));
  // Copy the value of the array into the return message
  temp_msg[0] = other_hold[0];
  temp_msg[1] = other_hold[1];
  // Reset hold_plz
  hold_plz = 0;

  // And do it all again
  // I could try to cut down the amount of code by doing another for loop but
  // honestly with the amount of things akwardly incrementing and the time
  // crunch already, this will have to do... Please forgive me for thy sins
  for (uint8_t w = 9; w < 16; w++) {
    for (uint8_t h = 0; h < 32; h++) {
      hold_plz += frame[w * 8 + h];
    }
  }
  hold_plz = hold_plz / 256;
  memcpy(other_hold, &(hold_plz), sizeof(hold_plz));
  temp_msg[2] = other_hold[0];
  temp_msg[3] = other_hold[1];
  hold_plz = 0;

  // And one last time
  for (uint8_t w = 17; w < 24; w++) {
    for (uint8_t h = 0; h < 32; h++) {
      hold_plz += frame[w * 8 + h];
    }
  }
  hold_plz = hold_plz / 256;
  memcpy(other_hold, &(hold_plz), sizeof(hold_plz));
  temp_msg[4] = other_hold[0];
  temp_msg[5] = other_hold[1];
  hold_plz = 0;

  return temp_msg;
}
#endif // TIRE_TEMP
