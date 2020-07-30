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
//-------------------------------------------------------------------------------------------------------------------------------------------------------------


dataGesture SnapshotsAngle (infoSystem system,uint16_t angle){
    dataGesture gesture;
    gesture.id=0;
    if ((angle==0)||(angle==359)||(angle==1)){
        printf("angle 0 : %d\n",angle);
        gesture.id=1;
        gesture.angle=0;
        gesture.nbrsnapshots=4;
        gesture.snapshot[0].nreceivers=0;
        gesture.snapshot[0].receivers[0]=0;
        gesture.snapshot[1].nreceivers=1;
        gesture.snapshot[1].receivers[0]=3;
        gesture.snapshot[2].nreceivers=2;
        gesture.snapshot[2].receivers[0]=3;
        gesture.snapshot[2].receivers[1]=12;
        gesture.snapshot[3].nreceivers=1;
        gesture.snapshot[3].receivers[0]=12;
    }
    else if ((angle==90)||(angle==89)||(angle==91)){
        printf("angle 90 : %d\n",angle);
        gesture.id=2;
        gesture.angle=90;
        gesture.nbrsnapshots=4;
        gesture.snapshot[0].nreceivers=0;
        gesture.snapshot[0].receivers[0]=0;
        gesture.snapshot[1].nreceivers=1;
        gesture.snapshot[1].receivers[0]=9;
        gesture.snapshot[2].nreceivers=2;
        gesture.snapshot[2].receivers[0]=9;
        gesture.snapshot[2].receivers[1]=6;
        gesture.snapshot[3].nreceivers=1;
        gesture.snapshot[3].receivers[0]=6;
    }
    else if ((angle==180)||(angle==179)||(angle==181)){
        printf("angle 180 : %d\n",angle);
        gesture.id=4;
        gesture.angle=180;
        gesture.nbrsnapshots=4;
        gesture.snapshot[0].nreceivers=0;
        gesture.snapshot[0].receivers[0]=0;
        gesture.snapshot[1].nreceivers=1;
        gesture.snapshot[1].receivers[0]=12;
        gesture.snapshot[2].nreceivers=2;
        gesture.snapshot[2].receivers[0]=12;
        gesture.snapshot[2].receivers[1]=3;
        gesture.snapshot[3].nreceivers=1;
        gesture.snapshot[3].receivers[0]=3;
    }
    else if ((angle == 270)||(angle==269)||(angle==271)){
        printf("angle 270 : %d\n",angle);
        gesture.id=8;
        gesture.angle=270;
        gesture.nbrsnapshots=4;
        gesture.snapshot[0].nreceivers=0;
        gesture.snapshot[0].receivers[0]=0;
        gesture.snapshot[1].nreceivers=1;
        gesture.snapshot[1].receivers[0]=6;
        gesture.snapshot[2].nreceivers=2;
        gesture.snapshot[2].receivers[0]=6;
        gesture.snapshot[2].receivers[1]=9;
        gesture.snapshot[3].nreceivers=1;
        gesture.snapshot[3].receivers[0]=9;
    }
    return gesture;
}
/**
 * @brief createDataBase
 * @param system information about the system : number of receivers, positions,
 * @return list of data with all the movement allowed
 */
dataGestures createDataBase (infoSystem system){
    uint16_t angle=0;
    int16_t minAngle,maxAngle;
    dataGesture gesture;
    dataGestures dataGestures;
    dataGestures.numberMovements=0;

    //For each gesture
    for (uint16_t i=0;i<system.numberGesture;i++){
        printf("direction %d\n",system.gesture[i].NAngle);
        minAngle=system.gesture[i].NAngle-system.gesture[i].DAngle;
        maxAngle=system.gesture[i].NAngle+system.gesture[i].DAngle+1;
        //From minAngle to maxAngle ranging from 1 in 1
        for (int16_t j=minAngle;j<maxAngle;j++){
            if (j < 0){
                angle=360+j;
            }else if (j> 359){
                angle=360-j;
            }else{
                angle=j;
            }
            printf("angle  = %d\n",angle);
            //Create all snapshots to make the movement with the direction = angle
            gesture = SnapshotsAngle (system,angle);
            printf("gesture.nbrsnapshots  = %d\n",gesture.nbrsnapshots);
            dataGestures.movement[dataGestures.numberMovements]=gesture;
            dataGestures.numberMovements++;
        }
    }
    printf("dataGestures.numberMovements  = %d\n",dataGestures.numberMovements);
    return dataGestures;
}
/**
 * @brief displayDataGesture display data
 * @param dataGestures list of data with all the movement allowed
 */
void displayDataGesture(dataGestures dataGestures){
    //For each snapshot
    printf("dataGestures.numberMovements  = %d\n",dataGestures.numberMovements);
    for (uint16_t i=0;i<dataGestures.numberMovements;i++){
        printf("dataGestures.movement[%d].nbrsnapshots  = %d\n",i,dataGestures.movement[i].nbrsnapshots);
        for (uint16_t j=0;j<dataGestures.movement[i].nbrsnapshots;j++){
           display(dataGestures.movement[i].snapshot[j]);
        }
    }
}
/**
 * @brief displayAllSnap display a list of snapshots
 * @param all_snapshots list of snapshots
 * @param number number of snapshots
 */
void displayAllSnap(snapshots all_snapshots,uint16_t number){
    //For each snapshot
    for (uint16_t i=0;i<number;i++){
        display(all_snapshots.snapshot[i]);
    }
}
/**
 * @brief extractSnapshot The function takes all the different snapshots in dataGesture, and create a liste with all these snapshots
 * @param dataGestures list of data with all movements allowed
 * @return all_snapshots
 */
snapshots extractSnapshot (dataGestures dataGestures){
    snapshots all_snapshots;

    //Init with the snapshot {0,{0}}
    all_snapshots.snapshot[0].nreceivers=0;
    all_snapshots.snapshot[0].receivers[0]=0;
    all_snapshots.nbrsnapshots=1;

    //For each movement
    for (uint16_t i=0;i<dataGestures.numberMovements;i++){

       //For each snapshot
       for (uint16_t j=0;j<dataGestures.movement[i].nbrsnapshots;j++){

            //If the snapshot is new
            if (checkIfSnapshopInAllSnap(all_snapshots.snapshot,all_snapshots.nbrsnapshots,dataGestures.movement[i].snapshot[j])==0){
                all_snapshots.snapshot[all_snapshots.nbrsnapshots]=dataGestures.movement[i].snapshot[j];
                all_snapshots.nbrsnapshots++;
            }
        }
    }
    displayAllSnap(all_snapshots,all_snapshots.nbrsnapshots);
    printf("NumberSnap  = %d\n",all_snapshots.nbrsnapshots);
    return all_snapshots;
}
/**
 * @brief positionAll_Snapshots research the position of the snapshot in all_snapshots
 * @param all_snapshots list of snapshots
 * @param snapshot
 * @return the position of the snapshot
 */
uint16_t positioninAll_Snapshots (snapshots all_snapshots,snapshot_t snapshot){
    uint16_t position;
    //For each snapshot
    for (uint16_t i=0;i<all_snapshots.nbrsnapshots;i++){
        //If the snapshot in all_snapshots equals snapshot => keep the position of this snapshot in position
        if (equal(all_snapshots.snapshot[i],snapshot)==1){
            position=i;
        }
    }
    return position;
}
/**
 * @brief displayAllSnap display the row and the pool transition
 * @param all_snapshots list of snapshots
 * @param transitions all the transition after each snapshot
 */
void displayAllTransition(snapshots all_snapshots,transition transitions){

    //For each snapshot
    for (uint16_t i=0;i<all_snapshots.nbrsnapshots;i++){

        printf("---------------------------------------------------- \n");
        display(all_snapshots.snapshot[i]);
        printf("---------------------------------------------------- \n");

        //For each transition for this snapshot
        for (uint16_t j=transitions.transitions_rows[i];j<transitions.transitions_rows[i+1];j++){
            printf("transition %d \n",j);
            //Display the snapshot and the gesture
            display(all_snapshots.snapshot[transitions.transitions_pool[j].snapshotID]);
            printf("gesture %d \n",transitions.transitions_pool[j].gestureID);
        }
    }
}
/**
 * @brief extractTransition Create transitions_rows and transitions_pool
 * @param dataGestures list of data with all the movement allowed
 * @param all_snapshots list of snapshots
 * @return transitions_rows and transitions_pool
 */
transition extractTransition (dataGestures dataGestures,snapshots all_snapshots){
    transition transitions;
    uint16_t numberTransition=0,positionSnapshot=0,positionTransition=0,add=0;
    transitions.transitions_rows[0]=0;

    //For each snapshot
    for (uint16_t i=0;i<all_snapshots.nbrsnapshots;i++){

        printf("---------------------------------------------------- \n");
        display(all_snapshots.snapshot[i]);
        transitions.transitions_rows[i]=numberTransition;
        printf("Start %d \n",numberTransition);
        printf("---------------------------------------------------- \n");

        //Research this snapshot in dataGestures
        //For each movement
        for (uint16_t l=0;l<dataGestures.numberMovements;l++){

            //For each snapshot
            for (uint16_t j=0;j<dataGestures.movement[l].nbrsnapshots-1;j++){
                display(dataGestures.movement[l].snapshot[j]);

                if (equal(all_snapshots.snapshot[i],dataGestures.movement[l].snapshot[j])==1){
                    printf("equal\n");

                    //Take next snap => research position in all snap
                    positionSnapshot = positioninAll_Snapshots (all_snapshots,dataGestures.movement[l].snapshot[j+1]);
                    printf("position next snap %d \n",positionSnapshot);

                    //Research if the snapshot is already in the transition
                    positionTransition = transitions.transitions_rows[i];
                    add=0;

                    //if there are any transitions already created for this snapshot
                    if (numberTransition>positionTransition){

                        //Check if this snapshot is in these transitions
                        for (uint16_t k=positionTransition;k<numberTransition;k++){

                            if(transitions.transitions_pool[k].snapshotID == positionSnapshot){
                                printf("already in the transition\n");
                                //Add a new gesture in the gesture allowed with this transition
                                transitions.transitions_pool[k].gestureID = transitions.transitions_pool[k].gestureID | dataGestures.movement[l].id;
                                printf("new gesture %d \n",transitions.transitions_pool[k].gestureID);
                                add=1;
                            }
                        }
                    }
                    //If it's a new transition
                    if(add==0){
                        printf("create transition\n");
                        transitions.transitions_pool[numberTransition].snapshotID=positionSnapshot;
                        transitions.transitions_pool[numberTransition].gestureID=dataGestures.movement[l].id;
                        numberTransition++;
                    }
                }
            }
        }
    }
    transitions.transitions_rows[all_snapshots.nbrsnapshots]=numberTransition;
    displayAllTransition(all_snapshots,transitions);

    return transitions;
}

