#include "snapshot.h"
/**
  * @file The objective of the program is to determine the movement made by the object.This movement can be broken down
  * into several snapshots (each snapshot is different). The snapshot is composed of the receptors present in front of the object.
  * These snapshots necessarily start and end with 0 receptors in front of the object.
  * We must first read the data to know the position of the snapshot sequence
  * In order to create these snapshots, we will read the information from the sensors in the file. Identify the receivers in front of
  * the object (valid == 1). Create a snapshot. And if this new snapshot is different from the previous one, this means that the receiver
  * states have changed and therefore it is a new snapshot to represent the movement of the object.
  */



/**
 * @brief detectionStartOfSequence The function allows to determine if the object is in front of one or more receivers.
 * If the object is in front of a receiver, then valid = 1. This function will check the value of valid for all receivers.
 * We will use this function to know the position of the information sequence
 * @param receivers Information id, time, valid for all receivers at an instant t
 * @param numberReceivers number of receiver
 * @return 1 : object is in front one or more receivers;  else 0
 */
uint8_t detectionStartOfSequence (allreceivers_info_t receivers,uint16_t numberReceivers){
    uint8_t start=0;
    //For each receiver
    for (uint16_t i=0;i<numberReceivers;i++){
        //Check the value of valid
        if (receivers.receivers[i].valid==1){
            start=1;
        }
    }
    return start;
}


/**
 * @brief snapshotCreation_t Creation of a snapshot. Read the receiver states, if the receiver is in front of the object (valid == 1),
 * add its id to the snapshot.
 * @param receivers receivers information at a time t
 * @param numberReceivers number of receivers in the simulation
 * @return snapshot at time t
 */
snapshot_t snapshotCreation_t (allreceivers_info_t receivers,uint16_t numberReceivers){
    snapshot_t snapshotReceivers_t;
    snapshotReceivers_t.nreceivers=0;

    //For each receiver
    for (uint16_t i=0;i<numberReceivers;i++){
        //If the object is in front the receiver ( valid=1 )
        if (receivers.receivers[i].valid==1){
            //Add its id in the snapshot
            snapshotReceivers_t.receivers[snapshotReceivers_t.nreceivers]=receivers.receivers[i].id;
            printf("id = %d\n",receivers.receivers[i].id);
            //the number of receivers in the snapshot increases by 1
            snapshotReceivers_t.nreceivers++;
        }
    }
    return snapshotReceivers_t;
}
/**
 * @brief equal The function allows to know if two elements of the type snapshot_t are equal.
 * We must first compare if the two snapshots have the same number of receivers. If so, see if they are the same receivers.
 * @param snapshotReceivers_t
 * @param lastsnapshot
 * @return 1 : The two elements are equal, else 0
 */
uint8_t equal (snapshot_t snapshotReceivers_t,snapshot_t lastsnapshot){
    uint8_t equal=0;
    // if the two snapshots have the same number of receivers
    if (lastsnapshot.nreceivers==snapshotReceivers_t.nreceivers){
        // For each receiver
        for(uint8_t i=0;i<lastsnapshot.nreceivers;i++){
            //Verify that these are the same ids
            if(lastsnapshot.receivers[i]==snapshotReceivers_t.receivers[i]){
                equal=1;
            }
        }
    }
    return equal;
}
/**
 * @brief snapshotCreation Creation of the snapshot list
 * @param receivers, receivers information
 * @return different snapshots that represent the movement of the object
 */
snapshot snapshotCreation (allreceivers_info receivers){
    uint16_t time=0;
    snapshot snapshotReceivers;
    snapshot_t snapshotReceivers_t;

    // This loop makes it possible to determine the 1st instant when the object is in front of a receiver.
    while (detectionStartOfSequence (receivers.t[time],receivers.numberReceivers)==0){
        time++;
    }
    printf("Start of the sequence : %d ms\n",time);

    //Creation of the first snapshot
    snapshotReceivers.t[0] = snapshotCreation_t (receivers.t[time],receivers.numberReceivers);
    snapshotReceivers.numberSnapshot=1;
    time++;

    //For each ms
    for (time;time<receivers.timeSimulationTotal;time++){
        printf("time = %d\n",time);

        //Calculate the snapshot at the time t = time
        snapshotReceivers_t= snapshotCreation_t (receivers.t[time],receivers.numberReceivers);
        //We compare this new snapshot with the last snapshop present in the variable snapshotReceivers
        //if this new snapshot is different, and if it is different from 0, we add it in snapshotReceivers
        //If it is equal to 0, it means that we are at the end of a sequence
        if ((equal (snapshotReceivers_t,(snapshotReceivers.t[snapshotReceivers.numberSnapshot-1]))==0)&&(snapshotReceivers_t.nreceivers>0)){
            snapshotReceivers.t[snapshotReceivers.numberSnapshot] = snapshotReceivers_t;
            snapshotReceivers.numberSnapshot++;
        }
    }

    printf("number of snapshot = %d\n",snapshotReceivers.numberSnapshot);

    display(snapshotReceivers);

    return snapshotReceivers;
}
/**
 * @brief display The function allows to display all the elements of snapshotReceivers
 * @param snapshotReceivers different snapshots that represent the movement of the object
 */
void display(snapshot snapshotReceivers){
    // For each snapshot
    for (uint16_t s=0;s<snapshotReceivers.numberSnapshot;s++){
        printf("snapshot %d\n",s);
        // For each receiver
        for(uint16_t r=0;r<snapshotReceivers.t[s].nreceivers;r++){
            printf("ID = %d\n",snapshotReceivers.t[s].receivers[r]);
        }
    }
}
