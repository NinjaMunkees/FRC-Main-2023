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
    initPitch = pigeon.GetPitch();

    m_armMotor = new TalonFX(13);
    m_armMotor->SetNeutralMode(ctre::phoenix::motorcontrol::NeutralMode::Brake);

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
    switch (armPosition)
    {
    case 1: // Stage 1
    if (m_armMotor->GetSelectedSensorPosition() != 0) {
      if(m_armMotor->GetSelectedSensorPosition() > 0){
        // Make arm go reverse
        m_armMotor->Set(ControlMode::PercentOutput, 0.05);
      } else if (m_armMotor->GetSelectedSensorPosition() < 0){
        // Make arm go forward
        m_armMotor->Set(ControlMode::PercentOutput, -0.05);
      }
    } else {
      // stop motor
      m_armMotor->Set(ControlMode::PercentOutput, 0);
    }
      break;

    case 2: // Stage 2
    if (m_armMotor->GetSelectedSensorPosition() != -10) {
      if(m_armMotor->GetSelectedSensorPosition() > 0){
        // Make arm go reverse
        m_armMotor->Set(ControlMode::PercentOutput, 0.05);
      } else if (m_armMotor->GetSelectedSensorPosition() < 0){
        // Make arm go forward
        m_armMotor->Set(ControlMode::PercentOutput, -0.05);
      }
    } else {
      // stop motor
      m_armMotor->Set(ControlMode::PercentOutput, 0);
    }
      break;

    case 3: // Stage 3
    if (m_armMotor->GetSelectedSensorPosition() != -20) {
      if(m_armMotor->GetSelectedSensorPosition() > 0){
        // Make arm go reverse
        m_armMotor->Set(ControlMode::PercentOutput, 0.05);
      } else if (m_armMotor->GetSelectedSensorPosition() < 0){
        // Make arm go forward
        m_armMotor->Set(ControlMode::PercentOutput, -0.05);
      } 
    } else {
      // stop motor
      m_armMotor->Set(ControlMode::PercentOutput, 0);
    }
      break;

    case 4: // Stage 4
    if (m_armMotor->GetSelectedSensorPosition() != -30) {
      if(m_armMotor->GetSelectedSensorPosition() > 0){
        // Make arm go reverse
        m_armMotor->Set(ControlMode::PercentOutput, 0.05);
      } else if (m_armMotor->GetSelectedSensorPosition() < 0){
        // Make arm go forward
        m_armMotor->Set(ControlMode::PercentOutput, -0.05);
      }
    } else {
      // stop motor
      m_armMotor->Set(ControlMode::PercentOutput, 0);
    }
      break;
    
    default: // Stage Off
      //m_armMotor->Set(ControlMode::PercentOutput, 0);
      break;
    }
  }


// untested
  void DriveTo (double speed, int distance)
  { 
    if (distance > 0) {
      if (fabs(m_rearRightEncoder.GetPosition()) < distance) {
        m_robotDrive.DriveCartesian(speed, 0, 0);
      }
      else{m_robotDrive.DriveCartesian(-0, 0, 0);} // Stop
    } 
  }
  
  void SendRoller(int rollerPolarity){
    rollerTimer.Restart();
    if (rollerTimer.Get().value() < 1)
    {
      m_rollerMotorLeft.Set(rollerSpeed * rollerPolarity);
      m_rollerMotorRight.Set(-rollerSpeed * rollerPolarity);
    }
  }

  void RobotPeriodic() override {
    frc::SmartDashboard::SmartDashboard::PutNumber("Front Left Encoder", m_frontLeftEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Rear Left Encoder", m_rearLeftEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Front Right Encoder", m_frontRightEncoder.GetPosition());
    frc::SmartDashboard::SmartDashboard::PutNumber("Rear Right Encoder", m_rearRightEncoder.GetPosition());

    frc::SmartDashboard::SmartDashboard::PutNumber("Arm Encoder", m_armMotor->GetSelectedSensorPosition());

    m_rightEncoder = (m_rearRightEncoder.GetPosition() + m_frontRightEncoder.GetPosition()) / 2;
    m_leftEncoder = (m_rearLeftEncoder.GetPosition() + m_frontLeftEncoder.GetPosition()) / 2;

    pitch = pigeon.GetPitch();
    yaw = pigeon.GetYaw();
    roll = pigeon.GetRoll();

    goodPitch = (pitch - initPitch) * balanceRate;
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
  }

  void AutonomousPeriodic() override {

      if (abs(goodPitch) > balanceThresh)
      {
        balance = true;
      }

      if (!balance)
      {
        m_armMotor->Set(ControlMode::PercentOutput, -0.05);
        if (m_armMotor->GetSelectedSensorPosition() >= 2048)
        {
          m_armMotor->Set(ControlMode::PercentOutput, 0);
        }
        SendRoller(-1);
        leftY = autoSpeedY;
      }
      else if (balance)
      {
        // Sets arm back to zero (prolly need to make sure it knows to change direction based on encoder value)
        if (m_armMotor->GetSelectedSensorPosition() != 0){m_armMotor->Set(ControlMode::PercentOutput, 0.05);}else{m_armMotor->Set(ControlMode::PercentOutput, 0);}
        m_rollerMotorLeft.Set(-0);
        m_rollerMotorRight.Set(0);
        leftY = goodPitch / 2.5 / 2 * 1.15; // used to be leftY = goodPitch / 2.5 / 3 * 1.15;
      }
      else{leftY = leftYRaw;}

      m_robotDrive.DriveCartesian(leftY, -leftX, rightX);
  }

  void TeleopPeriodic() override {

    if (btnBoard.GetRawButtonPressed(1)) { armPosition = 1;}
    else if (btnBoard.GetRawButtonPressed(2)) { armPosition = 2;}
    else if (btnBoard.GetRawButtonPressed(3)) { armPosition = 3;}
    else if (btnBoard.GetRawButtonPressed(4)) { armPosition = 4;}

    if (btnBoard.GetRawButton(5) || m_xboxControl.GetLeftBumper()) { armPosition = 0; m_armMotor->Set(ControlMode::PercentOutput, armSpeed);}
    else if (btnBoard.GetRawButton(6) || m_xboxControl.GetRightBumper()) { armPosition = 0; m_armMotor->Set(ControlMode::PercentOutput, -armSpeed);}
    else {m_armMotor->Set(ControlMode::PercentOutput, -0);}

    if (btnBoard.GetRawButtonPressed(7)) {SendRoller(-1);}
    else if (btnBoard.GetRawButtonPressed(8)) {SendRoller(1);}

    if (btnBoard.GetRawButton(9)) {
      m_rollerMotorLeft.Set(rollerSpeed);
      m_rollerMotorRight.Set(-rollerSpeed);}
    else if (btnBoard.GetRawButton(10)) {
      m_rollerMotorLeft.Set(-rollerSpeed); 
      m_rollerMotorRight.Set(rollerSpeed);}
    else{
      m_rollerMotorLeft.Set(-0);
      m_rollerMotorRight.Set(0);
    }

    if (m_xboxControl.GetAButtonPressed())
    {balance = !balance;}

    leftXRaw = m_xboxControl.GetLeftX();
    leftYRaw = m_xboxControl.GetLeftY();
    rightXRaw = m_xboxControl.GetRightX();

    if (balance){
      leftY = -goodPitch / 2.5;
    }
    else{
      if(fabs(leftXRaw) < deadzone) {leftX = 0;} else{leftX = leftXRaw / 1.5;}
      if(fabs(leftYRaw) < deadzone) {leftY = 0;} else {leftY = leftYRaw / 1.5;}
      if(fabs(rightXRaw) < deadzone) {rightX = 0;} else {rightX = rightXRaw / 1.5;}
    }

    SendArm(1);
    m_robotDrive.DriveCartesian(-leftY, leftX, rightX);
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif (btnBoard.GetRawButtonPressed(5)) {m_armMotor->Set(ControlMode::PercentOutput, 0.125);}if (btnBoard.GetRawButtonPressed(5)) {m_armMotor->Set(ControlMode::PercentOutput, 0.125);}