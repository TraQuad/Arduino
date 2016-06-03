#include <Servo.h>

Servo rollServo, pitchServo, throttleServo, yawServo;
int rollPin = 6, pitchPin = 7, throttlePin = 8, yawPin = 9;

void setup() {
  pinMode(13,OUTPUT);

  pinMode(rollPin, OUTPUT);
  pinMode(pitchPin, OUTPUT);
  pinMode(throttlePin, OUTPUT);
  pinMode(yawPin, OUTPUT);

  rollServo.attach(rollPin);
  pitchServo.attach(pitchPin);
  throttleServo.attach(throttlePin);
  yawServo.attach(yawPin);
  
  Serial.begin(9600);
  
}

int throttlePWM, pitchPWM, yawPWM, rollPWM;
char serialData[16];
int limitCharacters = 16;
int throttlePWMstored, pitchPWMstored, yawPWMstored, rollPWMstored;
int valRoll, valPitch, valThrottle, valYaw;

void loop() {
  
  if(Serial.available()!=0)
  { Serial.readBytesUntil(limitCharacters, serialData, 16); }

  //Format: Throttle, Pitch, Yaw, Roll
  throttlePWM = 1000*(serialData[0] - '0') + 100*(serialData[1] - '0') + 10*(serialData[2] - '0') + (serialData[3] - '0');
  pitchPWM = 1000*(serialData[4] - '0') + 100*(serialData[5] - '0') + 10*(serialData[6] - '0') + (serialData[7] - '0');
  yawPWM = 1000*(serialData[8] - '0') + 100*(serialData[9] - '0') + 10*(serialData[10] - '0') + (serialData[11] - '0');
  rollPWM = 1000*(serialData[12] - '0') + 100*(serialData[13] - '0') + 10*(serialData[14] - '0') + (serialData[15] - '0');

  if((throttlePWM<1000)|(throttlePWM>2000)|(pitchPWM<1000)|(pitchPWM>2000)|(yawPWM<1000)|(yawPWM>2000)|(rollPWM<1000)|(rollPWM>2000)){
    throttlePWM = throttlePWMstored;  pitchPWM = pitchPWMstored;  yawPWM = yawPWMstored;  rollPWM = rollPWMstored;
  }else{
    throttlePWMstored = throttlePWM;  pitchPWMstored = pitchPWM;  yawPWMstored = yawPWM;  rollPWMstored = rollPWM;
  }

  //testLED(throttlePWM);
  //displayPWMvalues(serialData, throttlePWM, pitchPWM, yawPWM, rollPWM, 0);

  valRoll = 45 + (rollPWM - 1000)/11;
  valPitch = 45 + (pitchPWM - 1000)/11;
  valThrottle = 45 + (throttlePWM - 1000)/11;
  valYaw = 45 + (yawPWM - 1000)/11;
  
  rollServo.write(valRoll);
  pitchServo.write(valPitch);
  throttleServo.write(valThrottle);
  yawServo.write(valYaw);
  delay(20);  
}

void testLED(int PWM){
  int i;
  
  for(i=1000; i<PWM; i++){
    digitalWrite(13,HIGH);
  }
  
  for(i=PWM;i<2000;i++){
    digitalWrite(13,LOW);
  }
  
  return;
  
}

void displayPWMvalues(char serialData[16], int throttlePWM, int pitchPWM, int yawPWM, int rollPWM, int onOff){
  if(onOff==1){
      Serial.println("");
      Serial.print(serialData);
      Serial.print(" Throttle: "); Serial.print(throttlePWM);
      Serial.print(", Pitch: "); Serial.print(pitchPWM);
      Serial.print(", Yaw: "); Serial.print(yawPWM);
      Serial.print(", Roll: "); Serial.print(rollPWM);
  }
  return;
}

