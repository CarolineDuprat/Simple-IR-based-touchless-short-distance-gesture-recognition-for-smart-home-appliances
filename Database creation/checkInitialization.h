#ifndef CHECKINITIALIZATION_H
#define CHECKINITIALIZATION_H
#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

bool checkAllParameters (int const nbrReceiver,double const positionReceiver[][2],int const angle,double const distance,double const speed,double const sizeWidth,double const sizeLength);
std::vector <double> linearRelation (int const direction);
double distanceMaxReceiverLinearRelation (int const direction,double const positionReceiver[][2],int const nbrReceiver);

#endif // CHECKINITIALIZATION_H
