// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

/**
 * This is a demo program showing the use of the DifferentialDrive class.
 * Runs the motors with tank steering and an Xbox controller.
 */
class Robot : public frc::TimedRobot {
  frc::PWMSparkMax m_leftFrontMotor{2};
  frc::PWMSparkMax m_leftRearMotor{3};
  frc::PWMSparkMax m_rightFrontMotor{0};
  frc::PWMSparkMax m_rightRearMotor{1};
  frc::MotorControllerGroup m_leftDrive{m_leftFrontMotor, m_leftRearMotor};
  frc::MotorControllerGroup m_rightDrive{m_rightFrontMotor, m_rightRearMotor};

  frc::DifferentialDrive m_robotDrive{m_leftDrive, m_rightDrive};
  frc::XboxController m_driverController{0};

 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
    m_rightDrive.SetInverted(true);
  }

  void TeleopPeriodic() override {
    // Drive with tank style
    m_robotDrive.TankDrive(-m_driverController.GetLeftY(),
                           -m_driverController.GetRightY());
  }

}

#ifndef RUNNING_FRC_TESTS
int main() 
{
  return frc::StartRobot<Robot>();
}
#endif