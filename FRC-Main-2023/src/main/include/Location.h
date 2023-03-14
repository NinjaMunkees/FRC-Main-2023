#include <AHRS.h>
#include <ctre/Phoenix.h>

const double balanceThreshold = 12; //Angle offset in which the robot will start balanceing automatically.
const double balanceRate = 0;       //Change later. Should be used in conjunction with current rotation do drive mecanum.
