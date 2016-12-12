#include <IRremote.h>
#include <Servo.h>

int RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define POWER 0x10EFD827 
#define A 0x10EFF807 
#define B 0x10EF7887
#define C 0x10EF58A7
#define UP 0x10EFA05F
#define DOWN 0x10EF00FF
#define LEFT 0x10EF10EF
#define RIGHT 0x10EF807F
#define SELECT 0x10EF20DF

int lightPin = 8;
const int motor1Pin = 3; // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4; // H-bridge leg 2 (pin 7, 2A)
const int motor3Pin = 5;
const int motor4Pin = 6;
const int motor5Pin=12;
const int motor6Pin=11;
const int enablePin = 9; // H-bridge enable pin
bool motForward;
bool motBack;
bool motLeft;
bool motRight;

//Servo myservo;
Servo theServo;
int potpin=0;
int valMotor;
bool armDown=false;

void setup()
{
Serial.begin(9600);
irrecv.enableIRIn(); // Start the receiver

pinMode(lightPin, OUTPUT);

pinMode(motor1Pin, OUTPUT);
pinMode(motor2Pin, OUTPUT);
pinMode(motor3Pin, OUTPUT);
pinMode(motor4Pin, OUTPUT);
pinMode(motor5Pin, OUTPUT);
pinMode(motor6Pin, OUTPUT);
pinMode(enablePin, OUTPUT);

digitalWrite(enablePin, LOW);
motForward=false;
motBack=false;
motLeft=false;
motRight=false;

//wheel axis servo
// myservo.attach(11);
//myservo.write(90);

//arm servo
theServo.attach(10);
theServo.write(90);
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == POWER) {
      Serial.println("POWER");
      motForward=false;
      motBack=false;
      motLeft=false;
      motRight=false;
      armDown=true;
      digitalWrite(lightPin,LOW); 
    }
    if (results.value == A){
      Serial.println("A");
      digitalWrite(lightPin, HIGH);
    }
    if (results.value == B) {
      Serial.println("B");
      digitalWrite(lightPin, LOW);
    }
    if (results.value == C) {
      Serial.println("C");
      if(armDown==true){
      armDown=false;
      }
      else{
        armDown=true;
      }
   }
    if(armDown==true){
      theServo.write(90);
      delay(50);
    }
    if(armDown==false){
      theServo.write(150);
    }
    if (results.value == UP){
      Serial.println("UP");
      if(motForward==true){
        Serial.println("forward true");
        motForward=false;
      }
      else{
        Serial.println("forward false");
        motForward=true;
      }
    }
    if(motForward==true){
      Serial.println("in forward motion");
      motBack=false;
      motRight=false;
      motLeft=false;
      digitalWrite(enablePin,HIGH);
      digitalWrite(motor1Pin, HIGH);
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, HIGH);
      digitalWrite(motor4Pin, LOW);
      digitalWrite(motor5Pin, HIGH);
      digitalWrite(motor6Pin, LOW);
      //myservo.write(90);
    }
    if (results.value == DOWN) {
      Serial.println("DOWN");
      if(motBack==true){
        motBack=false;
      }
      else{
        motBack=true;
      }
    }
    if(motBack==true){
      //myservo.write(90);
      motForward=false;
      motLeft=false;
      motRight=false;
      digitalWrite(enablePin,HIGH);
      digitalWrite(motor2Pin, HIGH);
      digitalWrite(motor1Pin, LOW);
      digitalWrite(motor6Pin, HIGH);
      digitalWrite(motor5Pin, LOW);
      digitalWrite(motor4Pin, HIGH);
      digitalWrite(motor3Pin, LOW);

    }
    
    if (results.value == LEFT) {
      Serial.println("LEFT");
      if(motLeft==true){
        motLeft=false;
      }
      else{
        motLeft=true;
      }
    
    }
    if(motLeft==true){
      //myservo.write(45);
      Serial.println("as expected");
      motForward=false;
      motBack=false;
      motRight=false;
      digitalWrite(enablePin,HIGH);
      digitalWrite(motor1Pin, LOW);
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, HIGH);
      digitalWrite(motor4Pin, LOW);
      digitalWrite(motor5Pin, LOW);
      digitalWrite(motor6Pin, LOW);
    }
     if (results.value == RIGHT) {
       Serial.println("RIGHT");
       if(motRight==true){
       motRight=false;
       }
       else{
         motRight=true;
       }
    }
    if(motRight==true){
      //myservo.write(135);
      motForward=false;
      motBack=false;
      motLeft=false;
      digitalWrite(enablePin,HIGH);
      digitalWrite(motor1Pin, HIGH);
      digitalWrite(motor2Pin, LOW);
      digitalWrite(motor3Pin, LOW);
      digitalWrite(motor4Pin, LOW);
      digitalWrite(motor5Pin, HIGH);
      digitalWrite(motor6Pin, LOW);
    }
    if(motBack==false && motForward==false && motLeft==false && motRight==false){
      digitalWrite(enablePin, LOW);
    }
    if (results.value == SELECT){
      Serial.println("SELECT");
    }
    irrecv.resume();
  }
}
