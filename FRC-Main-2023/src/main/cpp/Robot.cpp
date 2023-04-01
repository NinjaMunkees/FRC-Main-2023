// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <Robot.h>
#include <Drive.h>
#include <Balance.h>
#include <Arm.h>
#include <frc/TimedRobot.h>
#include <iostream>

#define PUT_NUMBER frc::SmartDashboard::SmartDashboard::PutNumber

// Debug Preprocessor
#define DEBUG
//End

class Robot : public frc::TimedRobot {
 public:

   void RobotInit() override {
    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(true);

    m_rearLeft.SetOpenLoopRampRate(accelRate);
    m_frontLeft.SetOpenLoopRampRate(accelRate);
    m_rearRight.SetOpenLoopRampRate(accelRate);
    m_frontRight.SetOpenLoopRampRate(accelRate);

    SendDisco(0);
    SendArm(0);
  }

  void SendArm(int armPos){
    switch (armPos)
    {
    case 1:
      break;

    case 2:
      break;

    case 3:
      break;

    case 4:
      break;
    
    default:
      break;
    }
  }

  void SendDisco(int discoPos){
    switch (discoPos)
    {
    case 0:
      break;
    
    case 1:
      break;
    
    default:
      break;
    }
  }

  void RobotPeriodic() override {
    frc::SmartDashboard::SmartDashboard::PutNumber("Front Left Encoder", m_frontLeftEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Rear Left Encoder", m_rearLeftEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Front Right Encoder", m_frontRightEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Rear Right Encoder", m_rearRightEncoder.GetPosition());

    double m_rightEncoder = (m_rearRightEncoder.GetPosition() + m_frontRightEncoder.GetPosition()) / 2;
    double m_leftEncoder = (m_rearLeftEncoder.GetPosition() + m_frontLeftEncoder.GetPosition()) / 2;

    PUT_NUMBER("yaw", pigeon.GetYaw());
    PUT_NUMBER("pitch", pigeon.GetPitch());
    PUT_NUMBER("roll", pigeon.GetRoll());

  }

  void AutonomousInit() override {
    m_frontLeftEncoder.SetPosition(0);
    m_rearLeftEncoder.SetPosition(0);
    m_frontRightEncoder.SetPosition(0);
    m_rearRightEncoder.SetPosition(0); 
  }

  void AutonomousPeriodic() override {
    if (fabs(m_rearRightEncoder.GetPosition()) < 30)
    {
      m_robotDrive.DriveCartesian(-0.2, 0, 0);
    }
    else{m_robotDrive.DriveCartesian(-0, 0, 0);}
  }

  void TeleopPeriodic() override {

    if (btnBoard.GetRawButtonPressed(1)) { SendArm(1);}
    else if (btnBoard.GetRawButtonPressed(2)) {SendArm(2);}
    else if (btnBoard.GetRawButtonPressed(3)) {SendArm(3);}
    else if (btnBoard.GetRawButtonPressed(4)) {SendArm(4);}

    if (btnBoard.GetRawButtonPressed(5)) {m_rollerMotor.Set(rollerSpeed);}
    else if (btnBoard.GetRawButtonPressed(6)) {m_rollerMotor.Set(rollerSpeed);}

    if (m_xboxControl.GetAButtonPressed())
    {balance = !balance;}

    double leftXRaw = m_xboxControl.GetLeftX();
    double leftYRaw = m_xboxControl.GetLeftY();
    double rightXRaw = m_xboxControl.GetRightX();

    double pitchAngleDegrees  = pigeon.GetPitch();
    double usablePitch = pitchAngleDegrees * balanceRate / 60;
    PUT_NUMBER("GOODPITCH", usablePitch);
    double rollAngleDegrees   = 0;

    if (balance){
      leftY = -usablePitch / 2.5;
    }
    else{
      if(fabs(leftXRaw) < deadzone) {leftX = 0;} else{leftX = leftXRaw / 2;}
      if(fabs(leftYRaw) < deadzone) {leftY = 0;} else {leftY = leftYRaw / 2;}
      if(fabs(rightXRaw) < deadzone) {rightX = 0;} else {rightX = rightXRaw / 2;}
    }

    PUT_NUMBER("LEFTY", -leftY);
    
    m_robotDrive.DriveCartesian(-leftY, -leftX, rightX);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif