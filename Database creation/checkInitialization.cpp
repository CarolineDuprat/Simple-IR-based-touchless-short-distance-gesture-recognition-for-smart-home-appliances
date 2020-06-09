#include "checkInitialization.h"
using namespace std;

/**
 * @brief checkAllParameters check the value of all parameters
 * @param nbrReceiver number of receiver
 * @param positionReceiver position x and y of all paramaters [cm]
 * @param angle Angular position of the obstacle [°]
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @param sizeWidth rectangle width [cm]
 * @param sizeLength rectangle length [cm]
 * @return true : No Error ; false : Error Parameters
 */

bool checkAllParameters (int const nbrReceiver,double const positionReceiver[][2],int const angle,double const distance,double const speed,double const sizeWidth,double const sizeLength){
    bool check(true);
    double distancemin(distanceMaxReceiverLinearRelation(angle,positionReceiver,nbrReceiver));
    //Check Paramaters
    if ((angle<0)||(angle>359)||(sizeLength<=0)||(speed<=0)||(distance<=0)||(distancemin==0)){
        check=false;
        cout << "Error Parameters" << endl;
    // Check if the width is large enough to cover all sensors
    }if (sizeWidth<distancemin*2){
        cout << "Error, sizeWidth > " << distancemin*2 << endl;
        check=false;
    }
    return check;
}

/**
 * @brief linearRelation eq : Ax + By = 0,  A= coefficient[0], B= coefficient[1]
 * @param direction Angular position of the obstacle
 * @return coefficient ( A & B ), if A=0 & B=0 => Parameter error
 */
std::vector <double> linearRelation (int const direction)
{
    double x,y,angleRad;
    vector <double> coefficient(2);
    //Check Paramaters
    if ((direction<0)||(direction>359)){
        coefficient[0]=0;
        coefficient[1]=0;
    }else{
        if ((direction == 0)||(direction == 180)){
            coefficient[0]=0;
            coefficient[1]=1;
        }
        else if ((direction == 90)||(direction == 270)){
            coefficient[0]=1;
            coefficient[1]=0;
        }
        else if ((direction < 90)||(direction > 270)){
            angleRad = direction * PI / 180;
            //Fixed x
            x= 5;
            // Calcul y with trigonometric relationship
            y= x*tan(angleRad);
            coefficient[0]=-(y/x);
            coefficient[1]=1;
        }
        else{
            angleRad = direction * PI / 180;
            //Fixed x
            x= - 5;
            // Calcul y with trigonometric relationship
            y= x*tan(angleRad);
            coefficient[0]=-(y/x);
            coefficient[1]=1;
        }
    }
    return coefficient;
}
/**
 * @brief distanceMaxReceiverLinearRelation Calculution of the maximum distance between the line and receivers
 * @param direction Angular position of the obstacle
 * @param positionReceiver all positions of receiver
 * @param nbrReceiver number of Receiver
 * @return maximum distance between the line and receivers, if distanceMax=0 => Parameter error
 */
double distanceMaxReceiverLinearRelation (int const direction,double const positionReceiver[][2],int const nbrReceiver){
    double distanceMax(0),distance;
    //Check Paramaters
    if ((direction<0)||(direction>359)||(nbrReceiver<1)){
        distanceMax=0;
    }else{
        //Calcul coefficients A and B of the direction line
        std::vector <double> coefficient = linearRelation (direction);
        //Check return value of the function linearRelation
        if ((coefficient[0]==0)&&(coefficient[1]==0)){
            distanceMax=0;
        }else{
            for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
                //Calcul the distance between the receiver and the direction line
                //                   | A * X + B * Y |
                //    distance = ------------------------
                //                | sqrt ( A*A + B*B ) |
                distance = fabs(((coefficient[0]*positionReceiver[compteur][0])+(coefficient[1]*positionReceiver[compteur][1]))/sqrt(pow(coefficient[0],2)+pow(coefficient[1],2)));
                // Maximum distance
                if (distance > distanceMax){
                    distanceMax=distance;
                }
            }
        }
    }
    return distanceMax;
}
