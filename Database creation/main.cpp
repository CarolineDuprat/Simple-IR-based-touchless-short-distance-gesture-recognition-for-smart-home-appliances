#include <iostream>
#include <Windows.h>
#include "time.h"
#include "detection.h"
#include "fileManagement.h"
#include "initialization.h"

using namespace std;


int main()
{
    // Initialization
    int nbrReceiver, direction;
    bool retour;
    double sizeLength,sizeWidth,objectMovingSpeed,distance(0);
    vector <double> data,positionObject;
    data=init(nbrReceiver,direction,sizeLength,sizeWidth,objectMovingSpeed,distance);
    double positionReceiver[nbrReceiver][2];
    retour=convertVectorToTab (data,positionReceiver,nbrReceiver);
    if (retour==false){
        cout<<"Error"<<endl;
    }
    positionObject= convertDistancetoPoint (direction,distance,sizeWidth);
    // End Initialization

  return 0;
}


