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
vex::motor LeftPushup = vex::motor(PORT16);//
vex::motor RightPushup = vex::motor(PORT17);

double rot = -60;
double rotArm;
bool stack = false;
bool knock2 = false;

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

void autonomousleft(void){
  
}


void autonomousright( void ) {  
  LeftMotor.setVelocity(100, velocityUnits::pct);
  RightMotor.setVelocity(100, velocityUnits::pct);
  
  LeftIntake.setVelocity(100, velocityUnits::pct);//spinning the left and right intake
  RightIntake.setVelocity(100, velocityUnits::pct);//spinning the left and rght intake

  LeftMotor.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct, false);//move forward to pick up cubes
  RightMotor.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct);//move forward to pick up cubes

  LeftMotor.rotateFor(-3000, rotationUnits::deg, 100, velocityUnits::pct, false);//move backward after pick up cube 
  RightMotor.rotateFor(-3000, rotationUnits::deg, 100, velocityUnits::pct);//move backward after pick up cube

  LeftMotor.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct, false);//turn 270 degrees
  RightMotor.rotateFor(-3000, rotationUnits::deg, 100, velocityUnits::pct);//turn 270 degrees

  LeftMotor.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct, false);//move forward to goal zone
  RightMotor.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct);//move forward to goal zone
  
  LeftPushup.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct, false);//position bar to be vetical of the floor
  RightPushup.rotateFor(3000, rotationUnits::deg, 100, velocityUnits::pct);//position bar to be vetical of the floor

  LeftIntake.setVelocity(0, velocityUnits::pct);//
  RightIntake.setVelocity(0, velocityUnits::pct);
}
/*If we start in the area that is closer to the smaller goal zone, we should aim to execute the following movements:

Move forward to capture the line of blocks. Simply execute a forward functions.
Sharp 90 degree turn.
Drive forward into the stack of two to knock it down. Retract the robot and collect the fallen cube by proceeding forward.
By then we should have have a short 5 second duration. Return with the cubes stacked in the robot and place it in the smaller goal zone:
Drive backwards almost to the wall. Rotate 90 degrees.
Drive forward and push the tray upright.
Plan Overview: Larger Goal

If we start in the area that is closer to the smaller goal zone, we should aim to execute the following movements:

Move forward towards the tower of four.
Drive forward, collect the single block.
Drive forward, use intake to pick of a cube at time.
Lower intake to collect all the cubes
Sharp 180 to return
*/


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
  if (Controller.ButtonY.pressing()){
    knock2 = true;
  }
  else if (Controller.ButtonA.pressing()) {
    knock2 = false;
  }
  if(stack||knock2){
    LeftIntake.spin(directionType::fwd, 100, velocityUnits::pct);
    RightIntake.spin(directionType::fwd, 100, velocityUnits::pct);
  }
  else{
    if((Controller.ButtonR2.pressing())){//if right 2 is pressed reverse the spin of left intake and right intake
        LeftIntake.spin(directionType::fwd, 75, velocityUnits::pct);
        RightIntake.spin(directionType::fwd, 75, velocityUnits::pct);
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
}

void armFunc( void ) {
  if (Controller.ButtonX.pressing()){
    stack = true;
  }
  else if (Controller.ButtonB.pressing()) {
    stack = false;
  }
  if(stack){
    LeftArmMotor.rotateTo(475, rotationUnits::deg, false);
    RightArmMotor.rotateTo(475, rotationUnits::deg, false);
  }
  else if(knock2){
    LeftArmMotor.rotateTo(700, rotationUnits::deg, false);
    RightArmMotor.rotateTo(700, rotationUnits::deg, false);
  }
  else{
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
}

void pushFunc( void ){
  if(Controller.ButtonUp.pressing() && rot > -240){
    PushupBar.spin(directionType::rev, 5, velocityUnits::pct);
    rot = PushupBar.rotation(deg);
  }
  else if(Controller.ButtonDown.pressing()){
      //PushupBar.spin(directionType::fwd, 5, velocityUnits::pct);
      rot = -60;
  }
  else{
      PushupBar.rotateTo(rot, rotationUnits::deg);
  }
}




void usercontrol( void ) {
  PushupBar.resetRotation();
  LeftArmMotor.resetRotation();
  RightArmMotor.resetRotation();
  while (1){
      LeftMotor.spin(vex::directionType::fwd, (Controller.Axis3.value() + Controller.Axis1.value()*2), vex::velocityUnits::pct);//left motor will spin forward and change direction according to input from the right stick
      RightMotor.spin(vex::directionType::fwd, (Controller.Axis3.value() - Controller.Axis1.value()*2), vex::velocityUnits::pct);//right motor will spin forward and change direction according to input from the left stick

      armFunc();
      intakeFunc();
      pushFunc();
  }

}
