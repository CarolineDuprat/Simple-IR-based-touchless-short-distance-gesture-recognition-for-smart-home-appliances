#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include "structure.h"

returnInit init(int& nbrReceiver,int& direction,dimension& dimensionObject,double& speed,double& distance);
bool checkAllParameters (int const nbrReceiver,position_t positionReceiver[] ,int const angle,double const distance,double const speed,dimension dimensionObject);
std::vector <double> linearRelation (int const direction);
double distanceMaxReceiverLinearRelationTab (int const direction,position_t positionReceiver[] ,int const nbrReceiver);
double distanceMaxReceiverLinearRelationVector (int const direction,std::vector <double> positionReceiver,int const nbrReceiver);
void showParameters (int nbrReceiver,position_t positionReceiver[],int direction,dimension dimensionObject,double speed,double distance);

#endif // INITIALIZATION_H
