/*
 * This is a prototype that replicates an obstacle avoiding car, this prorotype uses
 * a 4wd robot car that mimicks the car, an arduino microcontroller that mimicks the engine
 * and drive system.
 * Author : Elijah Echekwu
 * 
 */

#include <Servo.h>
#include <NewPing.h>

#define TRIGGER_PIN  A1
#define ECHO_PIN  A2
#define MAX_DISTANCE  200

#define MAX_SPEED 200;

Servo xservo;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int left = 50;
int right = 170;
int center = 110;

const int ENa = 5;
const int ENb = 3;
const int LF = 2;
const int LB = 4;
const int RF = 7;
const int RB = 6;


int distance = 100;
boolean forward_movement = false;

void setup() {
  pinMode(LF, OUTPUT);
  pinMode(LB, OUTPUT);
  pinMode(RF, OUTPUT);
  pinMode(RB, OUTPUT);
  pinMode(ENa, OUTPUT);
  pinMode(ENb, OUTPUT);

  xservo.attach(9);

  xservo.write(center);
  delay(2000);
  distance = cal_distance();
  delay(100);
  distance = cal_distance();
  delay(100);
  distance = cal_distance();
  delay(100);
  distance = cal_distance();
  delay(100);


}

void loop() {
  int L_dist = 0;
  int R_dist = 0;
  
  if (distance <=20){
    halt();
    delay(300);
    move_backward();
    delay(300);
    halt();
    delay(100);

    L_dist = seek_left_distance();
    delay(300);
    R_dist = seek_right_distance();
    delay(300);

    if (distance >= L_dist){
      turn_right();
      halt();
    }

    else{
      turn_left();
      halt();
    }

  }

  else{
    move_forward();
  }

  distance = cal_distance();

}

int cal_distance(){
  delay(50);
  int cm = sonar.ping_cm();
  if (cm== 0){
    cm = 250;
  }
  return cm;
}

int seek_left_distance(){
  xservo.write(left);
  delay(500);
  int distance = cal_distance();
  delay(100);
  xservo.write(center);
  return distance;
}

int seek_right_distance(){
  xservo.write(right);
  delay(500);
  int distance = cal_distance();
  delay(100);
  xservo.write(center);
  return distance;
}

void halt(){
  analogWrite(ENa, 0);
  analogWrite(ENb, 0);
}

void move_forward(){
  if(!forward_movement){
    
    forward_movement = true;
    
    digitalWrite(LF, HIGH);
    digitalWrite(LB, LOW);
    digitalWrite(RF, HIGH);
    digitalWrite(RB, LOW);
  }
}

void move_backward(){
  forward_movement = false;

  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
  
}

void turn_left(){
  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);

  delay(500);

  digitalWrite(LF, HIGH);
  digitalWrite(LB, LOW);
  digitalWrite(RF, LOW);
  digitalWrite(RB, HIGH);
}

void turn_right(){
  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);

  delay(500);

  digitalWrite(LF, LOW);
  digitalWrite(LB, HIGH);
  digitalWrite(RF, HIGH);
  digitalWrite(RB, LOW);
}
