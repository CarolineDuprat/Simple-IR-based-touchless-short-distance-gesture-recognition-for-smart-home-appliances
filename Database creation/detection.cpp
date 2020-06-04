#include "detection.h"


/**
 * @brief rectanglePointContains allows to know if the point is in the rectangle coordinate (0,0)
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param pointX x point coordinate
 * @param pointY y point coordinate
 * @return 1 if the point is in the rectangle, 0 if the point is not in the rectangle, -1 error parameter
 */
int rectanglePointContains (double sizeLength, double sizeWidth, double pointX, double pointY)
{
    int result (0);
    if ((sizeLength<=0)||(sizeWidth<=0)){
        result=-1;
    }else{
        if ((pointX >= 0)&& (pointX <= sizeLength))
        {
            if ((pointY >= 0)&& (pointY <= sizeWidth))
            {
                result = 1;
            }
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
 * @return 1 if the object is in front of the receiver, 0 if the object is not in front of the receiver, -1 error parameter
 */
int objectReceiverContains (double sizeLength, double sizeWidth,int angle, double positionObject[],double positionReceiver[])
{
    double dx,dy,rotRad,xProj,yProj;
    int retour;
    if ((sizeLength<=0)||(sizeWidth<=0)||(angle<0)||(angle>359)){
        retour=-1;
    }else{
        dx = positionReceiver[0] - positionObject [0];
        dy = positionReceiver[1] - positionObject [1];

        rotRad = angle * PI / 180;
        xProj = cos(rotRad)*dx + sin(rotRad)*dy;
        yProj = - sin(rotRad)*dx + cos(rotRad)*dy;
        retour = rectanglePointContains (sizeLength,sizeWidth, xProj, yProj);
    }
    return retour;
}
/**
 * @brief positionMoveObject calculate the new position of the object after a "time" at a speed objectMovingSpeed
 * @param positionInitObject initial position of the object
 * @param objectMovingSpeed speed of the object
 * @param angle Angular position of the obstacle
 * @param time the time since the launch of the simulation
 * @return the current position of the object, if result[2] == 0 => erreur
 */
vector<double> positionMoveObject (double positionInitObject[],double objectMovingSpeed,int angle,unsigned int time)
{
    vector<double> result(3);
    double angleRad;
    if ((objectMovingSpeed<=0)||(angle<0)||(angle>359)){
        result[2]=0;
    }else{
        double distance = time * objectMovingSpeed/10  ;
        angleRad = angle * PI / 180;
        result[0] = positionInitObject[0] - distance*cos(angleRad);
        result[1] = positionInitObject[1] - distance*sin(angleRad);
        result[2]=1;
    }
    return result;
}
