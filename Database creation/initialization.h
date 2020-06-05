#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

std::vector <double> init(int& nbrReceiver,int& direction,double& sizeLength,double& sizeWidth,double& objectMovingSpeed,double& distance);
std::vector <double> linearRelation (int direction);
double distanceMaxReceiverLinearRelation (int direction,std::vector <double> positionReceiver,int nbrReceiver);
bool convertVectorToTab (std::vector <double> positionReceiver,double tabPositionReceiver[][2],int nbrReceiver);
std::vector <double> equation2nddegre (double coef [3]);
std::vector <double> convertDistancetoPoint (int direction,double distance,double width);

#endif // INITIALIZATION_H

