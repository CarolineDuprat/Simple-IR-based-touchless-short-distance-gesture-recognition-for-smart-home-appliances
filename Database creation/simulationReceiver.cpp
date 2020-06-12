/**
  * @file This file simulates the process.
  * Create a time in ms
  * Calcul the position of the object as a function of time
  * Determine if the object is in front of a receiver at an instant t (time)
  */

#include "simulationReceiver.h"
using namespace std;
/**
 * @brief simulationTime Calcul the total time of the simulation [ms]
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @return the total time of the simulation [ms]
 */
int simulationTime (double const distance,double const speed){
    // speed[m/s] = speed[cm/ms]*1/10
    int time=10*(distance*2)/speed;
    //example: if reel time is 5.6 => time=5; but we want to travel the whole distance => time = time+1
    if (time < 10*(distance*2)/speed){
        time += 1;
    }
    return time;
}
/**
 * @brief HorizontalAndVerticalSpeed Calcul the horizontal and vertical speed and the initial position of the object
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @param angle Angular position of the obstacle [°]
 * @return retour.pos : position of the object [cm]
 *         retour.speed : horizontal and vertical speed [cm/ms]
 */
returnSpeedPos HorizontalAndVerticalSpeed (double const distance,double const speed,int const angle){
    double angleRad;
    int totalTime;
    returnSpeedPos retour;

    //Convert degree to radian
    angleRad = angle * PI / 180;

    //Initial position
    double xInit = distance*cos(angleRad);
    retour.pos.x=xInit;
    double yInit = distance*sin(angleRad);
    retour.pos.y=yInit;

    //Total speed [ms]
    totalTime=simulationTime (distance,speed);

    //HorizontalSpeed [cm/ms]
    if ((-xInit)>xInit){
        retour.speed.hor=2*fabs(xInit)/totalTime;
    }else{
        retour.speed.hor=-(2*fabs(xInit)/totalTime);
    }
    //VerticalSpeed [cm/ms]
    if ((-yInit)>yInit){
        retour.speed.vert=2*fabs(yInit)/totalTime;
    }else{
        retour.speed.vert=-(2*fabs(yInit)/totalTime);
    }

    return retour;
}
/**
 * @brief positionMoveObject Calcul the position of the object
 * @param information return of the function HorizontalAndVerticalSpeed :
 *         information.pos position of the object [cm]
 *         information.speed : horizontal and vertical speed [cm/ms]
 * @param time time of the simulation [ms]
 * @return positionObject [cm]
 */
position_t positionMoveObject (returnSpeedPos information ,unsigned int time){
    position_t positionObject;

    // x Object = x Intial Object + HorizontalSpeed * time
    positionObject.x=information.pos.x+information.speed.hor*time;
    // y Object = y Intial Object + VerticalSpeed * time
    positionObject.y=information.pos.y+information.speed.vert*time;

    return positionObject;
}
/**
 * @brief objectInFrontofReceiver allows to know if the object is in front of the receiver
 * translation : change the position of the receiver to have the center of the object as origin
 * rotation : change the value of the position of the receiver to have a rectangle aligned to the axes x and y
 * use the function rectanglePointContains, It's now easy to know if the object is in the rectangle or not
 * @param positionObject position (x,y) object [cm]
 * @param dimensionObject dimension of the object [cm]
 * @param angle Angular position of the obstacle [°]
 * @param positionReceiverX position x receiver [cm]
 * @param positionReceiverY position y receiver [cm]
 * @return  false : the object is not in front of the receiver
 *          true : the object is in front of the receiver
 */
bool objectInFrontofReceiver (position_t positionObject,dimension dimensionObject,int angle,position_t positionReceiver){
    double rotRad;
    bool retour;
    position_t positionTranslation,positionRotation;

    //Change the origin of the coordinate system, now the origin is the center of the object
    positionTranslation.x = positionReceiver.x - positionObject.x;
    positionTranslation.y = positionReceiver.y - positionObject.y;

    //Convert degree to radian
    rotRad = angle * PI / 180;

    // I make a rotation at the point. Now the object is a rectangle aligned with axes
    // Rotation matrix : ( xProj )   =   (  cos (angle)     - sin (angle)   ) ( dx )
    //                   ( yProj )       (  sin (angle)       cos (angle)   ) ( dy )
    positionRotation.x = cos(rotRad)*positionTranslation.x - sin(rotRad)*positionTranslation.y;
    positionRotation.y = sin(rotRad)*positionTranslation.x + cos(rotRad)*positionTranslation.y;
    retour = rectanglePointContains (dimensionObject, positionRotation);

    return retour;
}
/**
 * @brief rectanglePointContains allows to know if the point is in the rectangle ( origin of the repere is the center of the object)
 * @param dimensionObject dimension of the object [cm]
 * @param positionRotation position of the object [cm]
 * @return true : if the point is in the rectangle
 *         false : if the point is not in the rectangle
 */
bool rectanglePointContains (dimension dimensionObject, position_t positionRotation){
    bool result(false);

    if ((positionRotation.x >= - dimensionObject.length/2 )&& (positionRotation.x <= dimensionObject.length/2))
    {
        if ((positionRotation.y >= - dimensionObject.width/2)&& (positionRotation.y <= dimensionObject.width/2))
        {
            result = true;
        }
    }

    return result;
}
