#ifndef SIMULATIONRECEIVER_H
#define SIMULATIONRECEIVER_H

#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "structure.h"

int simulationTime (double const distance,double const speed);
returnSpeedPos HorizontalAndVerticalSpeed (double const distance,double const speed,int const angle);
position_t positionMoveObject (returnSpeedPos information ,unsigned int time);
bool objectInFrontofReceiver (std::vector<double> positionObject,dimension dimensionObject,int angle,position_t positionReceiver);
bool rectanglePointContains (dimension dimensionObject, position_t positionRotation);
posCorner rotationCorner (dimension dimensionObject,int angle);
posCorner ReelPositionCorner (position_t positionObject,posCorner positionCornerRotation);
int signdet (position_t positionCorner1,position_t positionCorner2,position_t positionReceiver);
bool ReceiverCovered (position_t positionReceiver,posCorner positionCorner);

#endif // SIMULATIONRECEIVER_H
