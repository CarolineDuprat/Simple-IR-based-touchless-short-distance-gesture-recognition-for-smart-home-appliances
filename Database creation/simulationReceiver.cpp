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
    int time=10*(distance*2)/speed;
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
 *         information[0] : x Intial position [cm], information[1] : y Intial position [cm]
 *         information[2] : HorizontalSpeed [cm/ms], information[3] : VerticalSpeed [cm/ms]
 *         information[4] : 1 No error parameters ; 0 Error
 * @param time time of the simulation [ms]
 * @return positionObject[0] : x position [cm]; positionObject[1] : y position [cm]
 */
std::vector<double> positionMoveObject (std::vector<double> information ,unsigned int time)
{
    std::vector<double> positionObject(2);

    // x Object = x Intial Object + HorizontalSpeed * time
    positionObject[0]=information[0]+information [2]*time;
    // y Object = y Intial Object + VerticalSpeed * time
    positionObject[1]=information[1]+information [3]*time;

    return positionObject;
}
/**
 * @brief objectInFrontofReceiver allows to know if the object is in front of the receiver
 * translation : change the position of the receiver to have the center of the object as origin
 * rotation : change the value of the position of the receiver to have a rectangle aligned to the axes x and y
 * use the function rectanglePointContains, It's now easy to know if the object is in the rectangle or not
 * @param positionObject position (x,y) object [cm]
 * @param sizeLength rectangle length [cm]
 * @param sizeWidth rectangle width [cm]
 * @param angle Angular position of the obstacle [°]
 * @param positionReceiverX position x receiver [cm]
 * @param positionReceiverY position y receiver [cm]
 * @return -1 : Error
 *          0 : the object is not in front of the receiver
 *          1 : the object is in front of the receiver
 */
int objectInFrontofReceiver (std::vector<double> positionObject,double sizeLength, double sizeWidth,int angle,double positionReceiverX,double positionReceiverY){
    double dx,dy,rotRad,xProj,yProj;
    int retour;
    if ((sizeLength<=0)||(sizeWidth<=0)||(angle<0)||(angle>359)){
        retour=-1;
    }else{
        //Change the origin of the coordinate system, now the origin is the center of the object
        dx = positionReceiverX - positionObject [0];
        dy = positionReceiverY - positionObject [1];
        rotRad = angle * PI / 180;
        // I make a rotation at the point. Now the object is a rectangle aligned with axes
        // Rotation matrix : ( xProj )   =   (  cos (angle)     - sin (angle)   ) ( dx )
        //                   ( yProj )       (  sin (angle)       cos (angle)   ) ( dy )
        xProj = cos(rotRad)*dx - sin(rotRad)*dy;
        yProj = sin(rotRad)*dx + cos(rotRad)*dy;
        retour = rectanglePointContains (sizeLength,sizeWidth, xProj, yProj);
    }
    return retour;
}
/**
 * @brief rectanglePointContains allows to know if the point is in the rectangle ( origin of the repere is the center of the object)
 * @param sizeLength rectangle length [cm]
 * @param sizeWidth rectangle width [cm]
 * @param pointX x point coordinate [cm]
 * @param pointY y point coordinate [cm]
 * @return 1 : if the point is in the rectangle
 *         0 : if the point is not in the rectangle
 *        -1 : error parameter
 */
int rectanglePointContains (double sizeLength, double sizeWidth, double pointX, double pointY){
    int result (0);
    if ((sizeLength<=0)||(sizeWidth<=0)){
        result=-1;
    }else{
        if ((pointX >= - sizeLength/2 )&& (pointX <= sizeLength/2))
        {
            if ((pointY >= - sizeWidth/2)&& (pointY <= sizeWidth/2))
            {
                result = 1;
            }
        }
    }
    return result;
}
