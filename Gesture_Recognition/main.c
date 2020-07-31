#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"
#include "snapshotAnalysis.h"
#include "generateSnapshot.h"
#include "simulationReceiver.h"

/**
 * @file The objective of this program is to determine the movement performed by the object from a data file of the receivers.
 * This program can be broken down into three parts: translate the info from the file, creation of the snapshot list and snapshot list analysis to determine movement
 */

// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] minSpeed maxSpeed NumberOfGesture name1 angleNominal1[°] angleDeviation1[°] name2 angleNominal2[°] angleDeviation2[°] name3 angleNominal3[°] angleDeviation3[°]...
// 4 1 1 1 -1 -1 -1 -1 1 8 "TB" 90 10 "BT" 270 10 "RL" 0 10 "LR" 180 10 "TRBL" 45 10 "TLBR" 135 10 "BRTL" 315 10 "BLTR" 225 10
// 4 1 1 1 -1 -1 -1 -1 1 4 "RL" 0 10 "TB" 90 10 "LR" 180 10 "BT" 270 10
// 4 1 1 2 -1 -1 2 -1 1 2 10 4 "RL" 0 10 "TB" 90 10 "LR" 180 10 "BT" 270 10
int main(int argc, char *argv[])
{
    snapshots all_snapshots;
    dataGestures dataGestures;
    transition transitions;
    infoSystem system;
    uint16_t j=1,error=0,angleN,angleD;

    //Link of the file to study
    //Put the file Data in build gesture recognition
    char *lien="Data\\4_1_1_2_-1_-1_2_-1_1_90_10_5_4_4_.txt";


    // Initialization and verification of parameters

    if (argc > 7){
        system.numberReceivers= atoi(argv[j]);
        printf("NumberReceivers = %d\n",system.numberReceivers);
        j++;
        //For each receiver
        for (uint16_t i=0;i<system.numberReceivers;i++){
            system.pos[i].x=atoi(argv[j]);
            printf("x = %f\n",system.pos[i].x);
            system.pos[i].y=atoi(argv[j+1]);
            printf("y = %f\n",system.pos[i].y);
            // Add the ID of each receiver in binaire
            system.pos[i].id=1<<i;
            printf("id = %d\n",system.pos[i].id);
            j=j+2;
        }
        system.speedMin=atoi(argv[j]);
        j++;
        system.speedMax=atoi(argv[j]);
        j++;
        system.numberGesture= atoi(argv[j]);
        printf("NumberGesture= %d\n",system.numberGesture);
        j++;
        //For each gesture
        for (uint16_t i=0;i<system.numberGesture;i++){
            system.gesture[i].name=argv[j];
            printf("Name = %s\n",system.gesture[i].name);
            system.gesture[i].id=1<<i;
            printf("id = %0x\n",system.gesture[i].id);
            angleN=atoi(argv[j+1]);
            angleD=atoi(argv[j+2]);
            //Check the value
            if((angleN <360)&&(angleD <360)){
                system.gesture[i].NAngle=angleN;
                system.gesture[i].DAngle=angleD;
                printf("angleNominal = %d\n",system.gesture[i].NAngle);
                printf("angleDeviation = %d\n",system.gesture[i].DAngle);
            }else{
                error=1;
            }
            j=j+3;
        }
    }
    if (error ==0){
        //Create data with all movements allowed
        dataGestures=createDataBase (system);
        //displayDataGesture(dataGestures);
        //Create all_snapshots
        all_snapshots=extractSnapshot (dataGestures);
        //Create transitions_rows and transitions_pool
        transitions=extractTransition (dataGestures,all_snapshots);
        //Analyse the file
        snapshotsGestureName (lien,all_snapshots,transitions,system);
    }













    return 0;
}
