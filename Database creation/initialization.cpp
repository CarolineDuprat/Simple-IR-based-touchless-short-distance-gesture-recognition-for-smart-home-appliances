#include "initialization.h"

/**
 * @brief init initialization of all parameters
 * @param nbrReceiver number of Receiver
 * @param direction Angular position of the obstacle
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param objectMovingSpeed speed of the object
 * @param distance distance object
 * @return all positions of receiver, if the return is empty => error
 */
vector <double> init(int& nbrReceiver,int& direction,double& sizeLength,double& sizeWidth,double& objectMovingSpeed,double& distance)
{
    vector <double> positionReveiver;
    double x,y,sizeWidthMin;
    cout << "Start of initialization " << endl;
    do{
        cout << "Number of Receiver ?" << endl;
        cin >> nbrReceiver;
    }while (nbrReceiver <= 0);

    for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
        do{
            cout << "Position of receiver [cm] " << compteur << " x :" << endl;
            cin >> x;
            cout << " y :" << endl;
            cin >> y;
        }while ((x==0)&&(y==0));
        positionReveiver.push_back(x);
        positionReveiver.push_back(y);
    }
    do{
        cout << "Object direction ? [degree]  " << endl;
        cin >> direction;
    }while((direction>359)||(direction<0));
    sizeWidthMin=(distanceMaxReceiverLinearRelation (direction,positionReveiver,nbrReceiver)*2);
    if (sizeWidthMin==0){
        cout << "Error"<< endl;
        positionReveiver.clear();
    }
    else{
        do{
            cout << "Object size : width [cm] ? must be greater than " << sizeWidthMin <<" cm" << endl;
            cin >> sizeWidth;
        }while(sizeWidth<sizeWidthMin);
        do{
            cout << "length [cm] ?" << endl;
            cin >> sizeLength;
        }while(sizeLength<=0);
        do{
            cout << "Object speed ? [m/s] " << endl;
            cin >> objectMovingSpeed;
        }while(objectMovingSpeed<=0);
        do{
            cout << "Object distance [cm] ?  " << endl;
            cin >> distance;
        }while(distance<=0);
        cout << "End of initialization  " << endl;
    }
    return positionReveiver;
}
/**
 * @brief linearRelation eq : Ax + By = 0,  A= coefficient[0], B= coefficient[1]
 * @param direction Angular position of the obstacle
 * @return coefficient ( A & B ), if A=0 & B=0 => Parameter error
 */
vector <double> linearRelation (int direction)
{
    double x,y,angleRad;
    vector <double> coefficient(2);
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
            x= 5;
            y= x*tan(angleRad);
            coefficient[0]=-(y/x);
            coefficient[1]=1;
        }
        else{
            angleRad = direction * PI / 180;
            x= - 5;
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
double distanceMaxReceiverLinearRelation (int direction,vector <double> positionReceiver,int nbrReceiver){
    double distanceMax(0),distance;
    int i(0);
    if ((direction<0)||(direction>359)||(nbrReceiver<1)||((int)positionReceiver.size()!=(nbrReceiver*2))){
        distanceMax=0;
    }else{
        vector <double> coefficient = linearRelation (direction);
        if ((coefficient[0]==0)&&(coefficient[1]==0)){
            distanceMax=0;
        }else{
            for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
                distance = fabs(((coefficient[0]*positionReceiver[i])+(coefficient[1]*positionReceiver[(i+1)]))/sqrt(pow(coefficient[0],2)+pow(coefficient[1],2)));
                if (distance > distanceMax){
                    distanceMax=distance;
                }
                i=i+2;
            }
        }
    }
    return distanceMax;
}
/**
 * @brief convertVectorToTab convert vector to tab
 * @param positionReceiver all positions of receiver
 * @param tabPositionReceiver tab empty
 * @param nbrReceiver number of Receiver
 * @return true if tab has been completed, false => error
 */
bool convertVectorToTab (vector <double> positionReceiver,double tabPositionReceiver[][2],int nbrReceiver){
    bool retour=false;
    int i(0);
    if ((nbrReceiver>0)&&((int)positionReceiver.size()==(nbrReceiver*2))){
        for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
            tabPositionReceiver[compteur][0]=positionReceiver[i];
            tabPositionReceiver[compteur][1]=positionReceiver[i+1];
            i=i+2;
        }
        retour=true;
    }
    return retour;
}
/**
 * @brief equation2nddegre Solution of the equation ay*y + by + c = 0
 * @param coef coef[0]=a , coef[1]=b , coef[2]=c
 * @return Number of solution + solutions
 */
vector <double> equation2nddegre (double coef [3]){
    vector <double> result (3);
    double delta = pow(coef[1],2)-4*coef[0]*coef[2];
    if (delta == 0){
        result[0]=1;
        result[1]=(-coef[1])/(2*coef[0]);
    }else{
        result[0]=2;
        result[1]=(-coef[1]+sqrt(delta))/(2*coef[0]);
        result[2]=(-coef[1]-sqrt(delta))/(2*coef[0]);
    }
    return result;
}
/**
 * @brief convertDistancetoPoint convert Object Distance to the position of the top front left
 * @param direction Angular position of the obstacle
 * @param distance distance object
 * @param width rectangle width
 * @return the position of this point, if point=(0,0) => error
 */
vector <double> convertDistancetoPoint (int direction,double distance,double width){
    vector <double> point (2);
    vector <double> resultEq;
    double coef [3];
    double intersectionPoint[2];
    double testX[2];
    if ((direction<360)&&(distance>0)&&(width>0)){
        vector <double> coefDroite = linearRelation (direction);
        if ((coefDroite[0]==0)&&(coefDroite[1]==0)){
            point[0]=0;
            point[1]=0;
        }else {
            intersectionPoint[1]=distance*sin(direction * PI / 180);
            intersectionPoint[0]=distance*cos(direction * PI / 180);
            if (direction==0){
                point[0]=distance;
                point[1]=-width/2;
            }else if(direction==90){
                point[0]=width/2;
                point[1]=distance;
            }else if(direction==180){
                point[0]=-distance;
                point[1]=width/2;
            }else if(direction==270){
                point[0]=-width/2;
                point[1]=-distance;
            }else{
                coef[0]=1;
                coef[1]=-2*intersectionPoint[1];
                coef[2]=pow(intersectionPoint[1],2)-(pow((width/2),2)/(pow(coefDroite[0],2)+1));
                resultEq=equation2nddegre(coef);
                if (resultEq[0]==1){
                    point[1]=resultEq[1];
                    point[0]=coefDroite[0]*(resultEq[1]-intersectionPoint[1]+(intersectionPoint[0])/coefDroite[0]);
                }else{
                    testX[0]=coefDroite[0]*(resultEq[1]-intersectionPoint[1]+(intersectionPoint[0])/coefDroite[0]);
                    testX[1]=coefDroite[0]*(resultEq[2]-intersectionPoint[1]+(intersectionPoint[0])/coefDroite[0]);
                    if ((direction>0)&&(direction<90)){
                        if((intersectionPoint[0]<testX[0])&&(intersectionPoint[1]>=resultEq[1])){
                            point[1]=resultEq[1];
                            point[0]=testX[0];
                        }else{
                            point[1]=resultEq[2];
                            point[0]=testX[1];
                        }
                    }else if((direction>90)&&(direction<180)){
                        if((intersectionPoint[0]<=testX[0])&&(intersectionPoint[1]<resultEq[1])){
                            point[1]=resultEq[1];
                            point[0]=testX[0];
                        }else{
                            point[1]=resultEq[2];
                            point[0]=testX[1];
                        }
                    }else if ((direction>180)&&(direction<270)){
                        if((intersectionPoint[0]>testX[0])&&(intersectionPoint[1]<=resultEq[1])){
                            point[1]=resultEq[1];
                            point[0]=testX[0];
                        }else{
                            point[1]=resultEq[2];
                            point[0]=testX[1];
                        }
                    }else{
                        if((intersectionPoint[0]>=testX[0])&&(intersectionPoint[1]>resultEq[1])){
                            point[1]=resultEq[1];
                            point[0]=testX[0];
                        }else{
                            point[1]=resultEq[2];
                            point[0]=testX[1];
                        }
                    }
                }
            }
        }
    }else{
        point[0]=0;
        point[1]=0;
    }
    return point;
}
