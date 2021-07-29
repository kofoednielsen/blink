#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <Servo.h>
#include "PWM.hpp"
#include <FastPID.h>
MPU6050 accelgyro;

int16_t gx, gy, gz;

Servo motor_1;
Servo motor_2;
// servo motor_3;
// servo motor_4;

PWM aileron(1);
PWM elevator(2);
PWM throttle(3);
PWM rudder(4);

FastPID myPID(10, 0, 0, 1000, 16, true);

void setup() {
  Wire.begin();

  myPID.setOutputRange(-200, 200);

  accelgyro.initialize();

  // use the code below to change accel/gyro offset values
  accelgyro.setXGyroOffset(-43);
  accelgyro.setYGyroOffset(33);
  accelgyro.setZGyroOffset(-28);

  // Setup receiver channels
  aileron.begin(true);
  elevator.begin(true);
  throttle.begin(true);
  rudder.begin(true);

  motor_1.attach(5);
  motor_1.writeMicroseconds(1000);
  motor_2.attach(6);
  motor_2.writeMicroseconds(1000);
  // motor_3.attach(7);
  // motor_3.writeMicroseconds(1500);
  // motor_4.attach(8);
  // motor_4.writeMicroseconds(1500);
}

unsigned long last_time = 0;
int16_t delta_t = 0;
int16_t x = 0;
int16_t y = 0;
int16_t z = 0;

long last = = micros();
void loop() {
  accelgyro.getRotation(&gx, &gy, &gz);
  y = gy/131.7;

  int16_t output = myPID.step(0, y);
  //Serial.println(output);
  if (throttle.getValue() > 1000) {
    motor_1.writeMicroseconds(throttle.getValue() - output);
    motor_2.writeMicroseconds(throttle.getValue() + output);
  } else {
    myPID.clear();
    motor_1.writeMicroseconds(1000);
    motor_2.writeMicroseconds(1000);
   }
  Serial.println(micros()-last);
  delay(1);
}
