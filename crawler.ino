/*


Emily Lam, November 2016
*/

#include "application.h"
#include <math.h>

Servo wheels;                 // servo for turning the wheels
Servo esc;                    // not actually a servo, but controlled like one!
bool startup = true;          // used to ensure startup only happens once
int startupDelay = 1000;      // time to pause at each calibration step
int speedOffset = 2;          // speed incredment
int turnOffset = 15;          // turn increment
int speed = 90;               // default speed, neutral
int turn = 90;                // default turn, neutral

void setup(){
  Serial.begin(9600);
  Particle.function("forbackward", procFB);
  Particle.function("leftright", procLR);
  wheels.attach(D0);          // initialize wheel servo to Digital IO Pin #8
  esc.attach(D1);             // initialize ESC to Digital IO Pin #9
  calibrateESC();
  delay(200);
}

/* Calibrate the ESC by sending a high signal, then a low, then middle.*/
void calibrateESC(){
  esc.write(180);             // full backwards
  delay(startupDelay);
  esc.write(0);               // full forwards
  delay(startupDelay);
  esc.write(90);              // neutral
  delay(startupDelay);
  esc.write(90);              // reset the ESC to neutral (non-moving) value
}

// Main loop
void loop() {
  esc.write(speed);
  wheels.write(turn);
  Serial.print("Speed: ");
  Serial.println(speed);
  Serial.print("Turn: ");
  Serial.println(turn);
  delay(50);
}


int procFB(String rcvValue) {
  if (rcvValue == "back" && speed < 120 && speed >= 90) {
    speed = speed + speedOffset; }
  else if (rcvValue == "forward" && speed > 90) {
    speed = 90;
  }
  else if (rcvValue == "forward" && speed > 45) {
    speed = speed - speedOffset;
  }
  else if (rcvValue == "back" && speed < 90) {
    speed = 90;
  }
  return 1;
}

int procLR(String rcvValue) {
  if (rcvValue == "left" && turn < 120 && turn >= 90) {
    turn = turn + turnOffset; }
  else if (rcvValue == "right" && turn > 90) {
    turn = 90;
  }
  else if (rcvValue == "right" && turn > 45) {
    turn = turn - turnOffset;
  }
  else if (rcvValue == "left" && turn < 90) {
    turn = 90;
  }
  return 1;
}
