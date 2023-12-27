#include "s_Temps.hpp"

// Local vars
Adafruit_MLX90640 mlx;
float frame[32 * 24]; // buffer for full frame of temperatures

// Function to set pin for other shit
void temps_I2C(uint8_t SDA, uint8_t SDL) {
  // Set wire speed to increase data rates
  Wire.setClock(1000000);

  // Wait for the module to respond
  while (!mlx.begin(MLX90640_I2CADDR_DEFAULT, &Wire))
    ;

  // Set the wire speed again because the adafruit library is wacky
  Wire.setClock(1000000);

  // Configure the boi
  mlx.setMode(MLX90640_CHESS);           // scanning mode
  mlx.setResolution(MLX90640_ADC_16BIT); // per cell depth
  mlx.setRefreshRate(MLX90640_32_HZ);    // refreshrate

#ifdef DEBUG
  Serial.println("Tire temps enabled");
#endif
}

// Function to actually read the boi
uint8_t *temps_ValO() {}
uint8_t *temps_ValM() {}
uint8_t *temps_ValI() {}
