#include <iostream>
#include <vector>
#include "simulationReceiver.h"
#include "checkInitialization.h"
#include "fileManagement.h"

using namespace std;

// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] angle[°] distance[cm] speed[m/s] width[cm] length[cm]
// 6 -6 5 -6 -2 0.5 3 -2.5 -2.5 4.5 -0.5 5.5 -4 +150 +10 +10 +11 +3

int main(int argc,char *argv[])
{
    int nbrReceiver, angle(0), j(2),totalTime,retourObjectInFrontofReceiver;
    double distance,speed,sizeLength,sizeWidth;
    bool check,writeF;
    std::vector<double> positionObject,information;
    string filename;


    nbrReceiver=stoi(argv[1]);
    double positionReceiver[nbrReceiver][2];
    if ( argc != (nbrReceiver*2 + 7)){
        cout<<"Error number of arguments"<<endl;
    }else {
        // Create file name
        for (int i=0 ; i<argc;i++){
            filename += argv[i];
            filename += '_';
        }
        // Create tab with the value of the position of all receivers
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

        //Check parameters
        check = checkAllParameters (nbrReceiver,positionReceiver,angle,distance,speed,sizeWidth,sizeLength);

        if (check==true){
            totalTime=simulationTime (distance,speed);
            information = HorizontalAndVerticalSpeed (distance,speed,angle);
            double dataReceiver [nbrReceiver][3];
            std::vector<double> iD=iDDecimal (nbrReceiver);
            for (int i=0;i< nbrReceiver;i++){
                dataReceiver [i][0]=iD[i];
            }
            for (int t=0;t< totalTime+1;t++){
                positionObject=positionMoveObject (information ,t);
            }
        }
    }
  return 0;
}


