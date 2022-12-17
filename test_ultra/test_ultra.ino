#include <NewPing.h>

#define TRIGGER_PIN  A1
#define ECHO_PIN  A2
#define MAX_DISTANCE  200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int distance ;
void setup() {
  Serial.begin(9600);

}

void loop() {
  distance = cal_distance();
  Serial.println(distance);
}

int cal_distance(){
  delay(50);
  int cm = sonar.ping_cm();
  if (cm== 0){
    cm = 250;
  }
  return cm;
}
