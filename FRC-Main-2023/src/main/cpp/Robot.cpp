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
    m_autoSelected = m_chooser.GetSelected();
    fmt::print("Auto selected: {}\n", m_autoSelected);

    m_chooser.SetDefaultOption(kAutoBalance, kAutoBalance);
    m_chooser.AddOption(kAutoStraight, kAutoStraight);
    m_chooser.AddOption(kAutoPark, kAutoPark);
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

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

    m_rightEncoder = (m_rearRightEncoder.GetPosition() + m_frontRightEncoder.GetPosition()) / 2;
    m_leftEncoder = (m_rearLeftEncoder.GetPosition() + m_frontLeftEncoder.GetPosition()) / 2;

    pitch = pigeon.GetPitch();
    yaw = pigeon.GetYaw();
    roll = pigeon.GetRoll();

    goodPitch = pitch * balanceRate / 60;
    PUT_NUMBER("Good Pitch", goodPitch);

    PUT_NUMBER("yaw", yaw);
    PUT_NUMBER("pitch", pitch);
    PUT_NUMBER("roll", roll);
  }

  void AutonomousInit() override {
    m_frontLeftEncoder.SetPosition(0);
    m_rearLeftEncoder.SetPosition(0);
    m_frontRightEncoder.SetPosition(0);
    m_rearRightEncoder.SetPosition(0); 

    balance = false;

    if (m_autoSelected == kAutoBalance) {

    }
    else if (m_autoSelected == kAutoStraight)
    {

    }
    else if (m_autoSelected == kAutoPark)
    {

    }
  }

  void AutonomousPeriodic() override {

    if (m_autoSelected == kAutoBalance) {

      if (m_rearLeftEncoder.GetPosition() < desiredPos && m_frontRightEncoder.GetPosition() < desiredPos)
      {
        leftYRaw = autoSpeedY;
      }
      else{balance = true;}
      
      if (balance)
      {
        leftY = -goodPitch / 2.5;
      }
      else{leftY = leftYRaw;}
      
      m_robotDrive.DriveCartesian(-leftY, -leftX, rightX);
    }
    else if (m_autoSelected == kAutoStraight)
    {
      if (fabs(m_rearRightEncoder.GetPosition()) < 30)
      {
       m_robotDrive.DriveCartesian(-0.2, 0, 0);
      }
      else{m_robotDrive.DriveCartesian(-0, 0, 0);}       
    }
    else if (m_autoSelected == kAutoPark)
    {
      m_robotDrive.DriveCartesian(-0, 0, 0);
    }
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

    leftXRaw = m_xboxControl.GetLeftX();
    leftYRaw = m_xboxControl.GetLeftY();
    rightXRaw = m_xboxControl.GetRightX();

    if (balance){
      leftY = -goodPitch / 2.5;
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