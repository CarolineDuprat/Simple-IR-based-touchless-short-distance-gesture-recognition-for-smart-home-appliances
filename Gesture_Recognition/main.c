#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"
#include "snapshotAnalysis.h"
#include "generateSnapshot.h"

/**
 * @file The objective of this program is to determine the movement performed by the object from a data file of the receivers.
 * This program can be broken down into three parts: translate the info from the file, creation of the snapshot list and snapshot list analysis to determine movement
 */

// arguments : name.exe NumberOfReceiver x1[cm] y1[cm] x2[cm] y2[cm].... xN[cm] yN[cm] NumberOfGesture angle1[°] angle2[°] angle3[°] ...
// 4 1 1 1 -1 -1 -1 -1 1 8 0 45 90 135 180 225 270 315
int main(int argc, char *argv[])
{
    snapshots all_snapshots;
    infoSystem system;
    uint16_t j=1,error=0,gesture=0;

    //Link of the file to study
    //Put the file Data in build gesture recognition
    char *lien="Data\\4_1_1_1_-1_-1_-1_-1_1_315_10_5_4_4_.txt";


    // Initialization and verification of parameters

    if (argc > 5){
        system.numberReceivers= atoi(argv[j]);
        printf("NumberReceivers = %d\n",system.numberReceivers);
        j++;
        //For each receiver
        for (uint16_t i=0;i<system.numberReceivers;i++){
            system.pos[i].x=atoi(argv[j]);
            printf("x = %d\n",system.pos[i].x);
            system.pos[i].y=atoi(argv[j+1]);
            printf("y = %d\n",system.pos[i].y);
            // Add the ID of each receiver in binaire
            system.pos[i].id=1<<i;
            printf("id = %d\n",system.pos[i].id);
            j=j+2;
        }

        system.numberGesture= atoi(argv[j]);
        printf("NumberGesture= %d\n",system.numberGesture);
        j++;
        //For each gesture
        for (uint16_t i=0;i<system.numberGesture;i++){
            gesture=atoi(argv[j]);
            //Check the value
            if(gesture <360){
                system.gesture[i]=gesture;
                printf("gesture = %d\n",system.gesture[i]);
            }else{
                error=1;
            }
            j++;
        }
    }
    if (error ==0){
        all_snapshots=createAllSnap (system);


        //snapshotsGestureName (lien);
    }













    return 0;
}
