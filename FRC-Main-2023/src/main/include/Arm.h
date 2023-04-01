#include <frc/Joystick.h>
#include "ctre/Phoenix.h"
#include <rev/CANSparkMax.h>
#include <rev/SparkMaxRelativeEncoder.h>
#define MOTOR_BRUSHLESS rev::CANSparkMaxLowLevel::MotorType::kBrushless

double armSpeed = 0.1;
double rollerSpeed = 0.1;

frc::Joystick btnBoard{1};

TalonFX * m_armMotor;
rev::CANSparkMax m_rollerMotor{7, MOTOR_BRUSHLESS};

void SendDisco(int discoPos);
void SendArm(int armPos);

frc::Timer rollerTimer;
float rollerTimeToRun = 1;