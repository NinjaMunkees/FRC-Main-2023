  static constexpr int kJoystickChannel = 0;

  //Drive

    #include <frc/XboxController.h>
    #include <frc/drive/MecanumDrive.h>
    #include <frc/motorcontrol/PWMSparkMax.h>
    #include <frc/motorcontrol/MotorControllerGroup.h>

    frc::PWMSparkMax m_frontLeft1{0};
    frc::PWMSparkMax m_frontLeft2{1};
    frc::PWMSparkMax m_rearLeft1{2};
    frc::PWMSparkMax m_rearLeft2{3};
    frc::PWMSparkMax m_frontRight1{4};
    frc::PWMSparkMax m_frontRight2{5};
    frc::PWMSparkMax m_rearRight1{6};
    frc::PWMSparkMax m_rearRight2{7};

    frc::MotorControllerGroup m_frontLeft{m_frontLeft1, m_frontLeft2};
    frc::MotorControllerGroup m_rearLeft{m_rearLeft1, m_rearLeft2};
    frc::MotorControllerGroup m_frontRight{m_frontRight1, m_frontRight2};
    frc::MotorControllerGroup m_rearRight{m_rearRight1, m_rearRight2};

    frc::MecanumDrive m_robotDrive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};

    frc::XboxController m_xboxControl{0};

  //Pneumatics

    #include <frc/PneumaticHub.h>
    #include <frc/DoubleSolenoid.h>
    #include <frc/Joystick.h>

    int hubID = 3;

    frc::Joystick btnBoard{1};

    frc::DoubleSolenoid armShort{hubID, frc::PneumaticsModuleType::REVPH, 4, 5};
    frc::DoubleSolenoid armLong{hubID, frc::PneumaticsModuleType::REVPH, 4, 5};
    frc::DoubleSolenoid disco{hubID, frc::PneumaticsModuleType::REVPH, 4, 5};