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
 * @param positionReceiver position receiver [cm]
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
/**
 * @brief rotationCorner Center of the object (0,0), Obtained position of corners after rotation
 * @param dimensionObject dimension of the object [cm]
 * @param angle Angular position of the obstacle [°]
 * @return position of corners
 */
posCorner rotationCorner (dimension dimensionObject,int angle){
    posCorner positionCorner,positionCornerRotation;
    double rotRad;

    //Position c1 : (l/2,w/2)
    positionCorner.c1.x=dimensionObject.length/2;
    positionCorner.c1.y=dimensionObject.width/2;
    //Position c2 : (l/2,-w/2)
    positionCorner.c2.x=dimensionObject.length/2;
    positionCorner.c2.y=-dimensionObject.width/2;
    //Position c3 : (-l/2,-w/2)
    positionCorner.c3.x=-dimensionObject.length/2;
    positionCorner.c3.y=-dimensionObject.width/2;
    //Position c4 : (-l/2,w/2)
    positionCorner.c4.x=-dimensionObject.length/2;
    positionCorner.c4.y=dimensionObject.width/2;

    //Convert degree to radian
    rotRad = angle * PI / 180;

    // Rotation matrix : ( xProj )   =   (  cos (angle)     - sin (angle)   ) ( dx )
    //                   ( yProj )       (  sin (angle)       cos (angle)   ) ( dy )

    //Position c1 Rotation :
    positionCornerRotation.c1.x=positionCorner.c1.x*cos(rotRad) - positionCorner.c1.y*sin(rotRad);
    positionCornerRotation.c1.y=positionCorner.c1.x*sin(rotRad) + positionCorner.c1.y*cos(rotRad);
    //Position c2 Rotation :
    positionCornerRotation.c2.x=positionCorner.c2.x*cos(rotRad) - positionCorner.c2.y*sin(rotRad);
    positionCornerRotation.c2.y=positionCorner.c2.x*sin(rotRad) + positionCorner.c2.y*cos(rotRad);
    //Position c3 Rotation :
    positionCornerRotation.c3.x=positionCorner.c3.x*cos(rotRad) - positionCorner.c3.y*sin(rotRad);
    positionCornerRotation.c3.y=positionCorner.c3.x*sin(rotRad) + positionCorner.c3.y*cos(rotRad);
    //Position c4 Rotation :
    positionCornerRotation.c4.x=positionCorner.c4.x*cos(rotRad) - positionCorner.c4.y*sin(rotRad);
    positionCornerRotation.c4.y=positionCorner.c4.x*sin(rotRad) + positionCorner.c4.y*cos(rotRad);


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
bool ReceiverCovered (position_t positionReceiver,posCorner positionCorner){
    bool result(true);
    int signFinal,sign;

    //Check the sign between det(C1C2,C1R) and det(C2C3,C2R)
    signFinal= signdet (positionCorner.c1,positionCorner.c2,positionReceiver);
    sign=signdet (positionCorner.c2,positionCorner.c3,positionReceiver);
    if (signFinal==0){
        signFinal= sign;
    }else if ((signFinal!= sign)&&(sign!=0)){
        result=false;
    }
    //Check the sign between det(C1C2,C1R) and det(C3C4,C3R)
    if (result==true){
        sign=signdet (positionCorner.c3,positionCorner.c4,positionReceiver);
        if (signFinal==0){
            signFinal= sign;
        }else if ((signFinal!= sign)&&(sign!=0)){
            result=false;
        }
    }
    //Check the sign between det(C1C2,C1R) and det(C4C1,C4R)
    if (result==true){
        sign=signdet (positionCorner.c4,positionCorner.c1,positionReceiver);
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
 * @param positionObject positionObject [cm]
 * @param positionCornerRotation position corner after the rotation, the origin is the center of the object [cm]
 * @return  reel position of corners [cm]
 */
posCorner ReelPositionCorner (position_t positionObject,posCorner positionCornerRotation){
    posCorner positionCorner;
    double x(positionObject.x),y(positionObject.y);

    // The position of the object is not (0,0), it's (x,y)
    positionCorner.c1.x=positionCornerRotation.c1.x + x;
    positionCorner.c1.y=positionCornerRotation.c1.y + y;
    positionCorner.c2.x=positionCornerRotation.c2.x + x;
    positionCorner.c2.y=positionCornerRotation.c2.y + y;
    positionCorner.c3.x=positionCornerRotation.c3.x + x;
    positionCorner.c3.y=positionCornerRotation.c3.y + y;
    positionCorner.c4.x=positionCornerRotation.c4.x + x;
    positionCorner.c4.y=positionCornerRotation.c4.y + y;

    cout << "Position Corner,( "<< positionObject.x<<" , "<<positionObject.y<<" ): Position of the center of the object  " << endl;
    cout << "c1 : "<<positionCorner.c1.x << " , "<<positionCorner.c1.y << endl;
    cout << "c2 : "<<positionCorner.c2.x << " , "<<positionCorner.c2.y << endl;
    cout << "c3 : "<<positionCorner.c3.x << " , "<<positionCorner.c3.y << endl;
    cout << "c4 : "<<positionCorner.c4.x << " , "<<positionCorner.c4.y << endl;

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
