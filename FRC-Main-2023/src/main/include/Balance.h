#include <frc/SPI.h>
#include "AHRS.h"
#include "stdio.h"

float balanceRate = 0.1;
float  balanceThresh = 12;
bool balance;