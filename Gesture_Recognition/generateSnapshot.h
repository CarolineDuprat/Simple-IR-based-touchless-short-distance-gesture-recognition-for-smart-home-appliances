#ifndef GENERATESNAPSHOT_H
#define GENERATESNAPSHOT_H
#include "structure.h"


coefLine linearRelation (position A,position B);
uint8_t pointsAligned(position A,position B,position C);
uint8_t checkIfSnapshopInAllSnap (snapshot_t all_snapshots[],uint16_t numberSnapshot,snapshot_t newSnapshot);

snapshots createAllSnap (infoSystem system);
positionReceivers positionReceiverInSnapshot (snapshot_t snapshot,infoSystem system);
void displayAllSnap(snapshots all_snapshots,uint16_t number);
#endif // GENERATESNAPSHOT_H
