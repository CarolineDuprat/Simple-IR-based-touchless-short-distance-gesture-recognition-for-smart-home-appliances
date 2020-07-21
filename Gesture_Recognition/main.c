#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"
#include "snapshotAnalysis.h"

/**
 * @file The objective of this program is to determine the movement performed by the object from a data file of the receivers.
 * This program can be broken down into three parts: translate the info from the file, creation of the snapshot list and snapshot list analysis to determine movement
 */


int main()
{


    //Link of the file to study
    char *lien="Data\\addRL_TB_BT_LR.txt";
    //4_1_1_1_-1_-1_-1_-1_1_10_10_5_4_4_


    snapshotsGestureName (lien);





    return 0;
}
