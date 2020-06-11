
#include "initialization.h"

/**
 * @brief init initialization of all parameters with User interaction in the console
 * @param nbrReceiver Number of Receiver
 * @param direction Angular position of the obstacle[°]
 * @param sizeLength rectangle length [cm]
 * @param sizeWidth rectangle width [cm]
 * @param speed speed of the object [m/s]
 * @param distance distance from object center to device center [cm]
 * @param positionReceiverVector position of all receivers
 * @return true : No Error ; false : Error Parameters
 */
returnInit init(int& nbrReceiver,int& direction,double& sizeLength,double& sizeWidth,double& speed,double& distance)
{
    returnInit retour;
    bool check(true);
    std::vector<double> positionReceiverVector;
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
        positionReceiverVector.push_back(x);
        positionReceiverVector.push_back(y);
    }
    do{
        cout << "Object direction ? [degree]  " << endl;
        cin >> direction;
    }while((direction>359)||(direction<0));
    sizeWidthMin=(distanceMaxReceiverLinearRelationVector (direction,positionReceiverVector,nbrReceiver)*2);
    if (sizeWidthMin==0){
        cout << "Error"<< endl;
        check=false;
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
            cin >> speed;
        }while(speed<=0);
        do{
            cout << "Object distance [cm] ?  " << endl;
            cin >> distance;
        }while(distance<=0);
        cout << "End of initialization  " << endl;
    }
    retour.positionReceiver=positionReceiverVector;
    retour.check=check;
    return retour;
}
/**
 * @brief checkAllParameters check the value of all parameters entered in the command line
 * @param nbrReceiver number of receiver
 * @param positionReceiver position x and y of all paramaters [cm]
 * @param angle Angular position of the obstacle [°]
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @param sizeWidth rectangle width [cm]
 * @param sizeLength rectangle length [cm]
 * @return true : No Error ; false : Error Parameters
 */
bool checkAllParameters (int const nbrReceiver,position_t positionReceiver[] ,int const angle,double const distance,double const speed,double const sizeWidth,double const sizeLength){
    bool check(true);
    double distancemin(distanceMaxReceiverLinearRelationTab(angle,positionReceiver,nbrReceiver));
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
 * @param direction Angular position of the obstacle [°]
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
 * @brief distanceMaxReceiverLinearRelationTab Calculution of the maximum distance between the line and receivers (Positions of receivers are in a tab)
 * @param direction Angular position of the obstacle [°]
 * @param positionReceiver all positions of receiver [cm]
 * @param nbrReceiver number of Receiver
 * @return maximum distance between the line and receivers, if distanceMax=0 => Parameter error
 */
double distanceMaxReceiverLinearRelationTab (int const direction,position_t positionReceiver[] ,int const nbrReceiver){
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
                distance = fabs(((coefficient[0]*positionReceiver[compteur].x)+(coefficient[1]*positionReceiver[compteur].y))/sqrt(pow(coefficient[0],2)+pow(coefficient[1],2)));
                // Maximum distance
                if (distance > distanceMax){
                    distanceMax=distance;
                }
            }
        }
    }
    return distanceMax;
}
/**
 * @brief distanceMaxReceiverLinearRelationVector Calculution of the maximum distance between the line and receivers (Positions of receivers are in a vector)
 * @param direction Angular position of the obstacle [°]
 * @param positionReceiver all positions of receiver [cm]
 * @param nbrReceiver number of Receivers
 * @return maximum distance between the line and receivers, if distanceMax=0 => Parameter error
 */
double distanceMaxReceiverLinearRelationVector (int const direction,vector <double> positionReceiver,int const nbrReceiver){
    double distanceMax(0),distance;
    int i(0);
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
                distance = fabs(((coefficient[0]*positionReceiver[i])+(coefficient[1]*positionReceiver[i+1]))/sqrt(pow(coefficient[0],2)+pow(coefficient[1],2)));
                // Maximum distance
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
 * @brief showParameters show all parameters
 * @param nbrReceiver number of Receivers
 * @param positionReceiver all positions of receiver [cm]
 * @param direction Angular position of the obstacle [°]
 * @param sizeLength rectangle length [cm]
 * @param sizeWidth rectangle width [cm]
 * @param speed speed of the object [m/s]
 * @param distance distance from object center to device center [cm]
 */
void showParameters (int nbrReceiver,position_t positionReceiver[],int direction,double sizeLength,double sizeWidth,double speed,double distance){
    cout << "Number of Receivers : " << nbrReceiver << endl;
    for (int i(0);i<nbrReceiver;i++){
        cout << "Receiver " << i <<", x: " << positionReceiver[i].x << " cm, y : "<< positionReceiver[i].y<< " cm" <<endl;
    }
    cout << "Angular position of the obstacle : "<<direction << " degree"<<endl;
    cout << "Object size : " << sizeLength << " cm length, " <<sizeWidth<< " cm width " << endl;
    cout << "Object speed : "<< speed << " m/s"<<endl;
    cout << "Object distance : "<< distance << " cm"<<endl;
}
