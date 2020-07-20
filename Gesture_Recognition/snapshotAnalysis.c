#include "snapshot.h"
#include "snapshotAnalysis.h"
#include "gesture.h"

/**
  * @file After creating the snapshots, you have to analyze them to determine the movement. For this he will have to study the transitions between
  * the different snapshots.
  *
  * To know which movement corresponds to each transition, you will have to create a database with each possible transition (transitions_rows,transitions_pool).
  *
  * All mouvements begin with the snapshot {0, {0x00}}, its position is 0 in all_snapshots. We research the transition between this snapshot and the next snapshot.
  * We know the position of the transition allows after {0, {0x00}} with transitions_rows. After that we will see the transition at the position allows in transitions_pool.
  * We get back the information about the position of the next snapshot in all_snapshots and the gesture allows is that transition.
  * We do a logical AND between the before gesture and this gesture.
  * We repeate this procedure for each transition.
  *
  * After that, we convert the id of the gesture to its name.
  *
  */


/**
 * @brief snapshotEqualAll_snapshots The function compare the snapshot and a snapshot at the position counter in the list of all_snapshots
 * @param snapshot
 * @param counter snapshot's position in the all_snapshots
 * @return 1 : both snapshots are equal, else 0
 */
uint16_t snapshotEqualAll_snapshots (const snapshot_t snapshot,uint16_t counter){
    uint16_t retour=0;
    const snapshot_t *all_snapshots=get_all_snapshots();

    //Compare snapshot and snapshot at the position counter in all_snapshots
    if (equal(snapshot,all_snapshots[counter])==1){
        retour=1;
    }
    return retour;
}


/**
 * @brief snapshotResearchTransitions_pool The function allows to return the position of the transition in transitions_pool : gesture's ID
 * and the position of the next snapshot in all_snapshots
 * @param snapshot next snapshot
 * @param position of the snapshot in the all_snapshots
 * @return the position of the transition in transitions_pool
 *                if the transition is not allowed, counter=1000
 */
uint16_t snapshotResearchTransitions_pool (const snapshot_t snapshot,uint16_t position){
    const uint16_t *transitions_rows=get_transitions_rows();
    const transitions_t *transitions_pool=get_transitions_pool();
    uint16_t counter,retour=0;

    //transition allowed after the snapshot at the position "position" is between transitions_rows[position] and transitions_rows[position+1]
    counter=transitions_rows[position];

    //We will compare the next snapshot with which snapshot allows.
    do{
        retour=snapshotEqualAll_snapshots (snapshot,transitions_pool[counter].snapshotID);
        if (retour==0){
            counter++;
        }
    }while((counter<=transitions_rows[position+1])&&(retour==0)); // for all positions allow

    //If the next snapshot is not found => the transition is not allowed
    if (retour==0){
        counter=1000;
    }

    return counter;
}
/**
 * @brief snapshotsGesture determine the id of the gesture
 * @param snapshots different snapshots that represent the movement of the object
 * @return id of the gesture
 */
uint16_t snapshotsGesture (snapshot snapshots){
    const transitions_t *transitions_pool=get_transitions_pool();
    uint16_t gestureID,positionTransitionPool=0,positionAllSnap;

    //All mouvements begin with the snapshot {0, {0x00}}, its position is 0 in all_snapshots
    positionAllSnap=0;

    //all gestures are possible
    gestureID=0xff;

    printf("gesture t : %d\n",gestureID);

    //For each snapshot
    for (uint16_t i=0;i<snapshots.numberSnapshot;i++){

        printf("transition : %d\n",i);

        //research the next snapshot in the transition allowed after the snapshot at the position "positionAllSnap"
        positionTransitionPool=snapshotResearchTransitions_pool (snapshots.t[i],positionAllSnap);
        printf("position TransitionPool : %d\n",positionTransitionPool);

        //If positionTransitionPool==1000, the transition is not allowed
        if (positionTransitionPool==1000){
            printf("the transition is not allowed");
            //Any gesture
            gestureID=0x00;
        }
        else{
            printf("gesture t : %d\n",transitions_pool[positionTransitionPool].gestureID);

            // Logical AND between the before gestureID and the gesture allows with this new transition
            gestureID= gestureID & transitions_pool[positionTransitionPool].gestureID;
            printf("gesture  = %d\n",gestureID);

            // the position of the next snapshot is transitions_pool[positionTransitionPool].snapshotID
            positionAllSnap=transitions_pool[positionTransitionPool].snapshotID;
            printf("position next snapshot : %d\n",positionAllSnap);
        }
    }
    return gestureID;
}
/**
 * @brief nameGesture the function displays the name of the gesture
 * @param gestureID id of the gesture
 */
void nameGesture (uint16_t gestureID ){

    if (GESTURE_TB == gestureID ){
        printf("Vertical top to bottom\n");
    }
    else
        if(GESTURE_BT == gestureID){
            printf("Vertical bottom to top \n");
    }
    else
        if(GESTURE_LR == gestureID){
            printf("Horizontal left to right\n");
    }
    else
        if(GESTURE_RL == gestureID){
            printf("Horizontal right to left\n");
    }
    else
        if(GESTURE_TLBR == gestureID){
            printf("Diagonal top-left to bottom-right\n");
    }
    else
        if(GESTURE_TRBL == gestureID){
            printf("Diagonal top-right to bottom-left\n");
    }
    else
        if(GESTURE_BLTR == gestureID){
            printf("Diagonal bottom-left to top-right\n");
    }
    else
        if(GESTURE_BRTL == gestureID){
            printf("Diagonal bottom-right to top-left\n");
    }
    else
        if(GESTURE_ALL == gestureID){
            printf("All gestures \n");
    }
    else
        if(GESTURE_NONE == gestureID){
            printf("Error\n");
    }
    else{
        printf("Many gestures are possible\n");
    }
}






