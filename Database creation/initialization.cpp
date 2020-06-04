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
vector <double> init(int& nbrReceiver,int& direction,double& sizeLength,double& sizeWidth,double& objectMovingSpeed,double distance)
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
 * @param positionReveicer all positions of receiver
 * @param nbrReceiver number of Receiver
 * @return maximum distance between the line and receivers, if distanceMax=0 => Parameter error
 */
double distanceMaxReceiverLinearRelation (int direction,vector <double> positionReveicer,int nbrReceiver){
    double distanceMax(0),distance;
    int i(0);
    if ((direction<0)||(direction>359)||(nbrReceiver<1)||(positionReveicer.size()!=(nbrReceiver*2))){
        distanceMax=0;
    }else{
        vector <double> coefficient = linearRelation (direction);
        if ((coefficient[0]==0)&&(coefficient[1]==0)){
            distanceMax=0;
        }else{
            for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
                distance = fabs(((coefficient[0]*positionReveicer[i])+(coefficient[1]*positionReveicer[(i+1)]))/sqrt(pow(coefficient[0],2)+pow(coefficient[1],2)));
                if (distance > distanceMax){
                    distanceMax=distance;
                }
                i=i+2;
            }
        }
    }
    return distanceMax;
}
