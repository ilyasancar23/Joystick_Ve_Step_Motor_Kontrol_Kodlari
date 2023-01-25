#include <Stepper.h>

const int steps_per_rev = 200; //Set to 200 for NIMA 17
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6

Stepper motor(steps_per_rev, IN1, IN2, IN3, IN4);

void setup()
{
  motor.setSpeed(100);
  Serial.begin(115200);
  pinMode(enableAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void loop()
{
  int motorPWMSpeed = 0;
  int joystickValue = analogRead(A0);   //Joystick gives values ranging from 0 to 1023. So we will consider center value as 512 and lets keep some deadband at center.

  if (joystickValue >= 530)           //This will move motor in forward direction  
  {
    motorPWMSpeed = map(joystickValue, 530, 1023, 0, 255);
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);    
    analogWrite(enableAPin, motorPWMSpeed);
  }
  else if (joystickValue <= 490)      //This will move motor in reverse direction    
  {
    motorPWMSpeed = map(joystickValue, 490, 0, 0, 255);
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);    
    analogWrite(enableAPin, motorPWMSpeed);
  }  
  else                                //Stop the motor
  {
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, LOW);    
  }
}
