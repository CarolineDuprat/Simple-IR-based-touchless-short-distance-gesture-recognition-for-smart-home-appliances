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
 * The object must travel from (x,y) to (-x,-y). So the total distance is the initial distance * 2
 * We know also the speed of the object.
 * So we can know the total time of the simulation : t = (total distance ) / vitesse
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @return the total time of the simulation [ms]
 */
int simulationTime (double const distance,double const speed){
    // Conversion of m/s to cm/ms : speed[m/s] = speed[cm/ms]*1/10
    // t [ms] = (total distance [cm] ) / vitesse [cm/ms] = ( 2 * distance [cm] ) / ( vitesse [m/s] * 1/10 )
    //                                                   = 10 * ( 2 * distance [cm] ) / ( vitesse [m/s] )
    int time=10*(distance*2)/speed;
    // the result of the calcul " 10*(distance*2)/speed " is a double not a int, so when we write " int time " we lose the decimal part
    //example: if reel time is 5.6 => time=5; but we want to travel the whole distance => time = time+1
    if (time < 10*(distance*2)/speed){
        time += 1;
    }
    return time;
}
/**
 * @brief HorizontalAndVerticalSpeed Calcul the horizontal and vertical speed and the initial position of the object
 * Initial position : We know the distance of the object and the angular position of the object, so we can project this point to know its position in the orthormed frame
 * Horizontal and vertical speed : The calculation of these speeds makes it easier to know the position of the object at all times
 *                                 We know the total distance and the total time => vitesse = distance / time
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

    // Convert degree to radian
    angleRad = angle * PI / 180;

    // Initial position
    // cos = adjacent / hypotenuse = xInit / distance
    double xInit = distance*cos(angleRad);
    retour.pos.x=xInit;
    // sin = opposite / hypotenuse = yInit / distance
    double yInit = distance*sin(angleRad);
    retour.pos.y=yInit;

    // Total speed [ms]
    totalTime=simulationTime (distance,speed);

    // HorizontalSpeed [cm/ms]
    // vitesse = distance / time
    // the total time of the simulation is calcul in the function simulationTime, the result is totalTime
    // the total distance is |xInit| * 2
    // Vitesse horizontal =  |xInit| * 2  / totalTime
    // The sens of the vitesse allows to know is the object moves to increasing or decreasing x
    // If (-xInit)>xInit , the object moves to increasing x
    if ((-xInit)>xInit){
        retour.speed.hor=2*fabs(xInit)/totalTime;
    }// Else, the object moves to decreasing x
    else{
        retour.speed.hor=-(2*fabs(xInit)/totalTime);
    }
    // VerticalSpeed [cm/ms]
    // Vitesse horizontal =  |yInit| * 2  / totalTime
    if ((-yInit)>yInit){
        retour.speed.vert=2*fabs(yInit)/totalTime;
    }else{
        retour.speed.vert=-(2*fabs(yInit)/totalTime);
    }

    return retour;
}
/**
 * @brief positionMoveObject Calcul the position of the object
 * In the function HorizontalAndVerticalSpeed, we calculated the initial position of the object, as well as the horizontal and vertical speeds
 * So we can calculate the position traveled by the object at all times, and add this distance to the initial position to know the position of the object
 * @param information return of the function HorizontalAndVerticalSpeed :
 *         information.pos position of the object [cm]
 *         information.speed : horizontal and vertical speeds [cm/ms]
 * @param time time of the simulation [ms]
 * @return positionObject [cm]
 */
position_t positionMoveObject (returnSpeedPos information ,unsigned int time){
    position_t positionObject;

    // x Object = x Intial Object + HorizontalSpeed * time
    positionObject.x = information.pos.x + information.speed.hor*time;
    // y Object = y Intial Object + VerticalSpeed * time
    positionObject.y = information.pos.y + information.speed.vert*time;

    return positionObject;
}
/**
 * @brief rotationCorner Center of the object (0,0), Obtained position of corners after rotation
 * To know the position of the corners of the rectangle, we will first assume that the rectangle
 * is aligned with the x and y axes, so it will be easy to calculate the position of the corners
 * with the dimension of the object. Then we will apply a rotation to these points (matrix rotation)
 * @param dimensionObject dimension of the object [cm]
 * @param angle Angular position of the obstacle [°]
 * @return position of corners
 */
std::vector<position_t> rotationCorner (dimension dimensionObject,int angle){
    std::vector<position_t> positionCorner(4),positionCornerRotation(4);
    double rotRad;

    //Assume that the rectangle is aligned with the x and y axes
    //Position c1 : (l/2,w/2);
    positionCorner[0].x=dimensionObject.length/2;
    positionCorner[0].y=dimensionObject.width/2;
    //Position c2 : (l/2,-w/2)
    positionCorner[1].x=dimensionObject.length/2;
    positionCorner[1].y=-dimensionObject.width/2;
    //Position c3 : (-l/2,-w/2)
    positionCorner[2].x=-dimensionObject.length/2;
    positionCorner[2].y=-dimensionObject.width/2;
    //Position c4 : (-l/2,w/2)
    positionCorner[3].x=-dimensionObject.length/2;
    positionCorner[3].y=dimensionObject.width/2;

    //Convert degree to radian
    rotRad = angle * PI / 180;

    // Rotation matrix : ( xProj )   =   (  cos (angle)     - sin (angle)   ) ( dx )
    //                   ( yProj )       (  sin (angle)       cos (angle)   ) ( dy )
    // xProj = cos (angle)*dx + (- sin (angle))*dy
    // yProj = sin (angle)*dx + cos (angle)*dy

    //Position Rotation :
    for (int i(0);i<4;i++){
        positionCornerRotation[i].x=positionCorner[i].x*cos(rotRad) - positionCorner[i].y*sin(rotRad);
        positionCornerRotation[i].y=positionCorner[i].x*sin(rotRad) + positionCorner[i].y*cos(rotRad);
    }

    return positionCornerRotation;
}
/**
 * @brief ReceiverCovered allows to know if the point is in a convex polygon. Calcul all the determinant, and check the result
 * If all signs are the same => receiver is in the rectangle
 * @param positionObject position of the object [cm]
 * @param positionReceiver position of the receiver [cm]
 * @param positionCornerRotation position of corners [cm]
 * @return true : the receiver is in the rectangle
 *        false : the receiver is not in the rectangle
 */
bool ReceiverCovered (position_t positionReceiver,std::vector<position_t> positionCorner){
    bool result(true);
    int signFinal,sign;

    //Check the sign between det(C1C2,C1R) and det(C2C3,C2R)
    signFinal= signdet (positionCorner[0],positionCorner[1],positionReceiver);
    sign=signdet (positionCorner[1],positionCorner[2],positionReceiver);
    if (signFinal==0){
        signFinal= sign;
    }else if ((signFinal!= sign)&&(sign!=0)){
        result=false;
    }
    //Check the sign between det(C1C2,C1R) and det(C3C4,C3R)
    if (result==true){
        sign=signdet (positionCorner[2],positionCorner[3],positionReceiver);
        if (signFinal==0){
            signFinal= sign;
        }else if ((signFinal!= sign)&&(sign!=0)){
            result=false;
        }
    }
    //Check the sign between det(C1C2,C1R) and det(C4C1,C4R)
    if (result==true){
        sign=signdet (positionCorner[3],positionCorner[0],positionReceiver);
        if (signFinal==0){
            signFinal= sign;
        }else if ((signFinal!= sign)&&(sign!=0)){
            result=false;
        }
    }

    return result;
}
/**
 * @brief ReelPositionCorner translation of the origin
 * In the function rotationCorner, we calculated the position of the corners assuming that the center
 * of the rectangle is (0,0), except that the position of the object is not that, it changes with time
 * we calculate the position of the object in the function positionMoveObject
 * so the actual position of the corners is positionCorner + positionObject
 * @param positionObject positionObject [cm]
 * @param positionCornerRotation position corner after the rotation, the origin is the center of the object [cm]
 * @return  reel position of corners [cm]
 */
std::vector<position_t> ReelPositionCorner (position_t positionObject,std::vector<position_t> positionCornerRotation){
    std::vector<position_t> positionCorner(4);
    double x(positionObject.x),y(positionObject.y);

    // The position of the object is not (0,0), it's (x,y)
    for (int i(0);i<4;i++){
        positionCorner[i].x=positionCornerRotation[i].x + x;
        positionCorner[i].y=positionCornerRotation[i].y + y;
    }

#if 0
    cout << "Position Corner,( "<< positionObject.x<<" , "<<positionObject.y<<" ): Position of the center of the object  " << endl;
    for (int i(0);i<4;i++){
        cout << "c" << i <<" : "<< positionCorner[i].x << " , "<< positionCorner[i].y << endl;
    }
#endif
    //cout << ", " << positionObject.x << ", " << positionObject.y;
    for (int i=0 ; i<4 ; i++){
        cout << ", " << positionCorner[i].x << ", " << positionCorner[i].y;
    }
    return positionCorner;
}
/**
 * @brief signdet calculation of the determinant between the vector C1C2 and the vector C1R, allows to know if the receiver is in the left or in the right of the vector C1C2
 * @param positionCorner1 position of the corner 1 [cm]
 * @param positionCorner2 position of the corner 2 [cm]
 * @param positionReceiver position of the receiver [cm]
 * @return 0 : vectors are aligned
 *         1 : determinant is positive
 *        -1 : determinant is negative
 */
int signdet (position_t positionCorner1,position_t positionCorner2,position_t positionReceiver){
    position_t vecteurC1C2,vecteurC1R;
    int sign(0),determinant;

    // Calcul vecteur C1C2 : C1 ( x ) , C2 ( x' )   /C1C2 ( x' - x )
    //                          ( y ) ,    ( y' )         ( y' - y )
    vecteurC1C2.x=positionCorner2.x - positionCorner1.x;
    vecteurC1C2.y=positionCorner2.y - positionCorner1.y;
    //Calcul vecteur C1R
    vecteurC1R.x=positionReceiver.x - positionCorner1.x;
    vecteurC1R.y=positionReceiver.y - positionCorner1.y;

    //Calcul determinant /C1C2 & /C1R
    // det(/C1C2,/C1R)=det ( (x) , (x') )=xy' - x'y
    //                     ( (y) , (y') )
    determinant=vecteurC1C2.x * vecteurC1R.y -  vecteurC1R.x * vecteurC1C2.y;

    if (determinant>0){
        sign=1;
    }else if (determinant<0){
        sign=-1;
    }
    return sign;
}
