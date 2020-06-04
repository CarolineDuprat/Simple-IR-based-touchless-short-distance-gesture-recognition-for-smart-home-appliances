#ifndef DETECTION_H
#define DETECTION_H
#define PI 3.141592
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;


int rectanglePointContains (double sizeLength, double sizeWidth, double pointX, double pointY);
int objectReceiverContains (double sizeLength, double sizeWidth,int angle, double positionObject[],double positionReceiver[]);
std::vector<double> positionMoveObject (double positionInitObject[],double objectMovingSpeed,int angle,unsigned int time);


#endif // DETECTION_H
