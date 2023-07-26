#include  <Servo.h>

// Create servo objects
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

// Create names to the analog input pins
int pin0 = A0;
int pin1 = A1;
int pin2 = A2;
int pin3 = A3;

// Setup of angle variables we have to use further down in the program
int angle1;
int angle2;
int angle3;
int angle4;

// Setup of value variables we have to use further down in the program
int value1;
int value2;
int value3;
int value4;

// Setup of limit values
long int forservo1 = 20100;
long int forservo2 = 19800;
long int forservo3 = 22300;
long int forservo4 = 20000;

void setup() {
  //Serial.begin(9600);   // 시리얼 통신 시작 (시리얼 모니터용)

  // Attaches the servo on pins to the servo objects
  servo1.attach(9);
  servo2.attach(6);
  servo3.attach(5);
  servo4.attach(3);
  
  //Serial.println("meArm with Joystick");
} 
 
void loop() {
  // read analog values from joysticks
  value1 = analogRead(pin0);
  value2 = analogRead(pin1);
  value3 = analogRead(pin2);
  value4 = analogRead(pin3);
  
  // 10 bit value is too big, so we change the scale from 0 - 1023 proportionately to 1 - 29
  value1 = map(value1, 0, 1023, 1, 29);
  value2 = map(value2, 0, 1023, 1, 29);
  value3 = map(value3, 0, 1023, 1, 29);
  value4 = map(value4, 0, 1023, 1, 29);
  
  // it needs correction of positions, because joysticks are not very precise to stay exactly in the center
  // if value1 if between 13-17, then it's equal to 15
  if(value1  <= 17 && value1 >= 13) value1 = 15;
  if(value2  <= 17 && value2 >= 13) value2 = 15;
  if(value3  <= 17 && value3 >= 13) value3 = 15;
  if(value4  <= 17 && value4 >= 13) value4 = 15;
    
  // Change initial value 'forservo' which is used to turn servo slower. This value has got very big scale.
  // We add or substract (depends on turning direction) difference between analog value and center from 'forservo'
  forservo1 = forservo1 - (value1 - 15);
  forservo2 = forservo2 - (value2 - 15);
  forservo3 = forservo3 + (value3 - 15);
  forservo4 = forservo4 + (value4 - 15);
  
  // forservo 변수가 최소치와 최대치를 넘어 가지 못 하게 함
  if(forservo1  < 1)     forservo1 = 1;     // if forservo1 is less than 1, then it's equal to 1
  if(forservo1  > 40000) forservo1 = 40000; // if forservo1 is greater than 20000, then it's equal to 20000
  if(forservo2  < 1)     forservo2 = 1;
  if(forservo2  > 40000) forservo2 = 40000;
  if(forservo3  < 1)     forservo3 = 1;
  if(forservo3  > 40000) forservo3 = 40000;
  if(forservo4  < 1)     forservo4 = 1;
  if(forservo4  > 20000) forservo4 = 20000;
  
  // forservo 값을 서보 모터 각도 값으로 매핑함. Angles are adjusted during testing 
  angle1 = map(forservo1, 1, 40000, 180, 10);
  angle2 = map(forservo2, 1, 40000, 180, 8);
  angle3 = map(forservo3, 1, 40000, 170, 4);
  angle4 = map(forservo4, 1, 20000, 90, 0);
  
  // send angles to servos 
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);

  //Serial.print(angle1); Serial.print("\t"); Serial.print(angle2); Serial.print("\t"); Serial.print(angle3); Serial.print("\t"); Serial.print(angle4); Serial.print("\t");
  //Serial.print(forservo1); Serial.print("\t"); Serial.print(forservo2); Serial.print("\t"); Serial.print(forservo3); Serial.print("\t"); Serial.println(forservo4);
}