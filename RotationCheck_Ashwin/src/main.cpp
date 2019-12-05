/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Neelay Joglekar                                  */
/*    Created:      Wed Dec 04 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller  Controller;
// A global instance of vex::competition
vex::competition Competition;

// define your global instances of motors and other devices here
vex::motor LeftMotor = vex::motor(PORT16);//left motor for movement
vex::motor RightMotor = vex::motor(PORT2, true);//right motor for movement
vex::motor LeftArmMotor = vex::motor(PORT3);//left motor to raise arm
vex::motor RightArmMotor = vex::motor(PORT4, true);//right motor to raise arm
vex::motor LeftIntake = vex::motor(PORT5);//if r1 and r2 are  not pressed, intake spins continous; if r1 intake stops; if r1+r2, reverse.
vex::motor RightIntake = vex::motor(PORT6, true);//left intake and right intake motors are the spinning mechanism that captures the cubes
vex::motor PushupBar = vex::motor(PORT7);//

bool x = true;

void checkRotation( void ){
  if(Controller.ButtonR1.pressing()){
    LeftMotor.stop();
    LeftMotor.setVelocity(0, velocityUnits::pct);
    //RightMotor.setVelocity(0, velocityUnits::pct);

    //Brain.Screen.print("Right Motor rotation: ");
    //Brain.Screen.print(RightMotor.rotation(rotationUnits::deg));
    //Brain.Screen.newLine();
    x = false;
  }
}

int main(){
  while(1){
    LeftMotor.spin(directionType::rev,5, velocityUnits::pct);
    while (x){
      //RightMotor.spin(directionType::rev,5, velocityUnits::pct);
      if(Controller.ButtonR1.pressing()){
        //LeftMotor.stop();
        LeftMotor.setVelocity(0, velocityUnits::pct);
        break;
      }
    }
    Brain.Screen.print("Motor rotation: ");
    Brain.Screen.print(LeftMotor.rotation(rotationUnits::deg));
    Brain.Screen.newLine();
  }
}

