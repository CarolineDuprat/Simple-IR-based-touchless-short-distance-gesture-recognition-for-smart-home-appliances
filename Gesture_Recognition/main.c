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


int main()
{


    //Link of the file to study
    //Put the file Data in build gesture recognition
    char *lien="Data\\4_1_1_1_-1_-1_-1_-1_1_315_10_5_4_4_.txt";

    //snapshotsGestureName (lien);
    uint16_t ok = calculBinomialCoeff (9,4);
    printf("combinaison = %d\n",ok);





    return 0;
}
