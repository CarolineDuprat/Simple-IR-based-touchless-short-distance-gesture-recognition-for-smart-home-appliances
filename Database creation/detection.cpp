#include "detection.h"


/**
 * @brief rectanglePointContains allows to know if the point is in the rectangle coordinate (0,0)
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param pointX x point coordinate
 * @param pointY y point coordinate
 * @return true if the point is in the rectangle, if not return false
 */
bool rectanglePointContains (double sizeLength, double sizeWidth, double pointX, double pointY)
{
    bool result (false);
    if ((pointX >= 0)&& (pointX <= sizeLength))
    {
        if ((pointY >= 0)&& (pointY <= sizeWidth))
        {
            result = true;
        }
    }
    return result;
}

/**
 * @brief objectReceiverContains allows to know if the object is in front of the receiver
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param angle Angular position of the obstacle
 * @param positionObject position (x,y) object , it's the position of the top front left
 * @param positionReceiver position (x,y) receiver
 * @return true if the object is in front of the receiver, if not return false
 */
bool objectReceiverContains (double sizeLength, double sizeWidth,int angle, double positionObject[],double positionReceiver[])
{
    double dx,dy,rotRad,xProj,yProj;

    dx = positionReceiver[0] - positionObject [0];
    dy = positionReceiver[1] - positionObject [1];

    rotRad = angle * PI / 180;
    xProj = cos(rotRad)*dx + sin(rotRad)*dy;
    yProj = - sin(rotRad)*dx + cos(rotRad)*dy;

    return rectanglePointContains (sizeLength,sizeWidth, xProj, yProj);
}
/**
 * @brief positionMoveObject calculate the new position of the object after a "time" at a speed objectMovingSpeed
 * @param positionInitObject initial position of the object
 * @param objectMovingSpeed speed of the object
 * @param angle Angular position of the obstacle
 * @param time the time since the launch of the simulation
 * @return the current position of the object
 */
vector<double> positionMoveObject (double positionInitObject[],double objectMovingSpeed,int angle,unsigned int time)
{
    vector<double> result(2);
    double angleRad;
    double distance = time * objectMovingSpeed/10  ;
    angleRad = angle * PI / 180;
    result[0] = positionInitObject[0] - distance*cos(angleRad);
    result[1] = positionInitObject[1] - distance*sin(angleRad);

    return result;
}
