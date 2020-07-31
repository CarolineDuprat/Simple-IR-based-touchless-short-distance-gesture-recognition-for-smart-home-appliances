#include "snapshot.h"
/**
  * @file The objective of the program is to determine the movement made by the object.This movement can be broken down
  * into several snapshots (each snapshot is different). The snapshot is composed of the receptors present in front of the object.
  * These snapshots necessarily start and end with 0 receptors in front of the object.
  * We must first read the data to know the position of the snapshot sequence
  * In order to create these snapshots, we will read the information from the sensors in the file. Identify the receivers in front of
  * the object (valid == 1). Create a snapshot.
  */


/* This table defines the possible, valid snapshots given the number ofreceivers and shape.This example is for 4 receivers in a rectangle shape.
 * Assume we can combine receivers vertically, horizontally, or diagonally,but L-shapes are considered illegal. */
const snapshot_t all_snapshots[] = {
    /* There are no valid snapshots of 4 receivers */
    /* Mark the end of the table with this special snapshot(0 receivers, receiver ID 0x00) */
    {0, {0x00}}, /* 0 */
    /* Single individual receivers */
    {1, {0x01}}, /* 1 */
    {1, {0x02}}, /* 2 */
    {1, {0x04}}, /* 3 */
    {1, {0x08}}, /* 4 */
    /* Single combined receivers */
    {1, {0x03}}, /* 5 */
    {1, {0x05}}, /* 6 */
    {1, {0x06}}, /* 7 */
    {1, {0x09}}, /* 8 */
    {1, {0x0A}}, /* 9 */
    {1, {0x0C}}, /* 10 */
    /* Two receivers; receiver 0x01 and a second one. */
    /* Impossible combinations: 0x01 followed by 0x9, 0x3, 0x5 */
    {2, {0x01, 0x02}}, /* 11 */
    {2, {0x01, 0x04}}, /* 12 */
    {2, {0x01, 0x08}}, /* 13 */
    {2, {0x01, 0x06}}, /* 14 */
    {2, {0x01, 0x0A}}, /* 15 */
    {2, {0x01, 0x0C}}, /* 16 */
    /* Two receivers; receiver 0x02 and a second one. */
    /* Impossible combinations: 0x02 followed by 0x3, 0x6, 0xA */
    {2, {0x02, 0x01}}, /* 17 */
    {2, {0x02, 0x04}}, /* 18 */
    {2, {0x02, 0x08}}, /* 19 */
    {2, {0x02, 0x05}}, /* 20 */
    {2, {0x02, 0x09}}, /* 21 */
    {2, {0x02, 0x0C}}, /* 22 */
    /* Two receivers; receiver 0x04 and a second one. */
    /* Impossible combinations: 0x04 followed by 0x5, 0x6, 0xC */
    {2, {0x04, 0x01}}, /* 23 */
    {2, {0x04, 0x02}}, /* 24 */
    {2, {0x04, 0x08}}, /* 25 */
    {2, {0x04, 0x03}}, /* 26 */
    {2, {0x04, 0x09}}, /* 27 */
    {2, {0x04, 0x0A}}, /* 28 */
    /* Two receivers; receiver 0x08 and a second one. */
    /* Impossible combinations: 0x08 followed by 0x9, 0xA, 0xC */
    {2, {0x08, 0x01}}, /* 29 */
    {2, {0x08, 0x02}}, /* 30 */
    {2, {0x08, 0x04}}, /* 31 */
    {2, {0x08, 0x03}}, /* 32 */
    {2, {0x08, 0x05}}, /* 33 */
    {2, {0x08, 0x06}}, /* 34 */
    /* Two receivers; receiver 0x03 and a second one. */
    /* Possible combinations: 0x03 followed by 0x4, 0x8, or 0xC */
    {2, {0x03, 0x04}}, /* 35 */
    {2, {0x03, 0x08}}, /* 36 */
    {2, {0x03, 0x0C}}, /* 37 */
    /* Two receivers; receiver 0x05 and a second one. */
    /* Possible combinations: 0x05 followed by 0x2 or 0x8 */
    {2, {0x05, 0x02}}, /* 38 */
    {2, {0x05, 0x08}}, /* 39 */
    /* Two receivers; receiver 0x06 and a second one. */
    /* Possible combinations: 0x06 followed by 0x1, 0x8, or 0x9 */
    {2, {0x06, 0x01}}, /* 40 */
    {2, {0x06, 0x08}}, /* 41 */
    {2, {0x06, 0x09}}, /* 42 */
    /* Two receivers; receiver 0x09 and a second one. */
    /* Possible combinations: 0x09 followed by 0x2, 0x4, or 0x6 */
    {2, {0x09, 0x02}}, /* 43 */
    {2, {0x09, 0x04}}, /* 44 */
    {2, {0x09, 0x06}}, /* 45 */
    /* Two receivers; receiver 0x0A and a second one. */
    /* Possible combinations: 0x0A followed by 0x1 or 0x4 */
    {2, {0x0A, 0x01}}, /* 46 */
    {2, {0x0A, 0x04}}, /* 47 */
    /* Two receivers; receiver 0x0C and a second one. */
    /* Possible combinations: 0x0C followed by 0x1, 0x2, or 0x3 */
    {2, {0x0C, 0x01}}, /* 48 */
    {2, {0x0C, 0x02}}, /* 49 */
    {2, {0x0C, 0x03}}, /* 50 */
    /* Three receivers: Let's assume an L-shape is illegal, so the onlyvalid combinations of 3 receivers are diagonal:receiver, two receivers combined, and receiver */
    {3, {0x01, 0x0A, 0x04}}, /* 51 */
    {3, {0x02, 0x05, 0x08}}, /* 52 */
    {3, {0x04, 0x0A ,0x01}}, /* 53 */
    {3, {0x08, 0x05, 0x02}}, /* 54 */
};

/*const snapshot_t * get_all_snapshots(void) {
    return all_snapshots;
}*/

/**
 * @brief snapshotCreation_t Creation of a snapshot. Read the receiver states, if the receiver is in front of the object (valid == 1),
 * add its id to the snapshot.
 * @param receivers receivers information at a time t
 * @return snapshot at time t
 */
snapshot_t snapshotCreation_t (allreceivers_info_t receivers){
    snapshot_t_time snapshotReceivers_t;
    snapshot_t snapshotReceivers;
    snapshotReceivers_t.nreceivers=0;

    //For each receiver
    for (uint16_t i=0;i<receivers.numberReceivers;i++){
        //If the object is in front the receiver ( valid=1 )
        if (receivers.receivers[i].valid==1){
            //Add its id in the snapshot
            snapshotReceivers_t.receivers[snapshotReceivers_t.nreceivers]=receivers.receivers[i].id;
            snapshotReceivers_t.time[snapshotReceivers_t.nreceivers]=receivers.receivers[i].time;
            //printf("id = %d\n",receivers.receivers[i].id);
            //the number of receivers in the snapshot increases by 1
            snapshotReceivers_t.nreceivers++;
        }
    }
    //Combined Receiver
    snapshotReceivers=combinedReceivers(snapshotReceivers_t);

    return snapshotReceivers;
}

/**
 * @brief combinedReceivers This function allows to group receivers when they are at the same time in front of the object,
 * the function also sort the id by time (sort by selection)
 * @param snapshotReceivers_t
 * @return snapshot with receivers combined
 */
snapshot_t combinedReceivers(snapshot_t_time snapshotReceivers_t){
    snapshot_t snapshotCombined_t;
    snapshotCombined_t.nreceivers=0;
    uint16_t time=0,somme=0,copyTime=0,copyID=0;
    //Sort ID by time
    if (snapshotReceivers_t.nreceivers>1){
        for (uint16_t z=0;z<snapshotReceivers_t.nreceivers-1;z++){
            for (uint16_t y=z+1;y<snapshotReceivers_t.nreceivers;y++){
                if(snapshotReceivers_t.time[z]>snapshotReceivers_t.time[y]){
                    copyTime=snapshotReceivers_t.time[z];
                    copyID=snapshotReceivers_t.receivers[z];
                    snapshotReceivers_t.time[z]=snapshotReceivers_t.time[y];
                    snapshotReceivers_t.receivers[z]=snapshotReceivers_t.receivers[y];
                    snapshotReceivers_t.time[y]=copyTime;
                    snapshotReceivers_t.receivers[y]=copyID;
                }
            }
        }
    }
    //For each receiver
    for (uint16_t i=0;i<snapshotReceivers_t.nreceivers;i++){
        time=snapshotReceivers_t.time[i];
        somme=0;
        //For each receiver
        for (uint16_t t=0;t<snapshotReceivers_t.nreceivers;t++){
            if (time==snapshotReceivers_t.time[t]){
                somme=somme+snapshotReceivers_t.receivers[t];
            }
        }
        if (snapshotCombined_t.nreceivers==0){
            snapshotCombined_t.receivers[0]=somme;
            snapshotCombined_t.nreceivers++;
        }else{
            if (valeurInTab (snapshotCombined_t.nreceivers,snapshotCombined_t.receivers,somme)==0){
                snapshotCombined_t.receivers[snapshotCombined_t.nreceivers]=somme;
                snapshotCombined_t.nreceivers++;
            }
        }
    }
    return snapshotCombined_t;
}
/**
 * @brief valeurInTab The function allows to know if an element is in an array
 * @param newNbrReceivers  number of elements in the array
 * @param newIDReceivers array
 * @param somme element
 * @return 1 : element is in the tab, else 0
 */
uint8_t valeurInTab ( uint16_t newNbrReceivers, uint16_t newIDReceivers[],uint16_t somme){
    uint8_t test=0;
    // For each element in the array
    for(uint16_t t=0;t<newNbrReceivers;t++){
        if (somme==newIDReceivers[t]){
            test=1;
        }
    }
    return test;
}
/**
 * @brief equal The function allows to know if two elements of the type snapshot_t are equal.
 * We must first compare if the two snapshots have the same number of receivers. If so, see if they are the same receivers.
 * @param snapshotReceivers_t
 * @param lastsnapshot
 * @return 1 : The two elements are equal, else 0
 */
uint8_t equal (snapshot_t snapshotReceivers_t,snapshot_t lastsnapshot){
    uint8_t equal=0,counter=0;
    // if the two snapshots have the same number of receivers
    if (lastsnapshot.nreceivers==snapshotReceivers_t.nreceivers){
        // For each receiver
        for(uint8_t i=0;i<lastsnapshot.nreceivers;i++){
            //Verify that these are the same ids

            if(lastsnapshot.receivers[i]==snapshotReceivers_t.receivers[i]){
                counter++;
            }
        }
        //if all the snapshots are the same counter = lastsnapshot.nreceivers
        if (counter==lastsnapshot.nreceivers){
            equal=1;
        }
    }
    return equal;
}
/**
 * @brief display The function allows to display all the elements of snapshotReceivers
 * @param snapshotReceivers snapshot
 */
void display(snapshot_t snapshotReceivers){
    // For each receiver
    printf("snaphot : \n");
    for(uint16_t r=0;r<snapshotReceivers.nreceivers;r++){
        printf("ID = %d\n",snapshotReceivers.receivers[r]);
    }
}
