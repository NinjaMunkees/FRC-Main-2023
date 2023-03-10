// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <Robot.h>
#include <Drive.h>
#include <Pneumatics.h>
#include <frc/TimedRobot.h>

class Robot : public frc::TimedRobot {
 public:

  void SendArm(int armPos){
    switch (armPos)
    {
    case 1:
      armShort.Set(frc::DoubleSolenoid::Value::kReverse);
      armLong.Set(frc::DoubleSolenoid::Value::kReverse);
      disco.Set(frc::DoubleSolenoid::Value::kReverse);
      break;

    case 2:
      armShort.Set(frc::DoubleSolenoid::Value::kForward);
      armLong.Set(frc::DoubleSolenoid::Value::kReverse);
      break;

    case 3:
      armShort.Set(frc::DoubleSolenoid::Value::kReverse);
      armLong.Set(frc::DoubleSolenoid::Value::kForward);
      break;

    case 4:
      armShort.Set(frc::DoubleSolenoid::Value::kForward);
      armLong.Set(frc::DoubleSolenoid::Value::kForward);
      break;
    
    default:
      break;
    }
  }

  void sendDisco(int discoPos){
    switch (discoPos)
    {
    case 0:
      disco.Set(frc::DoubleSolenoid::Value::kReverse);
      break;
    
    case 1:
      disco.Set(frc::DoubleSolenoid::Value::kForward);
      break;
    
    default:
      break;
    }
  }

  void RobotInit() override {
    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(true);

    sendDisco(0);
    SendArm(0);
  }

  void TeleopPeriodic() override {

    if (btnBoard.GetRawButtonPressed(1)) {SendArm(1);}
    else if (btnBoard.GetRawButtonPressed(2)) {SendArm(2);}
    else if (btnBoard.GetRawButtonPressed(3)) {SendArm(3);}
    else if (btnBoard.GetRawButtonPressed(4)) {SendArm(4);}

    if (btnBoard.GetRawButtonPressed(5)) {sendDisco(0);}
    else if (btnBoard.GetRawButtonPressed(6)) {sendDisco(1);}

    double leftXRaw = m_xboxControl.GetLeftX();
    double leftYRaw = m_xboxControl.GetLeftY();
    double rightXRaw = m_xboxControl.GetRightX();

    if(fabs(leftXRaw) < deadzone) {leftX = 0;} else{leftX = leftXRaw;}
    if(fabs(leftYRaw) < deadzone) {leftY = 0;} else {leftY = leftYRaw;}
    if(fabs(rightXRaw) < deadzone) {rightX = 0;} else {rightX = rightXRaw;}

    m_robotDrive.DriveCartesian(-leftY, -leftX, rightX);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif