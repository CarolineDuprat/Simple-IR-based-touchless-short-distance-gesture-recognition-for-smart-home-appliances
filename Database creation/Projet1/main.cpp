#include <QCoreApplication>
#include <iostream>
#include <string>
#include "detection.h"
#include <vector>
using namespace std;

int main ()
{
    bool result;
    int const nombre(2);
    double receiver[nombre];
    receiver[0] = -4.5;
    receiver[1] = -1.5;
    double object[nombre];
    object[0] = -5.3;
    object[1] = -4.8;
    result =  objectReceiverContains (3, 3, 30 ,object, receiver);
    cout << result << endl;

    return 0;

}
