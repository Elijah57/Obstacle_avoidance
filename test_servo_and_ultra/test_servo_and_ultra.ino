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
int distance = 100;
void setup() {

  Serial.begin(9600);
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
  
  L_dist = seek_left_distance();
  Serial.print(L_dist);
  delay(300);
  R_dist = seek_right_distance();
  Serial.print(R_dist);
  delay(300);


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
