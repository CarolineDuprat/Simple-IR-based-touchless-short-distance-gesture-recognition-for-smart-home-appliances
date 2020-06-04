#include <iostream>
#include <Windows.h>
#include "time.h"
#include "detection.h"
#include "fileManagement.h"
#include "initialization.h"

using namespace std;


int main()
{
    int nbrReceiver, direction;
    bool retour;
    double sizeLength,sizeWidth,objectMovingSpeed,distance(0);
    vector <double> data;
    data=init(nbrReceiver,direction,sizeLength,sizeWidth,objectMovingSpeed,distance);
    double tabPositionReceiver[nbrReceiver][2];
    retour=convertVectorToTab (data,tabPositionReceiver,nbrReceiver);
    cout << tabPositionReceiver[0][0] << "   "<<tabPositionReceiver[1][0];

  return 0;
}


