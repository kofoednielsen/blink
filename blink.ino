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

float pk = 0.0067;
float dk = 0.0000057;

FastPID myPID(pk, 0, dk, 1000, 16, true);

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

long last = 0;

int loop_counter = 0; void loop() {
  last = micros();
  accelgyro.getRotation(&gx, &gy, &gz);

  int16_t calc_throttle = (elevator.getValue() - 500);
  //Serial.println(output);
  if (calc_throttle > 1000) {
    int16_t output = myPID.step(aileron.getValue() - 1500, gy);
    motor_1.writeMicroseconds(calc_throttle - output);
    motor_2.writeMicroseconds(calc_throttle + output);
  } else {
    motor_1.writeMicroseconds(1000);
    motor_2.writeMicroseconds(1000);
   }
  if (loop_counter++ % 200 == 0) {
    float tmp = ((float)throttle.getValue()-1000)/100000;
    if (tmp < 0) tmp = 0;
    myPID.configure(tmp, 0, dk, 1000, 16, true);
    Serial.print(tmp, 8);
    Serial.print("\t");
    Serial.println(micros()-last);
  }
  delayMicroseconds(150);
}
