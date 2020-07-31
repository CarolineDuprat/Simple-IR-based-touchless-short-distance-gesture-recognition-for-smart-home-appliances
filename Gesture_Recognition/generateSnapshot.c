#include "generateSnapshot.h"
#include "snapshot.h"

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
                 //printf("id = %d\n",system.pos[j].id);
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
 * @brief SnapshotsAngle Calcul all snapshots to produce a movement
 * @param system information about the system : position Receiver, number of receivers, ..
 * @param angle Angular position of the obstacle [°]
 * @param speed speed of the object [m/s]
 * @param id id of the movement
 * @return all snapshots to produce a movement
 */
dataGesture SnapshotsAngle (infoSystem system,uint16_t angle,uint16_t speed,uint16_t id){
    dataGesture gesture;
    returnSpeedPos infoSpeedPos;
    dimension dimensionObject;
    uint16_t distance=DISTANCE,totalTime;
    corner positionCornerRotation,positionCorner;
    position positionObject;
    uint8_t inRectangle;
    allreceivers_info_t receivers;
    snapshot_t snapshot;

    //Init gesture
    gesture.id=id;
    gesture.angle=angle;
    gesture.snapshot[0].nreceivers=0;
    gesture.snapshot[0].receivers[0]=0;
    gesture.nbrsnapshots=1;
    //display(gesture.snapshot[0]);

    //Init dimension of the object
    dimensionObject.width=(distanceMaxReceiverLinearRelationTab (angle,system)*2)+1;
    dimensionObject.length=OBJECT_LENGTH;

    //Calcul the total time
    totalTime=simulationTime (distance,speed);
    //Calcul initial position of the object, horirontal & vertical speed
    infoSpeedPos = HorizontalAndVerticalSpeed (distance,speed,angle);
    //Position Corner after the rotation
    positionCornerRotation = rotationCorner (dimensionObject,angle);

    receivers.numberReceivers=system.numberReceivers;

    //Init the id of each receiver
    for (uint16_t i=0;i< system.numberReceivers;i++){
        receivers.receivers[i].id=1 << i;
    }

    for (uint16_t t=0;t< totalTime+1;t++){
        //Calcul the new position of the object after time=t
        positionObject=positionMoveObject (infoSpeedPos ,t);
        //Calcul the new position of corners
        positionCorner=ReelPositionCorner (positionObject,positionCornerRotation);
        for (uint16_t r=0;r<system.numberReceivers;r++){
            //Check if the receiver is in the object

            inRectangle=ReceiverCovered (system.pos[r],positionCorner);

            // If inrectangle==1 => the object is in front a receiver
            // We must keep in memory the first time that the object is in front of the receiver, so we must check the
            // valid state on the front turn.

            if ((inRectangle==1)&&(receivers.receivers[r].valid==0)){
                receivers.receivers[r].time=t;
                receivers.receivers[r].valid=1;
            }else if(inRectangle==1){
                receivers.receivers[r].valid=1;
            }else{
                receivers.receivers[r].time=0;
                receivers.receivers[r].valid=0;
            }
        }
        //Create a snapshot
        snapshot=snapshotCreation_t (receivers);
        //Check if this snapshot is different of {0,{0}} and the previous snapshot
        if ((equal (snapshot,gesture.snapshot[0])==0)&&(equal(snapshot,gesture.snapshot[gesture.nbrsnapshots-1])==0)){
            //Add this snapshot in gesture
            gesture.snapshot[gesture.nbrsnapshots]=snapshot;
            //display(snapshot);
            gesture.nbrsnapshots++;
        }
    }
    return gesture;
}

/**
 * @brief createDataBase create a database with all movements allowed
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

        //calculation of angles allowed

        //printf("direction %d\n",system.gesture[i].NAngle);
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
            //printf("angle  = %d\n",angle);
            //Create all snapshots to make the movement with the direction = angle
            //Add gesture for more speed ....
            gesture = SnapshotsAngle (system,angle,5,system.gesture[i].id);
            //printf("gesture.nbrsnapshots  = %d\n",gesture.nbrsnapshots);
            dataGestures.movement[dataGestures.numberMovements]=gesture;
            dataGestures.numberMovements++;
        }
    }
    //printf("dataGestures.numberMovements  = %d\n",dataGestures.numberMovements);
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
    //displayAllSnap(all_snapshots,all_snapshots.nbrsnapshots);
    //printf("NumberSnap  = %d\n",all_snapshots.nbrsnapshots);
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

        //printf("---------------------------------------------------- \n");
        //display(all_snapshots.snapshot[i]);
        transitions.transitions_rows[i]=numberTransition;
        //printf("Start %d \n",numberTransition);
        //printf("---------------------------------------------------- \n");

        //Research this snapshot in dataGestures
        //For each movement
        for (uint16_t l=0;l<dataGestures.numberMovements;l++){

            //For each snapshot
            for (uint16_t j=0;j<dataGestures.movement[l].nbrsnapshots-1;j++){
                //display(dataGestures.movement[l].snapshot[j]);

                if (equal(all_snapshots.snapshot[i],dataGestures.movement[l].snapshot[j])==1){
                    //printf("equal\n");

                    //Take next snap => research position in all snap
                    positionSnapshot = positioninAll_Snapshots (all_snapshots,dataGestures.movement[l].snapshot[j+1]);
                    //printf("position next snap %d \n",positionSnapshot);

                    //Research if the snapshot is already in the transition
                    positionTransition = transitions.transitions_rows[i];
                    add=0;

                    //if there are any transitions already created for this snapshot
                    if (numberTransition>positionTransition){

                        //Check if this snapshot is in these transitions
                        for (uint16_t k=positionTransition;k<numberTransition;k++){

                            if(transitions.transitions_pool[k].snapshotID == positionSnapshot){
                                //printf("already in the transition\n");
                                //Add a new gesture in the gesture allowed with this transition
                                transitions.transitions_pool[k].gestureID = transitions.transitions_pool[k].gestureID | dataGestures.movement[l].id;
                                //printf("new gesture %d \n",transitions.transitions_pool[k].gestureID);
                                add=1;
                            }
                        }
                    }
                    //If it's a new transition
                    if(add==0){
                        //printf("create transition\n");
                        transitions.transitions_pool[numberTransition].snapshotID=positionSnapshot;
                        transitions.transitions_pool[numberTransition].gestureID=dataGestures.movement[l].id;
                        numberTransition++;
                    }
                }
            }
        }
    }
    transitions.transitions_rows[all_snapshots.nbrsnapshots]=numberTransition;
    //displayAllTransition(all_snapshots,transitions);

    return transitions;
}

