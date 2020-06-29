#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"

/**
 * @file The objective of this program is to determine the movement performed by the object from a data file of the receivers.
 * This program can be broken down into three parts: translate the info from the file, creation of the snapshot list and snapshot list analysis to determine movement
 */


int main()
{
    allreceivers_info receivers;
    snapshot snapshotReceivers;

    //Link of the file to study
    char *lien="Data\\4_1_1_1_-1_-1_-1_-1_1_0_10_5_4_4_.txt";

    //translate the information from the file to receivers
    receivers=translateInfoFromFile (lien);

    //Creation of a file with data from receivers
    checkFunction (receivers);

    //Creation of the snapshot list
    snapshotReceivers=snapshotCreation (receivers);

    (void)snapshotReceivers;

    return 0;
}
