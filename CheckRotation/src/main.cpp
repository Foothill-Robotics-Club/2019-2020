/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Neelay Joglekar                                  */
/*    Created:      Tue Sep 03 2019                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/
#include "vex.h"

using namespace vex;

// A global instance of vex::brain used for printing to the V5 brain screen
vex::brain       Brain;
vex::controller  Controller;

// define your global instances of motors and other devices here
vex::motor LeftMotor = vex::motor(PORT1);//left motor for movement
vex::motor RightMotor = vex::motor(PORT2, true);//right motor for movement
vex::motor LeftArmMotor = vex::motor(PORT3);//left motor to raise arm
vex::motor RightArmMotor = vex::motor(PORT4, true);//right motor to raise arm
vex::motor LeftIntake = vex::motor(PORT5);//if r1 and r2 are  not pressed, intake spins continous; if r1 intake stops; if r1+r2, reverse.
vex::motor RightIntake = vex::motor(PORT6, true);//left intake and right intake motors are the spinning mechanism that captures the cubes
vex::motor PushupBar = vex::motor(PORT7);//

bool notEnded = true;


int main() {

  Brain.Screen.print("CHECK ROTATION HAS BEGUN");
  Brain.Screen.newLine();

  //task::sleep(2000);

  LeftMotor.resetRotation();//left morotor reset rotation
  RightMotor.resetRotation();//right motor reset rotation
  
  LeftMotor.setVelocity(5, velocityUnits::pct);//left motor set velocity at 5pct
  RightMotor.setVelocity(5, velocityUnits::pct);//right motor set velocity at 5pct
  //+ Controller.Axis4.value())/2
  //- Controller.Axis4.value())/2,
  
  LeftIntake.spin(directionType::fwd);//left intake motor set spin direction forward
  RightIntake.spin(directionType::fwd);//right intake motor set spin direction forward

  LeftIntake.setVelocity(50, velocityUnits::pct);//left intake motor set velocity to 50pct
  RightIntake.setVelocity(50, velocityUnits::pct);//right intake motor set velcoity to 50pct

  while (notEnded){
        LeftIntake.setVelocity(50, velocityUnits::pct);//left intake will continue to spin at 50pct when right 1 is not pressed
        RightIntake.setVelocity(50, velocityUnits::pct);//right intake will continue to spin at 50 pct when right 1 is not pressed

        LeftMotor.spin(vex::directionType::fwd, (Controller.Axis3.value() + Controller.Axis1.value()*2), vex::velocityUnits::pct);//left motor will spin forward and change direction according to input from the right stick
        RightMotor.spin(vex::directionType::fwd, (Controller.Axis3.value() - Controller.Axis1.value()*2), vex::velocityUnits::pct);//right motor will spin forward and change direction according to input from the left stick

        if((Controller.ButtonL1.pressing())){//if right 1 is pressed reverse the spin of left intake and right intake
            LeftIntake.spin(directionType::rev);
            RightIntake.spin(directionType::rev);
            LeftIntake.setVelocity(100, velocityUnits::pct);
            RightIntake.setVelocity(1000, velocityUnits::pct);
        }

        else if (Controller.ButtonR1.pressing()){//if right 1 is pressed set the left intake and right intake speed to 0
            LeftIntake.setVelocity(0, velocityUnits::pct);
            RightIntake.setVelocity(0, velocityUnits::pct);
        }
  }
/*
while(Controller.ButtonR1.pressing()){
  ArmMotor1.spin(directionType::fwd);
  ArmMotor2.spin(directionType::fwd);
}
ArmMotor1.stop()
ArmMotor1.stop()

*/

  /*while(notEnded){
    LeftMotor.rotateFor(5, rotationUnits::deg, false);
    RightMotor.rotateFor(-5, rotationUnits::deg);

    if (Controller.ButtonR1.pressing()){
      notEnded = false;
    }
  }*/

  Brain.Screen.print("Left Motor rotation: ");
  Brain.Screen.print(LeftMotor.rotation(rotationUnits::deg));
  Brain.Screen.newLine();

  Brain.Screen.print("Right Motor rotation: ");
  Brain.Screen.print(RightMotor.rotation(rotationUnits::deg));
  Brain.Screen.newLine();
}