#include <SoftwareSerial.h>
#include <Servo.h>

// ---------------- Bluetooth ----------------
SoftwareSerial BT(2, 3); // RX, TX

// ---------------- L298N Pins ----------------
int enA = 9, in1 = 8, in2 = 7;       // Left motors
int enB = 10, in3 = 12, in4 = 11;    // Right motors
int speedVal = 200;                  // Motor speed (0-255)

// ---------------- Servo ----------------
Servo myServo;
int servoPin = 13;
int servoPos = 90;   // Initial middle position
bool sweeping = false;   // state flag
int stepSize = 2;        // step per move
int leftLimit = 45;      // min angle
int rightLimit = 135;    // max angle
int stepDelay = 15;      // full speed delay (100%)

// ---------------- Setup ----------------
void setup() {
  Serial.begin(9600);
  BT.begin(9600);

  pinMode(enA, OUTPUT); pinMode(in1, OUTPUT); pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT); pinMode(in3, OUTPUT); pinMode(in4, OUTPUT);

  myServo.attach(servoPin);
  myServo.write(servoPos);

  Serial.println("Bluetooth Robot Ready!");
  stopMotors();
}

// ---------------- Motor Functions ----------------
void forward(){
  digitalWrite(in1,HIGH); digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH); digitalWrite(in4,LOW);
  analogWrite(enA,speedVal); analogWrite(enB,speedVal);
  Serial.println("Forward");
}

void backward(){
  digitalWrite(in1,LOW); digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW); digitalWrite(in4,HIGH);
  analogWrite(enA,speedVal); analogWrite(enB,speedVal);
  Serial.println("Backward");
}

void rotateLeft(){
  digitalWrite(in1,LOW); digitalWrite(in2,HIGH); // Left backward
  digitalWrite(in3,HIGH); digitalWrite(in4,LOW); // Right forward
  analogWrite(enA,speedVal); analogWrite(enB,speedVal);
  Serial.println("Rotate Left");
}

void rotateRight(){
  digitalWrite(in1,HIGH); digitalWrite(in2,LOW); // Left forward
  digitalWrite(in3,LOW); digitalWrite(in4,HIGH); // Right backward
  analogWrite(enA,speedVal); analogWrite(enB,speedVal);
  Serial.println("Rotate Right");
}

void frontLeft(){ // small left
  digitalWrite(in1,HIGH); digitalWrite(in2,LOW);
  digitalWrite(in3,LOW); digitalWrite(in4,LOW);
  analogWrite(enA,speedVal); analogWrite(enB,0);
  Serial.println("Front Left");
}

void frontRight(){ // small right
  digitalWrite(in1,LOW); digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH); digitalWrite(in4,LOW);
  analogWrite(enA,0); analogWrite(enB,speedVal);
  Serial.println("Front Right");
}

void stopMotors(){
  digitalWrite(in1,LOW); digitalWrite(in2,LOW);
  digitalWrite(in3,LOW); digitalWrite(in4,LOW);
  analogWrite(enA,0); analogWrite(enB,0);
  Serial.println("Stop");
}

// ---------------- Servo Functions ----------------
void startservo(){
  sweeping = true;
  Serial.println("Servo Sweep Started");
}

void stopservo(){
  sweeping = false;
  myServo.write(46); // hold at center
  Serial.println("Servo Sweep Stopped");
}

// ---------------- Main Loop ----------------
void loop(){
  // Bluetooth command check
  if(BT.available()){
    char cmd = BT.read();
    switch(cmd){
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': rotateLeft(); break;
      case 'R': rotateRight(); break;
      case 'S': stopMotors(); break;
      case '1': frontLeft(); break;
      case '2': frontRight(); break;

      case '0': startservo(); break; // start sweeping
      case '5': stopservo(); break;  // stop sweeping

      default: Serial.print("Unknown: "); Serial.println(cmd); break;
    }
  }
  // Run servo sweep if active
  if(sweeping){
    for(servoPos = leftLimit; servoPos <= rightLimit && sweeping; servoPos += stepSize){
      myServo.write(servoPos);
      delay(stepDelay);
      if(BT.available() && BT.read() == '5') stopservo();
    }
    for(servoPos = rightLimit; servoPos >= leftLimit && sweeping; servoPos -= stepSize){
      myServo.write(servoPos);
      delay(stepDelay);
      if(BT.available() && BT.read() == '5') stopservo();
    }
  }
}