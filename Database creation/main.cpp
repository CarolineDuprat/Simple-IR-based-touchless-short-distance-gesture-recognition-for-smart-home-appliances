#include <iostream>
#include <vector>
#include "simulationReceiver.h"
#include "fileManagement.h"
#include "initialization.h"

using namespace std;


typedef struct {
    double hor;
    double vert;
} speed_t;


typedef struct {
    position_t pos;
    speed_t speed;
    bool error;
} xx_t;


// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] angle[°] distance[cm] speed[m/s] width[cm] length[cm]
// 6 -6 5 -6 -2 0.5 3 -2.5 -2.5 4.5 -0.5 5.5 -4 +150 +10 +10 +11 +3

int main(int argc,char *argv[])
{
    int nbrReceiver, angle(0), c(2),j(0),totalTime;
    double distance,speed,sizeLength,sizeWidth;
    bool check(true);
    std::vector<double> positionObject,information,positionReceiverVector;
    string filename;
    xx_t whatever;
    returnInit retour;

    //@FRB
    position_t *positionReceiver = nullptr;

    (void)totalTime;
    (void)whatever;
    //
    //        Initialization and verification of parameters
    //
    if (argc < 2) {
        //User interaction in the console
        retour=init(nbrReceiver,angle,sizeLength,sizeWidth,speed,distance);
        positionReceiverVector=retour.positionReceiver;
        check=retour.check;
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
            sizeWidth=stof(argv[5+nbrReceiver*2]);
            sizeLength=stof(argv[6+nbrReceiver*2]);

            //The function stof returns error
            //The function stoi returns 0 if error

            //Check parameters
            check = checkAllParameters (nbrReceiver,positionReceiver,angle,distance,speed,sizeWidth,sizeLength);
        }
    }
    if (check==false){
        cout << "Error Parameters" << endl;
    }else{
        (void )showParameters (nbrReceiver,positionReceiver,angle,sizeLength,sizeWidth,speed,distance);
    }
    //
    //
    //
    /*
    if (check==true) {
        //debugAllParameters(nbrReceiver, positionReceiver, angle, distance, speed, sizeWidth, sizeLength);
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

  return 0;
}


