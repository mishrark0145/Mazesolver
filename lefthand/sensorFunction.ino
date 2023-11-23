#include <Servo.h>
#include "robotDefines.h"

String command;
String device;
  
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  // line follow sensors
  pinMode(lineFollowSensor0, INPUT);
  pinMode(lineFollowSensor1, INPUT);
  pinMode(lineFollowSensor2, INPUT);
  pinMode(lineFollowSensor3, INPUT);
  pinMode(lineFollowSensor4, INPUT);
  
  // servos
  leftServo.attach(5);
  rightServo.attach(3);
  
  BT1.print("check the PID constants to be sent to Robot");
  BT1.println('\n');

  
  
  
  while (digitalRead(buttonPin) && !mode)
  {  
    checkBTcmd();  // verify if a comand is received from BT remote control
    manualCmd ();    
    command = "";  
  }
  
  motorFwTime (3000);
  
  checkPIDvalues();
  mode = STOPPED;
}

void loop() 
{
  readLFSsensors();  
  switch (mode)
  {   
    case NO_LINE:  
      motorStop();
      goAndTurn (LEFT, 180);
      break;
    
    case CONT_LINE: 
      runExtraInch();
      readLFSsensors();
      if (mode == CONT_LINE) mazeEnd();
      else goAndTurn (LEFT, 90);  // or it is a "T" or "Cross"). In both cases, goes to LEFT 
      break;
      
   case RIGHT_TURN: 
      runExtraInch();
      readLFSsensors();
      if (mode == NO_LINE) goAndTurn (RIGHT, 90); 
      break;   
      
   case LEFT_TURN: 
      goAndTurn (LEFT, 90); 
      break;   
   
   case FOLLOWING_LINE: 
      followingLine();
      break;      
      
  }
}


