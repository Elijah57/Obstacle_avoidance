#include <Servo.h>

Servo xservo;


int left = 50;
int right = 170;
int center = 110;

void setup() {
  xservo.attach(9);

  xservo.write(center);
}

void loop() {
  xservo.write(center);
  delay(300);
  xservo.write(left);
  delay(500)
  xservo.write(right);
  delay(500);

}
