#include <iostream>
#include <vector>
#include "simulationReceiver.h"
#include "fileManagement.h"
#include "initialization.h"

using namespace std;

// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] angle[°] distance[cm] speed[m/s] width[cm] length[cm]
// 6 -6 5 -6 -2 0.5 3 -2.5 -2.5 4.5 -0.5 5.5 -4 +150 +10 +10 +11 +3

int main(int argc,char *argv[])
{
    int nbrReceiver, angle(0), c(2),j(0),totalTime;
    double distance,speed;
    bool check(true);
    std::vector<double> positionReceiverVector;
    string filename;
    returnSpeedPos infoSpeedPos;
    returnInit retourinit;
    position_t *positionReceiver = nullptr;
    rec *data =nullptr;
    position_t positionObject;
    dimension dimensionObject;

    (void)totalTime;
    //
    //        Initialization and verification of parameters
    //
    if (argc < 2) {
        //User interaction in the console
        retourinit=init(nbrReceiver,angle,dimensionObject,speed,distance);
        positionReceiverVector=retourinit.positionReceiver;
        check=retourinit.check;
        if (check==true){
            positionReceiver = new(std::nothrow) position_t[nbrReceiver];
            // Create tab with the value of the position of all receivers
            for (int i=0 ; i<nbrReceiver;i++){
                positionReceiver[i].x = positionReceiverVector[j];
                positionReceiver[i].y = positionReceiverVector[j+1];
                j=j+2;
            }
            //add file name
        }
    } else {
        //Read Command-line argument
        nbrReceiver=stoi(argv[1]);
        positionReceiver = new(std::nothrow) position_t[nbrReceiver];
        if ( argc != (nbrReceiver*2 + 7)){
            cout<<"Error number of arguments"<<endl;
            check = false;
        }else {
            // Create file name
            for (int i=0 ; i<argc;i++){
                filename += argv[i];
                filename += '_';
            }
            // Create tab with the value of the position of all receivers
            for (int i(0) ; i<nbrReceiver;i++){
                positionReceiver[i].x = stof(argv[c]);
                positionReceiver[i].y = stof(argv[c+1]);
                c=c+2;
            }
            angle= stoi(argv[2+nbrReceiver*2]);
            distance= stof(argv[3+nbrReceiver*2]);
            speed=stof(argv[4+nbrReceiver*2]);
            dimensionObject.width=stof(argv[5+nbrReceiver*2]);
            dimensionObject.length=stof(argv[6+nbrReceiver*2]);

            //The function stof returns error
            //The function stoi returns 0 if error

            //Check parameters
            check = checkAllParameters (nbrReceiver,positionReceiver,angle,distance,speed,dimensionObject);
        }
    }
    //
    //       Simulation
    //
    if (check==false){
        cout << "Error Parameters" << endl;
    }else{
        (void )showParameters (nbrReceiver,positionReceiver,angle,dimensionObject,speed,distance);
        totalTime=simulationTime (distance,speed);
        cout << "Total Time : " << totalTime << " ms"<<endl;
        infoSpeedPos = HorizontalAndVerticalSpeed (distance,speed,angle);
        cout << "Initial position of the object, x: "<< infoSpeedPos.pos.x << " cm, y: " << infoSpeedPos.pos.y<<" cm"<<endl;
        cout << "Speed horirontal : "<< infoSpeedPos.speed.hor<<" cm/ms, Speed vertical : "<<infoSpeedPos.speed.vert << " cm/ms"<<endl;
        data = new(std::nothrow) rec[nbrReceiver];
        for (int i=0;i< nbrReceiver;i++){
            data [i].ID=1 << i;
            cout<<data [i].ID <<endl;
        }
        for (int t=0;t< totalTime+1;t++){
            positionObject=positionMoveObject (infoSpeedPos ,t);
            cout << "Position of the object, x: "<< positionObject.x << " cm, y: " << positionObject.y<<" cm"<<endl;
        }

    }

    /*
    if (check==true) {
        totalTime=simulationTime (distance,speed);
        information = HorizontalAndVerticalSpeed (distance,speed,angle, &whatever);
        cout << "totalTime: " << totalTime << endl;
        for (unsigned int i = 0; i < information.size(); i++) {
            cout << "HorizontalAndVerticalSpeed(" << i << "): " << information.at(i) << endl;
        }
        double dataReceiver [nbrReceiver][3];
        std::vector<double> iD=iDDecimal (nbrReceiver);
        for (int i=0;i< nbrReceiver;i++){
            dataReceiver [i][0]=iD[i];
        }
        for (int t=0;t< totalTime+1;t++){
            positionObject=positionMoveObject (information ,t);
        }
    }
    */
    delete[] positionReceiver;
    delete[] data;

  return 0;
}


