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
    double sizeLength,sizeWidth,objectMovingSpeed,distance;
    vector <double> data;
    data=init(nbrReceiver,direction,sizeLength,sizeWidth,objectMovingSpeed,distance);

  return 0;
}


