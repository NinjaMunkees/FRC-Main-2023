    #include <frc/PneumaticHub.h>
    #include <frc/DoubleSolenoid.h>
    #include <frc/Joystick.h>
    #define REVPNEUMATICS frc::PneumaticsModuleType::REVPH

    int hubID = 2;

    frc::Joystick btnBoard{1};

    frc::DoubleSolenoid armShort{hubID, REVPNEUMATICS, 0, 1};
    frc::DoubleSolenoid armLong{hubID, REVPNEUMATICS, 2, 3};
    frc::DoubleSolenoid disco{hubID, REVPNEUMATICS, 4, 5};