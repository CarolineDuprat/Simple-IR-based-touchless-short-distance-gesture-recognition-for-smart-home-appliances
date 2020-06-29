#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"


int main()
{
    allreceivers_info receivers;
    snapshot snapshotReceivers;

    //Link of the file to study
    char *lien="Data\\4_1_1_1_-1_-1_-1_-1_1_310_10_5_4_4_.txt";

    //translate the information from the file to receivers
    receivers=translateInfoFromFile (lien);

    //Creation of a file with data from receivers
    checkFunction (receivers);

    //Creation of the snapshot list
    snapshotReceivers=snapshotCreation (receivers);

    return 0;
}
