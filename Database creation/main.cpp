#include <iostream>
#include <vector>
#include "simulationReceiver.h"

using namespace std;

// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] angle[°] distance[cm] speed[m/s] width[cm] length[cm]
// 2 +1.2 -3.6 -6 -9 +6 +2 +3.1 +3 +6

int main(int argc,char *argv[])
{
    int nbrReceiver, angle(0), j(2);
    double distance,speed,sizeLength,sizeWidth;
    cout << "Number of arguments :" << argc;
    for (int i=0 ; i<argc;i++){
        cout<<"Arg"<< i << ":" << argv[i] <<endl;
    }
    nbrReceiver=stoi(argv[1]);
    double positionReceiver[nbrReceiver][2];
    if ( argc != (nbrReceiver*2 + 7)){
        cout<<"Error"<<endl;
    }else {
        for (int i=0 ; i<nbrReceiver;i++){
            positionReceiver[i][0]=stof(argv[j]);
            positionReceiver[i][1]=stof(argv[j+1]);
            j=j+2;
        }
        angle= stof(argv[2+nbrReceiver*2]);
        distance= stof(argv[3+nbrReceiver*2]);
        speed=stof(argv[4+nbrReceiver*2]);
        sizeWidth=stof(argv[5+nbrReceiver*2]);
        sizeLength=stof(argv[6+nbrReceiver*2]);
        cout << simulationTime (distance,speed)<<endl;
    }



  return 0;
}


