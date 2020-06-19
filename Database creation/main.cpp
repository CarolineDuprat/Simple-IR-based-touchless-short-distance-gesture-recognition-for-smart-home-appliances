#include <iostream>
#include <vector>
#include "simulationReceiver.h"
#include "fileManagement.h"
#include "initialization.h"

using namespace std;

// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] angle[°] distance[cm] speed[m/s] width[cm] length[cm]
// 6 -6 5 -6 -2 0.5 3 -2.5 -2.5 4.5 -0.5 5.5 -4 +150 +10 +10 +11 +3
// 4 1 1 1 -1 -1 -1 -1 1 0 10 5 4 4 > results.csv
/**
 * @file The objective of the program is to simulate the data received by the receivers during the movement of an object and write this data
 * to a file.For this code will be broken down into three parts: initialization of the parameters, simulation of the receivers, writing in a file.
 * For the parameter initialization part, the user can either enter the parameters in the command line or interact with the console (initialization).
 * As a function of time, we will have to calculate the displacement that the object has made and then see if the object is in front of one or more
 * receivers. ( sumulationReceiver )
 * Then, we add a line in the file with the states of the receivers. ( fileManagement )
 */

int main(int argc,char *argv[])
{
    int nbrReceiver, angle(0), c(2),j(0),totalTime;
    double distance,speed;
    bool check(true),inRectangle,write;
    std::vector<double> positionReceiverVector;
    std::vector<position_t> positionCornerRotation, positionCorner;
    string filename; //,lien(" C:\"Users\"Caroline Duprat\"");
    returnSpeedPos infoSpeedPos;
    returnInit retourinit;
    position_t *positionReceiver = nullptr;
    rec *data =nullptr;
    position_t positionObject;
    dimension dimensionObject;

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
            // Create file name
            filename = "_";
            filename += nameFile (nbrReceiver,positionReceiver,angle,distance,speed,dimensionObject);
        }
    } else {
        //Read Command-line argument
        nbrReceiver=int(stof(argv[1]));
        positionReceiver = new(std::nothrow) position_t[nbrReceiver];
        //Check number of arguments
        if ( argc != (nbrReceiver*2 + 7)){
            cout<<"Error number of arguments"<<endl;
            check = false;
        }else {
            // Create file name
            for (int i=1 ; i<argc;i++){
                filename += argv[i];
                filename += '_';
            }
            // Create tab with the value of the position of all receivers
            for (int i(0) ; i<nbrReceiver;i++){
                positionReceiver[i].x = stof(argv[c]);
                positionReceiver[i].y = stof(argv[c+1]);
                c=c+2;
            }
            angle= int(stof(argv[2+nbrReceiver*2]));
            distance= stof(argv[3+nbrReceiver*2]);
            speed=stof(argv[4+nbrReceiver*2]);
            dimensionObject.width=stof(argv[5+nbrReceiver*2]);
            dimensionObject.length=stof(argv[6+nbrReceiver*2]);
            //The function stof returns error

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
        // show parameters
        (void )showParameters (nbrReceiver,positionReceiver,angle,dimensionObject,speed,distance);

        //Calcul the total time
        totalTime=simulationTime (distance,speed);
        cout << "Total Time : " << totalTime << " ms"<<endl;

        //Calcul initial position of the object, horirontal & vertical speed
        infoSpeedPos = HorizontalAndVerticalSpeed (distance,speed,angle);
        cout << "Initial position of the object, x: "<< infoSpeedPos.pos.x << " cm, y: " << infoSpeedPos.pos.y<<" cm"<<endl;
        cout << "Speed horirontal : "<< infoSpeedPos.speed.hor<<" cm/ms, Speed vertical : "<<infoSpeedPos.speed.vert << " cm/ms"<<endl;
        data = new(std::nothrow) rec[nbrReceiver];

        // Add the ID of each receiver in binaire
        for (int i=0;i< nbrReceiver;i++){
            data [i].ID=1 << i;
        }

        //Position Corner after the rotation
        positionCornerRotation = rotationCorner (dimensionObject,angle);
        cout << "Position Corner, (0,0) : Position of the center of the object  " << endl;
        cout << "c1 : "<<positionCornerRotation[0].x << " , "<<positionCornerRotation[0].y << endl;
        cout << "c2 : "<<positionCornerRotation[1].x << " , "<<positionCornerRotation[1].y << endl;
        cout << "c3 : "<<positionCornerRotation[2].x << " , "<<positionCornerRotation[2].y << endl;
        cout << "c4 : "<<positionCornerRotation[3].x << " , "<<positionCornerRotation[3].y << endl;

        cout << endl;
        cout << endl;
        cout << "object.x, object.y";
        for (int i=0 ; i<4 ; i++){
            cout << ", corner[" << i << "].x, corner[" << i << "].y";
        }
        for (int r=0 ; r<nbrReceiver ; r++){
            cout << ", receiver[" << r << "].ID, inRect, time, valid";
        }
        cout << endl;

        for (int t=0;t< totalTime+1;t++){

            //Calcul the new position of the object after time=t

            positionObject=positionMoveObject (infoSpeedPos ,t);
            cout << positionObject.x << ", " << positionObject.y;

            //Calcul the new position of corners

            positionCorner=ReelPositionCorner (positionObject,positionCornerRotation);

            for (int r=0;r<nbrReceiver;r++){

                //Check if the receiver is in the object

                inRectangle=ReceiverCovered (positionReceiver[r],positionCorner);

                // If inrectangle==1 => the object is in front a receiver
                // We must keep in memory the first time that the object is in front of the receiver, so we must check the
                // valid state on the front turn.

                // Write information in the line that will be added to the file

                if ((inRectangle==1)&&(data[r].valid==0)){
                    data[r].time=t;
                    data[r].valid=1;
                }else if(inRectangle==1){
                    data[r].valid=1;
                }else{
                    data[r].time=0;
                    data[r].valid=0;
                }
                cout << ", " << data[r].ID << ", " << inRectangle<<", " << data[r].time<< ", " << data[r].valid;
            }
            cout << endl;

            //write data in the file

            write=writeFile (argv[0],filename,data,nbrReceiver);
            if (write==true){
                //cout << "The line has been added in the file" <<endl;
            }
        }
    }
    delete[] positionReceiver;
    delete[] data;

  return 0;
}


