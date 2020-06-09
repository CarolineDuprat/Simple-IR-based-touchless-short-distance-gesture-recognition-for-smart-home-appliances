#include "simulationReceiver.h"
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
 * @return result[0] : x Intial position [cm], result[1] : y Intial position [cm]
 *         result[2] : HorizontalSpeed [cm/ms], result[3] : VerticalSpeed [cm/ms]
 *         result[4] : 1 No error parameters ; 0 Error
 */
std::vector<double> HorizontalAndVerticalSpeed (double const distance,double const speed,int const angle){
    std::vector<double> result(5);
    double angleRad;
    int totalTime;
    //Check parameters
    if ((speed<=0)||(angle<0)||(angle>359)){
        result[4]=0;
    }else{
        //No error parameters
        result[4]=1;

        angleRad = angle * PI / 180;

        //Initial position
        double xInit = distance*cos(angleRad);
        result[0]=xInit;
        double yInit = distance*sin(angleRad);
        result[1]=yInit;

        //Total speed [ms]
        totalTime=simulationTime (distance,speed);

        //HorizontalSpeed [cm/ms]
        if ((-xInit)>xInit){
            result[2]=2*fabs(xInit)/totalTime;
        }else{
            result[2]=-(2*fabs(xInit)/totalTime);
        }
        //VerticalSpeed [cm/ms]
        if ((-yInit)>yInit){
            result[3]=2*fabs(yInit)/totalTime;
        }else{
            result[3]=-(2*fabs(yInit)/totalTime);
        }
    }
    return result;
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
