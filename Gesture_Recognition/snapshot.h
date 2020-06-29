#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "structure.h"

uint8_t detectionStartOfSequence (allreceivers_info_t receivers,uint16_t numberReceivers);

snapshot snapshotCreation (allreceivers_info receivers);

snapshot_t snapshotCreation_t (allreceivers_info_t receivers,uint16_t numberReceivers);

uint8_t equal (snapshot_t snapshotReceivers_t,snapshot_t lastsnapshot);

void display(snapshot snapshotReceivers);

#endif // SNAPSHOT_H
