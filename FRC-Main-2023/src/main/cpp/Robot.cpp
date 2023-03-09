// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <Robot.h>
#include <frc/TimedRobot.h>

/**
 * This is a demo program showing how to use Mecanum control with the
 * MecanumDrive class.
 */
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
      disco.Set(frc::DoubleSolenoid::Value::kForward);
      break;
    
    case 1:
      disco.Set(frc::DoubleSolenoid::Value::kReverse);
      break;
    
    default:
      break;
    }
  }

  void RobotInit() override {
    // Invert the right side motors. You may need to change or remove this to
    // match your robot.
    m_frontRight.SetInverted(true);
    m_rearRight.SetInverted(true);
  }

  void TeleopPeriodic() override {
    /* Use the joystick X axis for forward movement, Y axis for lateral
     * movement, and Z axis for rotation.
     */
    
    if (btnBoard.GetRawButtonPressed(1)) {SendArm(1);}
    else if (btnBoard.GetRawButtonPressed(2)) {SendArm(2);}
    else if (btnBoard.GetRawButtonPressed(3)) {SendArm(3);}
    else if (btnBoard.GetRawButtonPressed(4)) {SendArm(4);}

    if (btnBoard.GetRawButtonPressed(5)) {sendDisco(0);}
    else if (btnBoard.GetRawButtonPressed(6)) {sendDisco(1);}

    m_robotDrive.DriveCartesian(-m_xboxControl.GetLeftY(), -m_xboxControl.GetLeftX(), -m_xboxControl.GetRightX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
