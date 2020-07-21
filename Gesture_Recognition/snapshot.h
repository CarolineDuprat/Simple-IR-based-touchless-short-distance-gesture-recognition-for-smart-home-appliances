#ifndef SNAPSHOT_H
#define SNAPSHOT_H
#include "structure.h"

const snapshot_t *get_all_snapshots(void);

snapshot_t snapshotCreation_t (allreceivers_info_t receivers);

uint8_t equal (snapshot_t snapshotReceivers_t,snapshot_t lastsnapshot);

void display(snapshot_t snapshotReceivers);

uint8_t valeurInTab ( uint16_t newNbrReceivers, uint16_t newIDReceivers[],uint16_t somme);

snapshot_t combinedReceivers(snapshot_t_time snapshotReceivers_t);

#endif // SNAPSHOT_H
