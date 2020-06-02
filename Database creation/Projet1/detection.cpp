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
 * @param sizeLength rectangle width
 * @param sizeWidth rectangle length
 * @param angle Angular position of the obstacle
 * @param positionObject position (x,y) object
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
