#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
// #include "RCReceive.h"
#include <Servo.h>

MPU6050 accelgyro;

int16_t gx, gy, gz;

Servo motor_1;
Servo motor_2;
// servo motor_3;
// servo motor_4;

// RCReceive aileron;
// RCReceive elevator;
// RCReceive throttle;
// RCReceive rudder;

void setup() {
  Wire.begin();

  accelgyro.initialize();

  // use the code below to change accel/gyro offset values
  accelgyro.setXGyroOffset(-43);
  accelgyro.setYGyroOffset(33);
  accelgyro.setZGyroOffset(-28);

  // Setup receiver channels with default min, mid & max (1000, 1500, 1900)
  // aileron.attachInt(1);
  // elevator.attachInt(2);
  // throttle.attachInt(3);
  // rudder.attachInt(4);

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

void loop() {
    accelgyro.getRotation(&gx, &gy, &gz);

    delta_t = micros()-last_time;
    
    // byte aileron_pwm = aileron.getValue();
    // byte elevator_pwm = elevator.getValue();
    // byte throttle_pwm = throttle.getValue();
    // byte rudder_pwm = rudder.getValue();

    // Serial.print(aileron_pwm);
    // Serial.print("\t");
    // Serial.print(elevator_pwm);
    // Serial.print("\t");
    // Serial.print(throttle_pwm);
    // Serial.print("\t");
    // Serial.print(rudder_pwm);
    Serial.println("Code is actually running.");

    motor_1.writeMicroseconds(1000);
    motor_2.writeMicroseconds(1000);

    last_time = micros();
}
