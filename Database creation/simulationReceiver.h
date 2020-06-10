#ifndef SIMULATIONRECEIVER_H
#define SIMULATIONRECEIVER_H

#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

int simulationTime (double const distance,double const speed);
std::vector<double> HorizontalAndVerticalSpeed (double const distance,double const speed,int const angle);
std::vector<double> positionMoveObject (std::vector<double> information ,unsigned int time);
int objectInFrontofReceiver (std::vector<double> positionObject,double sizeLength, double sizeWidth,int angle,double positionReceiverX,double positionReceiverY);
int rectanglePointContains (double sizeLength, double sizeWidth, double pointX, double pointY);

#endif // SIMULATIONRECEIVER_H
