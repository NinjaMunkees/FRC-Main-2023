#include <string>
#include <iostream>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>

//Auto

  frc::SendableChooser<std::string> m_chooser;
  const std::string kAutoBalance = "Balance";
  const std::string kAutoStraight = "Straight";
  const std::string kAutoPark = "Park";
  std::string m_autoSelected;
  float desiredPos = 0;
  float autoSpeedY = 0.25;