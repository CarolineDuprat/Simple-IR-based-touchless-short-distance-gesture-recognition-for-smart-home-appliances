#include "generateSnapshot.h"
#include "snapshot.h"


/**
 * @brief linearRelation calcul the coefficent of the line passing through A and B  a * y = m * x + p
 *       yB - yA
 * m = ------------   and p = yA - m * xA  and a = 1
 *       xB - xA
 * @param A
 * @param B
 * @return m and p
 */
coefLine linearRelation (position A,position B){
    coefLine line;
    // aligned with axe y  x = A.x
    if ((B.x - A.x)==0){
        line.m = 1;
        line.p = - A.x;
        line.a = 0;
    }// aligned with axe x   y = A.y
    else if (( B.y - A.y)==0){
        line.m = 0;
        line.p = A.y;
        line.a = 1;
    }else{
        line.m = ( B.y - A.y)/(B.x - A.x);
        line.p = A.y - ( line.m * A.x );
        line.a = 1;
    }



    printf("eq  %d * y = %d * x + %d \n",line.a,line.m,line.p);

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
    if (line.a * C.y == ( line.m * C.x ) + line.p ){
        retour = 1;
        printf(" aligned \n");
    }else{
       printf(" not aligned\n");
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
    //For each receiver in the snapshot
     for (uint16_t i=0;i<snapshot.nreceivers;i++){
         //For each receiver in the system
         for (uint16_t j=0;j<system.numberReceivers;j++){
             //Test if the receiver is in the snapshot
             if ((snapshot.receivers[i] & system.pos[j].id) == system.pos[j].id){
                 receivers.pos[receivers.numberReceivers]=system.pos[j];
                 printf("id = %d\n",system.pos[j].id);
                 //printf("x = %d\n",system.pos[j].x);
                 //printf("y = %d\n",system.pos[j].y);
                 receivers.numberReceivers++;
             }
         }
     }
    printf("number of receivers = %d\n",receivers.numberReceivers);
    return receivers;
}

/**
 * @brief displayAllSnap display a list of snapshots
 * @param all_snapshots list of snapshots
 * @param number number of snapshots
 */
void displayAllSnap(snapshots all_snapshots,uint16_t number){
    for (uint16_t i=0;i<number;i++){
        display(all_snapshots.snapshot[i]);
    }
}

/**
 * @brief createAllSnap create a list with all the snapshot possible
 * @param system information about the system : number of receivers, positions, .
 * @return list all_snapshots
 */
snapshots createAllSnap (infoSystem system){
    snapshots all_snapshots;
    uint16_t numberOneReceiver=0,numberReceiver=0,pos=0,check=1;
    snapshot_t snapTest;
    positionReceivers position;
    posInAllSnap positionInAllReceivers[1000];

    /* Single individual receivers */

    //First snapshot {0,{0}}
    all_snapshots.snapshot[0].nreceivers=0;
    all_snapshots.snapshot[0].receivers[0]=0;
    display(all_snapshots.snapshot[0]);
    numberOneReceiver++;


    if (system.numberReceivers>0){

        //For each receiver, create a snapshot with its id
        for (uint16_t i=0;i<system.numberReceivers;i++){
            all_snapshots.snapshot[numberOneReceiver].nreceivers=1;
            all_snapshots.snapshot[numberOneReceiver].receivers[0]=system.pos[i].id;
            display(all_snapshots.snapshot[numberOneReceiver]);
            //positionReceiverInSnapshot (all_snapshots[numberOneReceiver],system);
            numberOneReceiver++;
        }
    }
    if (system.numberReceivers>2){
        /* Single combined receivers */

        //Strategy : Take all the snapshot with one id, test for each snapshot each id ( number of receivers in the system)
        //Create a new snapshot if it's a new snapshot
        //Take all the snapshot with two ids combined, test for each snapshot each id ( number of receivers in the system)
        //Create a new snapshot if it's a new snapshot
        //Take all the snapshot with three ids combined,....

        positionInAllReceivers[0].position=1;
        positionInAllReceivers[0].numberSnap=system.numberReceivers;

        //Create snapshot with only one receiver => init here
        snapTest.nreceivers=1;

        // 1 id in the snapshot, 2 ids in the snapshot, 3 ids in the snapshot, ... system.numberReceivers-2
        for (uint16_t j=0;j<system.numberReceivers-2;j++){
            printf("%d id combined    ------------------------------------------------------\n",j+1);
            positionInAllReceivers[j+1].numberSnap=0;

            // For each snapshot with i+1 id combined
            for (uint16_t i=0;i<positionInAllReceivers[j].numberSnap;i++){

                //position of the first snapshot with i+1 id combined
                pos=positionInAllReceivers[j].position + i;
                printf(" ------------------------------------------------------\n");
                display(all_snapshots.snapshot[pos]);
                printf(" ------------------------------------------------------\n");
                //For each receiver
                for (uint16_t k=0;k<system.numberReceivers;k++){
                    printf("test id with  = %d\n",system.pos[k].id);
                    //If the receiver is not already in the snapshot
                    if ((all_snapshots.snapshot[pos].receivers[0] & system.pos[k].id)!=system.pos[k].id){
                        printf("different \n");

                        //if number of id in the snapshot is >1; we have to check if the point are aligned
                        //j=0 one id in the snapshot
                        if (j>0){
                            //position of the receiver on the snapshot
                            position=positionReceiverInSnapshot (all_snapshots.snapshot[pos],system);
                            check=pointsAligned(position.pos[0],position.pos[1],system.pos[k]);
                        }else{
                            check=1;
                        }

                        // if points are aligned or if we have only two ids combined
                        if (check==1){

                            //Create the snapshot
                            snapTest.receivers[0]=all_snapshots.snapshot[pos].receivers[0] + system.pos[k].id;
                            display(snapTest);

                            //Check if this new combined receivers is already created
                            if (checkIfSnapshopInAllSnap(all_snapshots.snapshot,numberOneReceiver,snapTest)==0){

                                //init the position with i+1 id combined
                                if (positionInAllReceivers[j+1].numberSnap==0){
                                    positionInAllReceivers[j+1].position=numberOneReceiver;
                                    printf("position j+1  = %d\n",positionInAllReceivers[j+1].position);
                                }

                                printf("-- new snapshot --\n");

                                //add this snapshot in all_snapshots
                                all_snapshots.snapshot[numberOneReceiver]=snapTest;
                                display(all_snapshots.snapshot[numberOneReceiver]);
                                numberOneReceiver++;
                                positionInAllReceivers[j+1].numberSnap++;
                            }
                        }
                    }
                }
            }
        }
        printf("Single receivers---------------------------------------------------------------\n");
        displayAllSnap(all_snapshots,numberOneReceiver);
        printf("-------------------------------------------------------------------------------\n");
        positionInAllReceivers[0].position=1;
        positionInAllReceivers[0].numberSnap=numberOneReceiver-1;

        numberReceiver=numberOneReceiver;

        /* More than one receiver */

        //Strategy : Take all the snapshot with one receiver, test for each snapshot, each snapshot with one receiver (individual and combined)
        //Create a new snapshot if it's a new snapshot
        //Take all the snapshot with two receivers, test for each snapshot, each snapshot with one receiver (individual and combined)
        //Create a new snapshot if it's a new snapshot
        //Take all the snapshot with three receivers,....


        // 1 receiver in the snapshot, 2 receivers in the snapshot, 3 receivers in the snapshot, ... system.numberReceivers-2
        for (uint16_t j=0;j<system.numberReceivers-2;j++){
            printf("%d receivers in the snapshot ------------------------------------------------------\n",(j+1));
            positionInAllReceivers[j+1].numberSnap=0;

            //For each snapshot with i+1 receivers
            for (uint16_t i=0;i<positionInAllReceivers[j].numberSnap;i++){
                //position of the first snapshot with i+1 receivers
                pos=positionInAllReceivers[j].position + i;

                printf(" ------------------------------------------------------\n");
                display(all_snapshots.snapshot[pos]);
                printf(" ------------------------------------------------------\n");

                //For each receiver (individual and combined)
                for (uint16_t k=0;k<numberOneReceiver-1;k++){
                    printf("test id with  = %d\n",all_snapshots.snapshot[k+1].receivers[0]);
                    //Check if the id isn't already in the snapshot
                    //For each receivers in the snapshot
                    check=0;
                    position.numberReceivers=1;
                    for (uint16_t l=0;l<(j+1);l++){
                        if ((all_snapshots.snapshot[pos].receivers[l] & all_snapshots.snapshot[k+1].receivers[0])!=all_snapshots.snapshot[k+1].receivers[0]){
                            //Check if one of the receiver in all_snapshots[k+1].receivers[0] is not already in the snapshot
                            position=positionReceiverInSnapshot (all_snapshots.snapshot[k+1],system);
                            for (uint16_t c=0;c<position.numberReceivers;c++){
                                if ((all_snapshots.snapshot[pos].receivers[l] & all_snapshots.snapshot[k+1].receivers[0])!=position.pos[c].id){
                                    check++;
                                }
                            }
                        }
                    }
                    if (check == (j+1)*position.numberReceivers){
                        snapTest=all_snapshots.snapshot[pos];
                        snapTest.nreceivers++;
                        snapTest.receivers[j+1]=all_snapshots.snapshot[k+1].receivers[0];
                        //Check if this new combined receivers is already created
                        if (checkIfSnapshopInAllSnap(all_snapshots.snapshot,numberReceiver,snapTest)==0){

                            //init the position with i+1 id combined
                            if (positionInAllReceivers[j+1].numberSnap==0){
                                positionInAllReceivers[j+1].position=numberReceiver;
                                printf("position j+1  = %d\n",positionInAllReceivers[j+1].position);
                            }

                            printf("-- new snapshot --\n");

                            //add this snapshot in all_snapshots
                            all_snapshots.snapshot[numberReceiver]=snapTest;
                            display(all_snapshots.snapshot[numberReceiver]);
                            numberReceiver++;
                            positionInAllReceivers[j+1].numberSnap++;
                        }
                    }
                }
            }
        }
        printf("numberReceiver  = %d\n",numberReceiver);
        printf("AllSnapshot---------------------------------------------------------------\n");
        displayAllSnap(all_snapshots,numberReceiver);
        printf("--------------------------------------------------------------------------\n");
        all_snapshots.nbrsnapshots=numberReceiver;
    }
    return all_snapshots;
}

void createTransitions (snapshots  all_snapshots,infoSystem system){
    transition transition;
    uint16_t numberTransitions=0;

    for (uint16_t i=0;i<all_snapshots.nbrsnapshots;i++){
        transition.transitions_rows[i]=numberTransitions;
        //Add transition...
    }
}
