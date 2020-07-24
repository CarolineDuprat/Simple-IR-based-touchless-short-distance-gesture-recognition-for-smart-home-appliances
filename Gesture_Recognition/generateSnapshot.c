#include "generateSnapshot.h"
#include "snapshot.h"

/**
 * @brief calculBinomialCoeff         ( n )          n!
 *                             calcul (   ) = -----------------
 *                                    ( k )    k! * ( n - k )!
 * @param n
 * @param k
 * @return result
 */
uint16_t calculBinomialCoeff (uint16_t n,uint16_t k){
    uint16_t denominator  = 1,numerator = 1,combinaisons;


    for(uint16_t i = k; i > 1; i--) {
        denominator  *= i;
    }

    for(uint16_t j = n; j >= n - k + 1; j--) {
        numerator *= j;
    }

    combinaisons = numerator / denominator  ;
    return combinaisons;
}
/**
 * @brief linearRelation calcul the coefficent of the line passing through A and B  y = m * x + p
 *       yB - yA
 * m = ------------   and p = yA - m * xA
 *       xB - xA
 * @param A
 * @param B
 * @return m and p
 */
coefLine linearRelation (position A,position B){
    coefLine line;

    line.m = ( B.y - A.y)/(B.x - A.x);
    line.p = A.y - line.m * A.x;

    return line;
}
/**
 * @brief pointBelongstoline lets you know if the three points are aligned
 * if the 3 points are aligned, so C belongs to the line passing through A and B  y = m * x + p
 * @param A position A
 * @param B position B
 * @param C position C
 * @return 1 : the three points are aligned , else 0
 */
uint8_t pointsAligned(position A,position B,position C){
    uint8_t retour=0;
    coefLine line;

    line=linearRelation (A,B);
    if (C.y == line.m * C.x + line.p ){
        retour=1;
    }
    return retour;
}
/**
 * @brief checkIfSnapshopInAllSnap check if the new Snapshot is already in all_snapshots
 * @param all_snapshots liste of all the snapshot possible
 * @param numberSnapshot number of snapshot in all_snapshots
 * @param newSnapshot
 * @return 1 : the new Snapshot is already in all_snapshots , else 0
 */
uint8_t checkIfSnapshopInAllSnap (snapshot_t all_snapshots[],uint16_t numberSnapshot,snapshot_t newSnapshot){
    uint8_t check = 0;
    for (uint16_t i = 0; i<numberSnapshot;i++){
        if (equal(newSnapshot,all_snapshots[i])==1){
            check=1;
        }
    }
    return check;
}
/**
 * @brief positionReceiverInSnapshot The function returns position of all the receivers present in the snapshot
 * @param snapshot
 * @param system information about the system : position Receiver, number of receivers, ..
 * @return position of all the receivers present in the snapshot
 */
positionReceivers positionReceiverInSnapshot (snapshot_t snapshot,infoSystem system){
    positionReceivers receivers;
    receivers.numberReceivers=0;
     for (uint16_t i=0;i<snapshot.nreceivers;i++){
         for (uint16_t j=0;j<system.numberReceivers;j++){
             if ((snapshot.receivers[i] & system.pos[j].id) == system.pos[j].id){
                 receivers.pos[receivers.numberReceivers]=system.pos[j];
                 printf("id = %d\n",system.pos[j].id);
                 printf("x = %d\n",system.pos[j].x);
                 printf("y = %d\n",system.pos[j].y);
                 receivers.numberReceivers++;
             }
         }
     }
    printf("number of receivers = %d\n",receivers.numberReceivers);
    return receivers;
}
infoSystem initSystem (){
    infoSystem system;
    system.numberReceivers=4;
    system.pos[0].x=1;
    system.pos[0].y=1;
    system.pos[0].id=1;
    system.pos[1].x=1;
    system.pos[1].y=-1;
    system.pos[1].id=2;
    system.pos[2].x=-1;
    system.pos[2].y=-1;
    system.pos[2].id=4;
    system.pos[3].x=-1;
    system.pos[3].y=1;
    system.pos[3].id=8;

    return system;
}
void createAllSnap (infoSystem system){
    uint16_t numberOneReceiver=0;
    snapshot_t all_snapshots[1000],snapTest;

    /* Single individual receivers */
    all_snapshots[0].nreceivers=0;
    all_snapshots[0].receivers[0]=0;
    display(all_snapshots[0]);
    numberOneReceiver++;

    if (system.numberReceivers>2){
        /* Single individual receivers */
        //For each receiver, create a snapshot with its id
        for (uint16_t i=0;i<system.numberReceivers;i++){
            all_snapshots[numberOneReceiver].nreceivers=1;
            all_snapshots[numberOneReceiver].receivers[0]=system.pos[i].id;
            display(all_snapshots[numberOneReceiver]);
            positionReceiverInSnapshot (all_snapshots[numberOneReceiver],system);
            numberOneReceiver++;
        }

        /* Single combined receivers */
        snapTest.nreceivers=1;
        // combined two receivers
        for (uint16_t i=0;i<system.numberReceivers;i++){
            for (uint16_t j=0;j<system.numberReceivers;j++){
                //If it is not the same receiver
                if (system.pos[i].id!=system.pos[j].id){
                    // Add the two id
                    snapTest.receivers[0]=system.pos[i].id + system.pos[j].id;
                    //Check if this new combined receivers is already created
                    if (checkIfSnapshopInAllSnap(all_snapshots,numberOneReceiver,snapTest)==0){
                        //If it's a new snapshot, add this snapshot in all_snapshots
                        all_snapshots[numberOneReceiver]=snapTest;
                        display(all_snapshots[numberOneReceiver]);
                        positionReceiverInSnapshot (all_snapshots[numberOneReceiver],system);
                        numberOneReceiver++;
                    }
                }
            }
        }
        printf("numberOneReceiver  = %d\n",numberOneReceiver);


        //combined more than two receivers

            // take the combined snapshot with n-1 receivers
            // take one receiver ( 0 to system.numberReceivers), check if this new receiver is not already in the combined snapshot,
            // if not check if this new point is aligned with the other point in the snapshot
            // if they are aligned create a new id combined.


            //        = > (snapshot & newid) != newid    // this new receiver is not already in the combined snapshot
            //        = > position=positionReceiverInSnapshot (snapshot,system)  // retrieve the positions of receivers present in the snapshot
            //        = > pointsAligned(position[0],position[1],new point)     // check if this new point is aligned with points belongings in the snapshot



        /* More than one receiver */
            //Take one previous snapshot with n-1 receivers, take one receiver belonging to all_snapshots , if this new receivers it is not
            //in previous snapshot with n-1 receivers, create a new snapshot with n receivers

            //For each receivers with 1 receivers ( * )
                //Create a tab : position of a receiver (*) with 1 ,2 ,3 ,... receivers
                // For each number of receivers allowed in a snapshot ( system.numberReceivers - 1)
                        //take all the snapshot created with the snapshot [0] is (* ) and the number of receivers is n-1
                                // For each receivers with 1 receivers
                                        // if this new id is not already in the snapshot
                                                //  create a new snapshot with n receivers and the snapshot[n] = id


    }
}
