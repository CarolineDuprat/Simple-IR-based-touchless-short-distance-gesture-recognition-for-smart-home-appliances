#include "simulationReceiver.h"

/**
 * @brief simulationTime Calculation the total time of the simulation [ms]
 * The object must travel from (x,y) to (-x,-y). So the total distance is the initial distance * 2
 * We know also the speed of the object.
 * So we can know the total time of the simulation : t = (total distance ) / vitesse
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @return the total time of the simulation [ms]
 */
uint16_t simulationTime (uint16_t distance,uint16_t speed){
    // Conversion of m/s to cm/ms : speed[m/s] = speed[cm/ms]*1/10
    // t [ms] = (total distance [cm] ) / vitesse [cm/ms] = ( 2 * distance [cm] ) / ( vitesse [m/s] * 1/10 )
    //                                                   = 10 * ( 2 * distance [cm] ) / ( vitesse [m/s] )
    uint16_t time=10*(distance*2)/speed;
    // the result of the calcul " 10*(distance*2)/speed " is a double not a int, so when we write " int time " we lose the decimal part
    //example: if reel time is 5.6 => time=5; but we want to travel the whole distance => time = time+1
    if (time < 10*(distance*2)/speed){
        time += 1;
    }
    return time;
}
/**
 * @brief HorizontalAndVerticalSpeed Calculation the horizontal and vertical speeds and the initial position of the object
 * Initial position : We know the distance of the object and the angular position of the object, so we can project this point to know its position in the orthormed frame
 * Horizontal and vertical speed : The calculation of these speeds makes it easier to know the position of the object at all times
 *                                 We know the total distance and the total time => vitesse = distance / time
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @param angle Angular position of the obstacle [°]
 * @return retour.pos : position of the object [cm]
 *         retour.speed : horizontal and vertical speed [cm/ms]
 */
returnSpeedPos HorizontalAndVerticalSpeed (double distance,double  speed,double  angle){
    double angleRad;
    float totalTime;
    returnSpeedPos retour;

    // Convert degree to radian
    angleRad = angle * PI / 180;

    // Initial position
    // cos = adjacent / hypotenuse = xInit / distance
    int16_t xInit = distance*cos(angleRad);
    retour.pos.x=xInit;
    // sin = opposite / hypotenuse = yInit / distance
    int16_t yInit = distance*sin(angleRad);
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
        retour.speed.hor=(2*abs(xInit))/totalTime;
    }// Else, the object moves to decreasing x
    else{
        retour.speed.hor=-(2*abs(xInit)/totalTime);
    }
    // VerticalSpeed [cm/ms]
    // Vitesse horizontal =  |yInit| * 2  / totalTime
    if ((-yInit)>yInit){
        retour.speed.vert=(2*abs(yInit))/totalTime;
    }else{
        retour.speed.vert=-(2*abs(yInit)/totalTime);
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
position positionMoveObject (returnSpeedPos information ,uint16_t time){
    position positionObject;

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
 * with the dimension of the object. Then we will apply a rotation to these points (matrix rotation)to know the real position of the points at t = 0
 * @param dimensionObject dimension of the object [cm]
 * @param angle Angular position of the obstacle [°]
 * @return position of corners
 */
corner rotationCorner (dimension dimensionObject,uint16_t angle){
    corner positionCorner,positionCornerRotation;
    double rotRad;

    //Assume that the rectangle is aligned with the x and y axes
    //Position c1 : (l/2,w/2);
    positionCorner.c[0].x=dimensionObject.length/2;
    positionCorner.c[0].y=dimensionObject.width/2;
    //Position c2 : (l/2,-w/2)
    positionCorner.c[1].x=dimensionObject.length/2;
    positionCorner.c[1].y=-dimensionObject.width/2;
    //Position c3 : (-l/2,-w/2)
    positionCorner.c[2].x=-dimensionObject.length/2;
    positionCorner.c[2].y=-dimensionObject.width/2;
    //Position c4 : (-l/2,w/2)
    positionCorner.c[3].x=-dimensionObject.length/2;
    positionCorner.c[3].y=dimensionObject.width/2;

    //Convert degree to radian
    rotRad = angle * PI / 180;

    // Rotation matrix : ( xProj )   =   (  cos (angle)     - sin (angle)   ) ( dx )
    //                   ( yProj )       (  sin (angle)       cos (angle)   ) ( dy )
    // xProj = cos (angle)*dx + (- sin (angle))*dy
    // yProj = sin (angle)*dx + cos (angle)*dy

    //Position Rotation :
    for (uint16_t i=0;i<4;i++){
        positionCornerRotation.c[i].x=positionCorner.c[i].x*cos(rotRad) - positionCorner.c[i].y*sin(rotRad);
        positionCornerRotation.c[i].y=positionCorner.c[i].x*sin(rotRad) + positionCorner.c[i].y*cos(rotRad);
    }

    return positionCornerRotation;
}

/**
 * @brief ReceiverCovered allows to know if the point is in a convex polygon. The point will be inside a
 * convex polygon if and only if it lies on the same side of the support line of each of the segments.
 * Calcul all the determinant, and check the result
 * If all signs are the same => receiver is in the rectangle
 * @param positionObject position of the object [cm]
 * @param positionReceiver position of the receiver [cm]
 * @param positionCornerRotation position of corners [cm]
 * @return 1 : the receiver is in the rectangle
 *         0 : the receiver is not in the rectangle
 */
uint8_t ReceiverCovered (position positionReceiver,corner positionCorner){
    uint8_t result=1;
    int16_t signFinal=0,sign=0;

    //Check the sign between det(C1C2,C1R) and det(C2C3,C2R)
    signFinal = signdet (positionCorner.c[0],positionCorner.c[1],positionReceiver);
    sign = signdet (positionCorner.c[1],positionCorner.c[2],positionReceiver);
    if (signFinal==0){
        signFinal= sign;
    }else if ((signFinal!= sign)&&(sign!=0)){
        result=0;
    }
    //Check the sign between det(C1C2,C1R) and det(C3C4,C3R)
    if (result==1){
        sign = signdet (positionCorner.c[2],positionCorner.c[3],positionReceiver);
        if (signFinal==0){
            signFinal= sign;
        }else if ((signFinal!= sign)&&(sign!=0)){
            result=0;
        }
    }
    //Check the sign between det(C1C2,C1R) and det(C4C1,C4R)
    if (result == 1){
        sign=signdet (positionCorner.c[3],positionCorner.c[0],positionReceiver);
        if (signFinal==0){
            signFinal= sign;
        }else if ((signFinal!= sign)&&(sign!=0)){
            result=0;
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
corner ReelPositionCorner (position positionObject,corner positionCornerRotation){
    corner positionCorner;
    double x=positionObject.x,y=positionObject.y;

    // The position of the object is not (0,0), it's (x,y)
    for (uint8_t i=0;i<4;i++){
        positionCorner.c[i].x=positionCornerRotation.c[i].x + x;
        positionCorner.c[i].y=positionCornerRotation.c[i].y + y;
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
int16_t signdet (position positionCorner1,position positionCorner2,position positionReceiver){
    position vecteurC1C2,vecteurC1R;
    int sign=0,determinant;

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
/**
 * @brief linearRelation eq : Ax + By = 0,  A= coefficient[0], B= coefficient[1]
 * @param direction Angular position of the obstacle [°]
 * @return coefficient ( A & B ), if A=0 & B=0 => Parameter error
 */
coef linearRelation (uint16_t direction)
{
    double x,y,angleRad;
    coef coefficient;
    //Check Paramaters
    if (direction>359){
        coefficient.A=0;
        coefficient.B=0;
    }else{
        if ((direction == 0)||(direction == 180)){
            coefficient.A=0;
            coefficient.B=1;
        }
        else if ((direction == 90)||(direction == 270)){
            coefficient.A=1;
            coefficient.B=0;
        }
        else if ((direction < 90)||(direction > 270)){
            angleRad = direction * PI / 180;
            //Fixed x
            x= 5;
            // Calcul y with trigonometric relationship
            y= x*tan(angleRad);
            coefficient.A=-(y/x);
            coefficient.B=1;
        }
        else{
            angleRad = direction * PI / 180;
            //Fixed x
            x= - 5;
            // Calcul y with trigonometric relationship
            y= x*tan(angleRad);
            coefficient.A=-(y/x);
            coefficient.B=1;
        }
    }
    return coefficient;
}
/**
 * @brief distanceMaxReceiverLinearRelationTab Calculution of the maximum distance between the line and receivers (Positions of receivers are in a tab)
 * To have information on the line formed by the direction, we must calculate the coefficients of the line, these calculations are carried out in the function "linearRelation".
 * Then it calculates the distance between each receivers and this line. We return the greatest distance.
 * @param direction Angular position of the obstacle [°]
 * @param positionReceiver all positions of receiver [cm]
 * @param nbrReceiver number of Receiver
 * @return maximum distance between the line and receivers, if distanceMax=0 => Parameter error
 */
uint16_t distanceMaxReceiverLinearRelationTab (uint16_t direction,infoSystem positionReceiver){
    uint16_t distanceMax=0,distance;
    //Check Paramaters
    if ((direction>359)||(positionReceiver.numberReceivers<1)){
        distanceMax=0;
    }else{
        //Calcul coefficients A and B of the direction line
        coef coefficient = linearRelation (direction);
        //Check return value of the function linearRelation
        if ((coefficient.A==0)&&(coefficient.B==0)){
            distanceMax=0;
        }else{
            for (uint16_t compteur=0; compteur < positionReceiver.numberReceivers ; compteur++){
                //Calcul the distance between the receiver and the direction line
                //                   | A * X + B * Y |
                //    distance = ------------------------
                //                | sqrt ( A*A + B*B ) |
                distance = fabs(((coefficient.A*positionReceiver.pos[compteur].x)+(coefficient.B*positionReceiver.pos[compteur].y))/sqrt(pow(coefficient.A,2)+pow(coefficient.B,2)));

                // Maximum distance
                if (distance > distanceMax){
                    distanceMax=distance;
                }
            }
        }
    }
    return distanceMax;
}
