// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <Robot.h>
#include <Drive.h>
#include <Pneumatics.h>
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

    m_rearLeft1.SetOpenLoopRampRate(accelRate);
    m_rearLeft2.SetOpenLoopRampRate(accelRate);
    m_frontLeft1.SetOpenLoopRampRate(accelRate);
    m_frontLeft2.SetOpenLoopRampRate(accelRate);
    m_rearRight1.SetOpenLoopRampRate(accelRate);
    m_rearRight2.SetOpenLoopRampRate(accelRate);
    m_frontRight1.SetOpenLoopRampRate(accelRate);
    m_frontRight2.SetOpenLoopRampRate(accelRate);

    sendDisco(0);
    SendArm(0);
  }

  void RobotPeriodic() override {
    frc::SmartDashboard::SmartDashboard::PutNumber("Front Left Encoder", m_frontLeftEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Rear Left Encoder", m_rearLeftEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Front Right Encoder", m_frontRightEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Rear Right Encoder", m_rearRightEncoder.GetPosition());

    double m_rightEncoder = (m_rearRightEncoder.GetPosition() + m_frontRightEncoder.GetPosition()) / 2;
    double m_leftEncoder = (m_rearLeftEncoder.GetPosition() + m_frontLeftEncoder.GetPosition()) / 2;

    #ifdef DEBUG
      std::cout << "Right Encoder: " << m_rightEncoder << " Left Encoder: " << m_leftEncoder << std::endl;
    #endif
  }

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

  void AutonomousInit() override {
    m_frontLeftEncoder.SetPosition(0);
    m_rearLeftEncoder.SetPosition(0);
    m_frontRightEncoder.SetPosition(0);
    m_rearRightEncoder.SetPosition(0); 
  }

  void AutonomousPeriodic() override {
    if (fabs(m_rearRightEncoder.GetPosition()) < 20
    )
    {
      m_robotDrive.DriveCartesian(-0.2, 0, 0);
    }
    else{m_robotDrive.DriveCartesian(-0, 0, 0);}
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

    if(fabs(leftXRaw) < deadzone) {leftX = 0;} else{leftX = leftXRaw / 2;}
    if(fabs(leftYRaw) < deadzone) {leftY = 0;} else {leftY = leftYRaw / 2;}
    if(fabs(rightXRaw) < deadzone) {rightX = 0;} else {rightX = rightXRaw / 2;}

    m_robotDrive.DriveCartesian(-leftY, -leftX, rightX);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
