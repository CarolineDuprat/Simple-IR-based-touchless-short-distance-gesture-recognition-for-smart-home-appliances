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
std::vector<position_t> rotationCorner (dimension dimensionObject,int angle);
std::vector<position_t> ReelPositionCorner (position_t positionObject,std::vector<position_t> positionCornerRotation);
int signdet (position_t positionCorner1,position_t positionCorner2,position_t positionReceiver);
bool ReceiverCovered (position_t positionReceiver,std::vector<position_t> positionCorner);

#endif // SIMULATIONRECEIVER_H
