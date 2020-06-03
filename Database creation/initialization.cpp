#include "initialization.h"

/**
 * @brief init initialization of all parameters
 * @param nbrReceiver number of Receiver
 * @param direction Angular position of the obstacle
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param objectMovingSpeed speed of the object
 * @param positionObject position (x,y) object , it's the position of the top front left
 * @return all positions of receiver
 */
vector <double> init(int& nbrReceiver,int& direction,double& sizeLength,double& sizeWidth,double& objectMovingSpeed,double positionObject[])
{
    vector <double> positionReveicer;
    cout << "Number of Receiver ?" << endl;
    cin >> nbrReceiver;
    for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
        double x,y;
        cout << "Position of receiver [cm] " << compteur << " x :" << endl;
        cin >> x;
        positionReveicer.push_back(x);
        cout << " y :" << endl;
        cin >> y;
        positionReveicer.push_back(y);
    }
    cout << "Object size : width [cm] ?" << endl;
    cin >> sizeWidth;
    cout << "length [cm] ?" << endl;
    cin >> sizeLength;
    cout << "Object speed ? [m/s] " << endl;
    cin >> objectMovingSpeed;
    cout << "Object position [cm] x ?  " << endl;
    cin >> positionObject[0];
    cout << " y ?  " << endl;
    cin >> positionObject[1];
    cout << "Object direction ? [°]  " << endl;
    cin >> direction;

    return positionReveicer;
}
