#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t gx, gy, gz;

void setup() {
  Wire.begin();

  accelgyro.initialize();

  // use the code below to change accel/gyro offset values
  accelgyro.setXGyroOffset(-43);
  accelgyro.setYGyroOffset(33);
  accelgyro.setZGyroOffset(-28);
}

unsigned long last_time = 0;
int16_t delta_t = 0;

void loop() {
    accelgyro.getRotation(&gx, &gy, &gz);

    delta_t = micros()-last_time;
    Serial.write((uint8_t)(gx & 0xFF)); Serial.write((uint8_t)(gx >> 8));
    Serial.write((uint8_t)(gy & 0xFF)); Serial.write((uint8_t)(gy >> 8)); 
    Serial.write((uint8_t)(gz & 0xFF)); Serial.write((uint8_t)(gz >> 8));
    Serial.write((uint8_t)(delta_t & 0xFF)); Serial.write((uint8_t)(delta_t >> 8));

    // fly

    last_time = micros();
}
