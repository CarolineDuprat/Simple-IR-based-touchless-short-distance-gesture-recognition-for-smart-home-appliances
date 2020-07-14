#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "structure.h"

const snapshot_t *get_all_snapshots(void);

uint8_t detectionStartOfSequence (allreceivers_info_t receivers,uint16_t numberReceivers);

snapshot snapshotCreation (allreceivers_info receivers);

snapshot_t snapshotCreation_t (allreceivers_info_t receivers,uint16_t numberReceivers);

uint8_t equal (snapshot_t snapshotReceivers_t,snapshot_t lastsnapshot);

void display(snapshot snapshotReceivers);

uint8_t valeurInTab ( uint16_t newNbrReceivers, uint16_t newIDReceivers[],uint16_t somme);

snapshot_t combinedReceivers(snapshot_t_time snapshotReceivers_t);
#endif // SNAPSHOT_H
