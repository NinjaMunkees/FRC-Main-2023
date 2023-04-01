#include "rev/CANSparkMax.h"
#include "rev/SparkMaxRelativeEncoder.h"
#include <frc/XboxController.h>
#include <frc/drive/MecanumDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#define MOTOR_BRUSHLESS rev::CANSparkMaxLowLevel::MotorType::kBrushless

rev::CANSparkMax m_frontLeft{6, MOTOR_BRUSHLESS};
rev::CANSparkMax m_rearLeft{4, MOTOR_BRUSHLESS};
rev::CANSparkMax m_frontRight{10, MOTOR_BRUSHLESS};
rev::CANSparkMax m_rearRight{8, MOTOR_BRUSHLESS};

rev::SparkMaxRelativeEncoder m_frontRightEncoder = m_frontRight.GetEncoder();
rev::SparkMaxRelativeEncoder m_rearRightEncoder = m_rearRight.GetEncoder();
rev::SparkMaxRelativeEncoder m_frontLeftEncoder = m_frontLeft.GetEncoder();
rev::SparkMaxRelativeEncoder m_rearLeftEncoder = m_rearLeft.GetEncoder();
double m_rightEncoder;
double m_leftEncoder;

frc::MecanumDrive m_robotDrive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};

frc::XboxController m_xboxControl{0};

double leftX, leftY, rightX;
double leftXRaw, leftYRaw, rightXRaw;
const double deadzone = 0.175;
const double accelRate = 1.35;