//www.elegoo.com
//2016.12.12

/************************
Exercise the motor using
the L293D chip
************************/
#include "SR04.h"
#include <Servo.h>

#define ENABLE1 5
#define DIRA1 4
#define DIRB1 3

#define ENABLE2 11
#define DIRA2 10
#define DIRB2 9

#define TRIG_PIN 6
#define ECHO_PIN 7

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);

void rotateServo(int pos){
  myservo.write(pos);
}

void setup() {
  Serial.begin(9600);
  //---set pin direction
  pinMode(ENABLE1,OUTPUT);
  pinMode(DIRA1,OUTPUT);
  pinMode(DIRB1,OUTPUT);
  pinMode(ENABLE2,OUTPUT);
  pinMode(DIRA2,OUTPUT);
  pinMode(DIRB2,OUTPUT);
  Serial.begin(9600);
  myservo.attach(13);  // attaches the servo on pin 13 to the servo object
}

void loop() {
  long dist[5];
  for(int i = 0; i < 5; i++){
    delay(150);
    rotateServo( i*45 );
    delay(150);
    dist[i] = sr04.Distance();

  }
  decideDirection(dist);
  
}

void decideDirection(long dist[]){
  long min = dist[0];
  for(int i = 1; i <5 ;i++){
    if(min > dist[i])
      min = dist[i];
  }
  if(min < 30){
    stopCar();
  }else{
    startCar();
    goStraight(500);
  }
}

void stopCar(){
  digitalWrite(ENABLE1,LOW); // disable
  digitalWrite(ENABLE2,LOW); // disable
}

void startCar(){
  digitalWrite(ENABLE1,HIGH); // disable
  digitalWrite(ENABLE2,HIGH); // disable
  digitalWrite(DIRA1,LOW); //one way
  digitalWrite(DIRB1,LOW);
  digitalWrite(DIRA2,LOW); //one way
  digitalWrite(DIRB2,LOW);
} 

void goStraight(int _delay){
  analogWrite(ENABLE1,200);
  analogWrite(ENABLE2,200);
  digitalWrite(DIRA1,HIGH); //one way
  digitalWrite(DIRB1,LOW);
  digitalWrite(DIRA2,HIGH); //one way
  digitalWrite(DIRB2,LOW);
  delay(_delay);
}  
void rotateCarRight(int _delay){
  digitalWrite(DIRA1,LOW); //one way
  digitalWrite(DIRB1,HIGH);
  digitalWrite(DIRA2,HIGH); //one way
  digitalWrite(DIRB2,LOW);
  delay(_delay);
}
void rotateCarLeft(int _delay){
  digitalWrite(DIRA1,HIGH); //one way
  digitalWrite(DIRB1,LOW);
  digitalWrite(DIRA2,LOW); //one way
  digitalWrite(DIRB2,HIGH);
  delay(_delay);
}


