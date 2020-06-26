#include "snapshot.h"

/**
 * @brief detectionStartOfSequence The function allows to determine if the object is in front of one or more receivers.
 * If the object is in front of a receiver, then valid = 1. This function will check the value of valid for all receivers.
 * @param receivers Information id, time, valid for all receivers at an instant t
 * @param numberReceivers number of receiver
 * @return 1 : object is in front one or more receivers;  else 0
 */
uint8_t detectionStartOfSequence (allreceivers_info_t receivers,uint16_t numberReceivers){
    uint8_t start=0;
    for (uint16_t i=0;i<numberReceivers;i++){
        if (receivers.receivers[i].valid==1){
            start=1;
        }
    }
    return start;
}

/**
 * @brief snapshotCreation The function is not finished
 * @param receivers
 */
void snapshotCreation (allreceivers_info receivers){
    uint16_t time=0;
    // This loop makes it possible to determine the 1st instant when the object is in front of a receiver.
    while (detectionStartOfSequence (receivers.t[time],receivers.numberReceivers)==0){
        time++;
    }
    printf("time = %d\n",time);
}

