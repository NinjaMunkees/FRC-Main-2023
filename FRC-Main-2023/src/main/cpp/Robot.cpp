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

/*
  static void VisionThread(){
    cs::UsbCamera cam = frc::CameraServer::StartAutomaticCapture();
    cam.SetResolution(320, 240);
    cs::CvSink cvSink = frc::CameraServer::GetVideo();
    cs::CvSource outputStream = frc::CameraServer::PutVideo("Rectangle", 640, 480);
    cv::Mat mat;

    while (true)
    {
      outputStream.PutFrame(mat);
    }
  }
*/
   void RobotInit() override {
    m_autoSelected = m_chooser.GetSelected();
    fmt::print("Auto selected: {}\n", m_autoSelected);

    m_chooser.SetDefaultOption(kAutoBalance, kAutoBalance);
    m_chooser.AddOption(kAutoStraight, kAutoStraight);
    m_chooser.AddOption(kAutoPark, kAutoPark);
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

    m_armMotor = new TalonFX(13);

    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(true);

    m_rearLeft.SetOpenLoopRampRate(accelRate);
    m_frontLeft.SetOpenLoopRampRate(accelRate);
    m_rearRight.SetOpenLoopRampRate(accelRate);
    m_frontRight.SetOpenLoopRampRate(accelRate);

   // std::thread visionThread(VisionThread);
   // visionThread.detach(); 
  }

  void SendArm(int armPos){
    switch (armPos)
    {
    case 1:
      // if (m_armMotor->GetSelectedSensorPosition()  > 0)
      // {
      //   m_armMotor->Set(ControlMode::PercentOutput, -0.125);
      // }
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

  void SendRoller(int rollerPolarity){
    rollerTimer.Restart();
    if (rollerTimer.Get().value() < 1)
    {
      m_rollerMotorLeft.Set(rollerSpeed);
      m_rollerMotorRight.Set(rollerSpeed);
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

  void AutonomousInit() override {\
    m_frontLeftEncoder.SetPosition(0);
    m_rearLeftEncoder.SetPosition(0);
    m_frontRightEncoder.SetPosition(0);
    m_rearRightEncoder.SetPosition(0); 

    balance = false;
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

    if (btnBoard.GetRawButton(5) || m_xboxControl.GetLeftBumper()) {m_armMotor->Set(ControlMode::PercentOutput, 0.125);}
    else if (btnBoard.GetRawButton(6) || m_xboxControl.GetRightBumper()) {m_armMotor->Set(ControlMode::PercentOutput, -0.125);}

    if (btnBoard.GetRawButtonPressed(7)) {SendRoller(-1);}
    else if (btnBoard.GetRawButtonPressed(8)) {SendRoller(1);}

    if (btnBoard.GetRawButtonPressed(9)) {m_rollerMotor.Set(rollerSpeed);}
    else if (btnBoard.GetRawButtonPressed(10)) {m_rollerMotor.Set(rollerSpeed);}

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
#endif (btnBoard.GetRawButtonPressed(5)) {m_armMotor->Set(ControlMode::PercentOutput, 0.125);}if (btnBoard.GetRawButtonPressed(5)) {m_armMotor->Set(ControlMode::PercentOutput, 0.125);}