// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <cmath>

#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/PWMSparkMax.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

class Robot : public frc::TimedRobot {
 public:

  WPI_Pigeon2 pigeon{1};
  float yaw;
  float pitch;
  float roll;
  float initPitch;
  bool balance = true;
  bool balanceMode = false;
  float adjustedPitch;
  float balanceRate;
  float maxBalanceRate = 0.23;
  float baseBalanceRate = 0.022;
  float balanceThreshold = 8;

  void RobotInit() override {
    // Invert the right side motors. You may need to change or remove this to
    // match your robot.
    m_rearRight.SetInverted(false);
    m_rearLeft.SetInverted(true);
    m_frontLeft.SetInverted(true);
    pigeon.Reset();
    pigeon.Calibrate();
  }

  void RobotPeriodic() override {
    yaw = pigeon.GetYaw();
    pitch = pigeon.GetPitch();
    roll = pigeon.GetRoll();
    pigeon.Calibrate();

    adjustedPitch = pitch - initPitch;

    frc::SmartDashboard::PutNumber("Yaw", yaw);
    frc::SmartDashboard::PutNumber("Pitch", pitch);
    frc::SmartDashboard::PutNumber("Roll", roll);
    frc::SmartDashboard::PutBoolean("Balanced", balance);
    initPitch = frc::SmartDashboard::GetNumber("PitchOffset", initPitch);
    maxBalanceRate = frc::SmartDashboard::GetNumber("Max Balance Rate", maxBalanceRate);
    baseBalanceRate = frc::SmartDashboard::GetNumber("Base Balance Speed", baseBalanceRate);
    frc::SmartDashboard::PutNumber("True Pitch", adjustedPitch);
  }

  void TeleopInit() override {
    initPitch = pitch;
  }

  void TeleopPeriodic() override {
    /* Use the joystick X axis for forward movement, Y axis for lateral
     * movement, and Z axis for rotation.
     */
    m_robotDrive.DriveCartesian(-m_stick.GetLeftY(), -m_stick.GetLeftX(), m_stick.GetRightX());

    if(m_stick.GetAButtonPressed())
    {
      if (balanceMode)
      {
        balanceMode = false;
      }
      else
      {
        balanceMode = true;
      }
    }

    if (fabs(pitch) > balanceThreshold && balanceMode)
    {
      balance = false;
      balanceRate = (baseBalanceRate * -adjustedPitch);
      if (abs(balanceRate) > maxBalanceRate)
      {
        balanceRate = maxBalanceRate;
      }
      m_allMotors.Set(balanceRate);
    }
    else{balance = true;}
  }

 private:
  static constexpr int kFrontLeftChannel = 2;
  static constexpr int kRearLeftChannel = 3;
  static constexpr int kFrontRightChannel = 0;
  static constexpr int kRearRightChannel = 1;
  static constexpr int kJoystickChannel = 0;

  frc::PWMSparkMax m_frontLeft{kFrontLeftChannel};
  frc::PWMSparkMax m_rearLeft{kRearLeftChannel};
  frc::PWMSparkMax m_frontRight{kFrontRightChannel};
  frc::PWMSparkMax m_rearRight{kRearRightChannel};
  frc::MecanumDrive m_robotDrive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};

  frc::XboxController m_stick{kJoystickChannel};

  frc::MotorControllerGroup m_allMotors 
  {m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif