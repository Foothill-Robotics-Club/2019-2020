/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Neelay Joglekar                                  */
/*    Created:      Tue Nov 26 2019                                           */
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
vex::motor LeftMotor = vex::motor(PORT1);//left motor for movement
vex::motor RightMotor = vex::motor(PORT2, true);//right motor for movement
vex::motor LeftArmMotor = vex::motor(PORT3);//left motor to raise arm
vex::motor RightArmMotor = vex::motor(PORT4, true);//right motor to raise arm
vex::motor LeftIntake = vex::motor(PORT5);//if r1 and r2 are  not pressed, intake spins continous; if r1 intake stops; if r1+r2, reverse.
vex::motor RightIntake = vex::motor(PORT6, true);//left intake and right intake motors are the spinning mechanism that captures the cubes
vex::motor PushupBar = vex::motor(PORT7);//

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous( void ) {

  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void intakeFunc( void )
{ 
  if((Controller.ButtonR2.pressing())){//if right 2 is pressed reverse the spin of left intake and right intake
      LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
      RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
  }

  else if (Controller.ButtonR1.pressing()){//if right 1 is pressed set the left intake and right intake speed to 0
      LeftIntake.setVelocity(0, velocityUnits::pct);
      RightIntake.setVelocity(0, velocityUnits::pct);
  }
  else{//if not pressed the intake spins as normal
      LeftIntake.spin(directionType::rev, 100, velocityUnits::pct);
      RightIntake.spin(directionType::rev, 100, velocityUnits::pct);
  }
}

void armFunc( void ) {
  if(Controller.ButtonL1.pressing()){//if left 1 is pressing, than 
      LeftArmMotor.spin(directionType::fwd, 100, velocityUnits::pct);
      RightArmMotor.spin(directionType::fwd, 100, velocityUnits::pct);
  }
  else if(Controller.ButtonL2.pressing()){
      LeftArmMotor.spin(directionType::rev, 100, velocityUnits::pct);
      RightArmMotor.spin(directionType::rev, 100, velocityUnits::pct);
  }
  else{
      LeftArmMotor.stop();
      RightArmMotor.stop();
  }
}

void pushFunc( void ){
  if(Controller.ButtonUp.pressing()){
    PushupBar.spin(directionType::rev, 25, velocityUnits::pct);
  }
  else if(Controller.ButtonDown.pressing()){
      PushupBar.spin(directionType::rev, 25, velocityUnits::pct);
  }
  else{
      PushupBar.stop();
  }
}




void usercontrol( void ) {

  while (1){
      LeftMotor.spin(vex::directionType::fwd, (Controller.Axis3.value() + Controller.Axis1.value()*2), vex::velocityUnits::pct);//left motor will spin forward and change direction according to input from the right stick
      RightMotor.spin(vex::directionType::fwd, (Controller.Axis3.value() - Controller.Axis1.value()*2), vex::velocityUnits::pct);//right motor will spin forward and change direction according to input from the left stick

      armFunc();
      intakeFunc();
      //pushFunc();
  }

}
