#include <frc/Joystick.h>
#include "rev/CANSparkMax.h"
#include "rev/SparkMaxRelativeEncoder.h"
#define MOTOR_BRUSHLESS rev::CANSparkMaxLowLevel::MotorType::kBrushless

double armSpeed = 0.1;
double rollerSpeed = 0.1;

frc::Joystick btnBoard{1};

rev::CANSparkMax m_armMotor{11, MOTOR_BRUSHLESS};
rev::CANSparkMax m_rollerMotor{12, MOTOR_BRUSHLESS};

rev::SparkMaxRelativeEncoder m_armEncoder = m_armMotor.GetEncoder();
rev::SparkMaxRelativeEncoder m_rollerEncoder = m_rollerMotor.GetEncoder();

void SendDisco(int discoPos);
void SendArm(int armPos);