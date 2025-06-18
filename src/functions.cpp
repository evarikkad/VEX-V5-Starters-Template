#include "robot-config.h"
#include "vex.h"

using namespace vex;

double inchesToDegrees(double inches) {
  return (inches / (M_PI * 3.25)) * 360.0 * (5/3);
}

void setDTPosition(double inches) {
    double deg = inchesToDegrees(inches);
    LF.setPosition(deg, degrees);
    LM.setPosition(deg, degrees);
    LB.setPosition(deg, degrees);
    RF.setPosition(deg, degrees);
    RM.setPosition(deg, degrees);
    RB.setPosition(deg, degrees);
}

void stopDT() {
    LF.stop();
    LM.stop();
    LB.stop();
    RF.stop();
    RM.stop();
    RB.stop();
}


void spinRightDT(double velocity) {
    RF.spin(forward, velocity, percent);
    RM.spin(forward, velocity, percent);
    RB.spin(forward, velocity, percent);
}

void spinLeftDT(double velocity) {
    LF.spin(forward, velocity, percent);
    LM.spin(forward, velocity, percent);
    LB.spin(forward, velocity, percent);
}

void spinDT(double velocity) {
    spinRightDT(velocity);
    spinLeftDT(velocity);
}

//Copy This Funtion When Teaching
void spinDTWithDistance(double inches, double velocity) {
    setDTPosition(inches);
    spinDT(velocity);
    while (LF.position(degrees) < inchesToDegrees(inches)) {
        vex::task::sleep(20);
    }
    stopDT();
}

void turnDTWithAngle(double angle, double velocity) {
    InertialSensor.setHeading(0, degrees);
    RF.spin(forward, velocity, percent);
    RM.spin(forward, velocity, percent);
    RB.spin(forward, velocity, percent);
    LF.spin(reverse, velocity, percent);
    LM.spin(reverse, velocity, percent);
    LB.spin(reverse, velocity, percent);
    while (fabs(InertialSensor.heading(degrees)) < fabs(angle)) {
        vex::task::sleep(20);
    }
    stopDT();
}