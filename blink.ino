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
Servo motor_3;
Servo motor_4;

PWM aileron(1);
PWM elevator(2);
PWM throttle(3);
PWM rudder(4);

float pk = 0.0050;
float dk = 0.0000057;

FastPID xPID(pk, 0, dk, 1000, 16, true);
FastPID yPID(pk, 0, dk, 1000, 16, true);

void setup() {
  Wire.begin();

  xPID.setOutputRange(-200, 200);
  yPID.setOutputRange(-200, 200);

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

  motor_1.attach(8);
  motor_2.attach(5);
  motor_3.attach(6);
  motor_4.attach(7);
}

long last = 0;

int loop_counter = 0; void loop() {
  last = micros();
  accelgyro.getRotation(&gx, &gy, &gz);

  // int16_t x_output = xPID.step((elevator.getValue()-1500)*30, gx);
  // int16_t y_output = yPID.step((aileron.getValue()-1500)*30, gy);
  // motor_1.writeMicroseconds(throttle.getValue() + y_output + x_output);
  // motor_2.writeMicroseconds(throttle.getValue() - y_output + x_output);
  // motor_3.writeMicroseconds(throttle.getValue() + y_output - x_output);
  // motor_4.writeMicroseconds(throttle.getValue() - y_output - x_output);

  motor_1.writeMicroseconds(throttle.getValue());
  motor_2.writeMicroseconds(throttle.getValue());
  motor_3.writeMicroseconds(throttle.getValue());
  motor_4.writeMicroseconds(throttle.getValue());

  if (loop_counter++ % 10 == 0) {
    Serial.print((int)aileron.getValue() - 1500);
    Serial.print("\t");
    Serial.print((int)elevator.getValue() - 1500);
    Serial.print("\t");
    Serial.println(micros()-last);
  }
  delayMicroseconds(150);
}
