#include <frc/PneumaticHub.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Joystick.h>
#define REV_PNEUMATICS frc::PneumaticsModuleType::REVPH

int hubID = 2;

frc::Joystick btnBoard{1};

frc::DoubleSolenoid armShort{hubID, REV_PNEUMATICS, 0, 1}; 
frc::DoubleSolenoid armLong{hubID, REV_PNEUMATICS, 2, 3};
frc::DoubleSolenoid disco{hubID, REV_PNEUMATICS, 4, 5};