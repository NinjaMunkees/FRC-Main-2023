//#include <frc/SPI.h>
#include <ctre/phoenix/sensors/Pigeon2.h>

ctre::phoenix::sensors::Pigeon2 pigeon{11};

float balanceRate = 1;
float balanceThresh = 0;
bool balance;

float pitch, yaw, roll;
double goodPitch;