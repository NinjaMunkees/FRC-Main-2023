  #include <iostream>
  #include <string>
  
  //Drive

    #include "rev/CANSparkMax.h"
    #include <frc/XboxController.h>
    #include <frc/drive/MecanumDrive.h>
    #include <frc/motorcontrol/MotorControllerGroup.h>

    rev::CANSparkMax m_frontLeft1{5, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_frontLeft2{6, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_rearLeft1{3, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_rearLeft2{4, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_frontRight1{9, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_frontRight2{10, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_rearRight1{7, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
    rev::CANSparkMax m_rearRight2{8, rev::CANSparkMaxLowLevel::MotorType::kBrushless};

    frc::MotorControllerGroup m_frontLeft{m_frontLeft1, m_frontLeft2};
    frc::MotorControllerGroup m_rearLeft{m_rearLeft1, m_rearLeft2};
    frc::MotorControllerGroup m_frontRight{m_frontRight1, m_frontRight2};
    frc::MotorControllerGroup m_rearRight{m_rearRight1, m_rearRight2};

    frc::MecanumDrive m_robotDrive{m_frontLeft, m_rearLeft, m_frontRight, m_rearRight};

    frc::XboxController m_xboxControl{0};

    double leftX, leftY, rightX;
    double deadzone = 0.15;

  //Pneumatics

    #include <frc/PneumaticHub.h>
    #include <frc/DoubleSolenoid.h>
    #include <frc/Joystick.h>

    int hubID = 2;

    frc::Joystick btnBoard{1};

    frc::DoubleSolenoid armShort{hubID, frc::PneumaticsModuleType::REVPH, 0, 1};
    frc::DoubleSolenoid armLong{hubID, frc::PneumaticsModuleType::REVPH, 2, 3};
    frc::DoubleSolenoid disco{hubID, frc::PneumaticsModuleType::REVPH, 4, 5};