#include <frc/SPI.h>
#include <ctre/phoenix/sensors/Pigeon2.h>

ctre::phoenix::sensors::Pigeon2 pigeon{11};

float balanceRate = 0.5;
float balanceThresh = 5;
bool balance;