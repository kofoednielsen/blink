#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"
#include <Servo.h>
#include "PWM.hpp"

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

void setup() {
  Wire.begin();

  accelgyro.initialize();

  // use the code below to change accel/gyro offset values
  accelgyro.setXGyroOffset(-43);
  accelgyro.setYGyroOffset(33);
  accelgyro.setZGyroOffset(-28);

  // Setup receiver channels
  aileron.begin(true)
  elevator.begin(true)
  throttle.begin(true)
  rudder.begin(true)

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
    
    Serial.print(aileron.getValue());
    Serial.print("\t");
    Serial.print(elevator.getValue());
    Serial.print("\t");
    Serial.print(throttle.getValue());
    Serial.print("\t");
    Serial.print(rudder.getValue());

    motor_1.writeMicroseconds(throttle.getValue());
    motor_2.writeMicroseconds(throttle.getValue());

    last_time = micros();
}
