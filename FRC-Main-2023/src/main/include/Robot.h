#include <string>
#include <cstdio>
#include <thread>
#include <iostream>
#include <frc/TimedRobot.h>
#include <cameraserver/CameraServer.h>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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