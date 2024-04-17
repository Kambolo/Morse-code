#include <Arduino.h>
#include <string.h>

#define BUTTON 2

int startTime = 0;
int endTime = 0;

bool startStatus = false;
bool endStatus = false;

void getStartTime();
void getEndTime();

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop() {
  attachInterrupt(digitalPinToInterrupt(BUTTON), getStartTime, FALLING);
  attachInterrupt(digitalPinToInterrupt(BUTTON), getEndTime, RISING);
  if(startTime != 0 && endTime != 0){
    Serial.println(endTime - startTime);
    startStatus = false;
    endStatus = false;
    startTime = 0;
    endTime = 0;
  }

}

void getStartTime(){
  Serial.println("start");
  if(!startStatus){
      Serial.println("start");
      startTime = millis();
      startStatus = true;
  }
}

void getEndTime(){
   Serial.println("end");
    if(!endStatus){
      Serial.println("end");
      endTime = millis();
      endStatus = true;
  }
}
