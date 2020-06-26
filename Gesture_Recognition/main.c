#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"
#include "snapshot.h"


int main()
{
    allreceivers_info receivers;

    //Link of the file to study
    char *lien="Data\\4_1_1_1_-1_-1_-1_-1_1_310_10_5_4_4_.txt";

    receivers=translateInfoFromFile (lien);

    //checkFunction (receivers);

    snapshotCreation (receivers);

    return 0;
}
