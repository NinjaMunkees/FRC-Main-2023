#include <frc/Joystick.h>
#include "ctre/Phoenix.h"
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxRelativeEncoder.h>
#define MOTOR_BRUSHLESS rev::CANSparkMaxLowLevel::MotorType::kBrushless

double armSpeed = 0.7;
double rollerSpeed = 1;
int armPosition = 1;

frc::Joystick btnBoard{1};

TalonFX * m_armMotor;
rev::CANSparkMax m_rollerMotorRight{12, rev::CANSparkMaxLowLevel::MotorType::kBrushed};
rev::CANSparkMax m_rollerMotorLeft{14, rev::CANSparkMaxLowLevel::MotorType::kBrushed};

void SendArm(int armPos);

frc::Timer rollerTimer;
float rollerTimeToRun = 1;