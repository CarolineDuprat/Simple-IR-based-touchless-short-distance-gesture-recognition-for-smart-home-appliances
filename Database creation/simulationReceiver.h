#ifndef SIMULATIONRECEIVER_H
#define SIMULATIONRECEIVER_H

#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "initialization.h"

typedef struct {
    double hor;
    double vert;
} speed_t;


typedef struct {
    position_t pos;
    speed_t speed;
} returnSpeedPos;

int simulationTime (double const distance,double const speed);
returnSpeedPos HorizontalAndVerticalSpeed (double const distance,double const speed,int const angle);
position_t positionMoveObject (returnSpeedPos information ,unsigned int time);
bool objectInFrontofReceiver (std::vector<double> positionObject,dimension dimensionObject,int angle,position_t positionReceiver);
bool rectanglePointContains (dimension dimensionObject, position_t positionRotation);

#endif // SIMULATIONRECEIVER_H
