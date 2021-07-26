#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <RcChannel.h>
// #include <Servo.h>

MPU6050 accelgyro;

int16_t gx, gy, gz;

// servo motor_1;
// servo motor_2;
// servo motor_3;
// servo rudder; 

void setup() {
  Wire.begin();

  accelgyro.initialize();

  // use the code below to change accel/gyro offset values
  accelgyro.setXGyroOffset(-43);
  accelgyro.setYGyroOffset(33);
  accelgyro.setZGyroOffset(-28);

  // Setup receiver channels with default min, mid & max (1000, 1500, 1900)
  RcChannel rc[] = {1, 2, 3, 4};

  // aileron.attach(5);
  // aileron.writeMicroseconds(1500);
  // elevator.attach(6);
  // elevator.writeMicroseconds(1500);
  // throttle.attach(7);
  // throttle.writeMicroseconds(1500);
  // rudder.attach(8);
  // rudder.writeMicroseconds(1500);

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

    aileron_percentage = rc[1].readPercentage();
    elevator_percentage = rc[2].readPercentage();
    throttle_percentage = rc[3].readPercentage();
    rudder_percentage = rc[4].readPercentage();

    Serial.print(aileron_percentage);
    Serial.print("\t");
    Serial.print(elevator_percentage);
    Serial.print("\t");
    Serial.print(throttle_percentage);
    Serial.print("\t");
    Serial.print(rudder_percentage);

    last_time = micros();
}
