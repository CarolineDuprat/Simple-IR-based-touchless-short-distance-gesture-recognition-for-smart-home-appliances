#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"
//#include "snapshotAnalysis.h"

/**
 * @file The objective of this program is to determine the movement performed by the object from a data file of the receivers.
 * This program can be broken down into three parts: translate the info from the file, creation of the snapshot list and snapshot list analysis to determine movement
 */


int main()
{
    allreceivers_info receivers;
    snapshot snapshotReceivers;
    //uint16_t position;

    //Link of the file to study
    char *lien="Data\\4_1_1_1_-1_-1_-1_-1_1_310_10_5_4_4_.txt";

    //translate the information from the file to receivers
    receivers=translateInfoFromFile (lien);

    //Creation of a file with data from receivers
    checkFunction (receivers);

    //Creation of the snapshot list
    snapshotReceivers=snapshotCreation (receivers);
    display(snapshotReceivers);
    //position=snapshotResearch (snapshotReceivers.t[0]);
    //printf("position = %d\n",position);

    return 0;
}
