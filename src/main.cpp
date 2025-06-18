/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       katherinezeng                                             */
/*    Created:      5/27/2025, 10:30:19 PM                                    */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "robot-config.h"
#include "PID.h"
#include "autons.h"
#include "auton-selector.h"
#include "arm.h"
#include "functions.h"

using namespace vex;

// A global instance of competition
competition Competition;


// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


  vexcodeInit();
  displayAutonSelector();
  
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

void autonomous(void) {
  
  switch (getSelectedAuton()) {
    case 0:
      rightAuton();
      break;
    case 1:
      leftAuton();
      break;
    case 2:
      skillsAuton();
      break;
    default:
      Brain.Screen.print("No valid auton selected!");
      break;
  }
 


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

void usercontrol(void) {

  while (true) {
    // ========== DRIVE CONTROL ========== //
    double fwd = Controller.Axis3.position();
    double turn = Controller.Axis1.position();

    double leftPower  = fwd + turn;
    double rightPower = fwd - turn;

    spinLeftDT(leftPower*0.5);
    spinRightDT(rightPower/2);

    // ========== ARM CONTROL ========== //
    if (Controller.ButtonA.pressing()) {
      Arm1.spin(forward, 75, percent);
      Arm2.spin(forward, 75, percent);
    } else if (Controller.ButtonB.pressing()) {
      Arm1.spin(reverse, 75, percent);
      Arm2.spin(reverse, 75, percent);
    } else {
      Arm1.stop(hold);
      Arm2.stop(hold);
    }

    // ========== CLAMP CONTROL ========== //
    if (Controller.ButtonL1.pressing()) {
      DoubleActingPiston.set(true);  // close
    } else if (Controller.ButtonL2.pressing()) {
      DoubleActingPiston.set(false); // open
    }

    // Loop delay
    wait(20, msec);
  }
}


//
// Main will set up the competition functions and callbacks.
//
int main() {

  pre_auton();

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  Competition.test_auton();
  //Competition.test_driver();

  while (true) {
    wait(100, msec);
  }
}
