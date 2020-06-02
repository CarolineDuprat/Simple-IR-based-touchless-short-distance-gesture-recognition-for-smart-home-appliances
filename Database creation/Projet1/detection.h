#ifndef DETECTION_H
#define DETECTION_H
#define PI 3.141592
#include <vector>
#include <string>
#include <cmath>

bool rectanglePointContains (double sizeLength, double sizeWidth, double pointX, double pointY);
bool objectReceiverContains (double sizeLength, double sizeWidth,int angle, double positionObject[],double positionReceiver[]);


#endif // DETECTION_H
