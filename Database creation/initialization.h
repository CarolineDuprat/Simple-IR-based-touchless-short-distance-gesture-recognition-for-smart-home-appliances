#ifndef INITIALIZATION_H
#define INITIALIZATION_H

#define PI 3.141592
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

typedef struct {
    double x;
    double y;
} position_t;

typedef struct {
    vector<double> positionReceiver;
    bool check;
} returnInit;

returnInit init(int& nbrReceiver,int& direction,double& sizeLength,double& sizeWidth,double& speed,double& distance);
bool checkAllParameters (int const nbrReceiver,position_t positionReceiver[] ,int const angle,double const distance,double const speed,double const sizeWidth,double const sizeLength);
std::vector <double> linearRelation (int const direction);
double distanceMaxReceiverLinearRelationTab (int const direction,position_t positionReceiver[] ,int const nbrReceiver);
double distanceMaxReceiverLinearRelationVector (int const direction,vector <double> positionReceiver,int const nbrReceiver);
void showParameters (int nbrReceiver,position_t positionReceiver[],int direction,double sizeLength,double sizeWidth,double speed,double distance);
#endif // INITIALIZATION_H
