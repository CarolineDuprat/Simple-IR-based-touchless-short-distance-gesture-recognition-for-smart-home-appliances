#ifndef GENERATESNAPSHOT_H
#define GENERATESNAPSHOT_H
#include "structure.h"


coefLine linearRelation (position A,position B);
uint8_t pointsAligned(position A,position B,position C);
uint8_t checkIfSnapshopInAllSnap (snapshot_t all_snapshots[],uint16_t numberSnapshot,snapshot_t newSnapshot);

snapshots createAllSnap (infoSystem system);
positionReceivers positionReceiverInSnapshot (snapshot_t snapshot,infoSystem system);
void displayAllSnap(snapshots all_snapshots,uint16_t number);

dataGesture SnapshotsAngle (infoSystem system,uint16_t angle);
dataGestures createDataBase (infoSystem system);
snapshots extractSnapshot (dataGestures dataGestures);
transition extractTransition (dataGestures dataGestures,snapshots all_snapshots);
uint16_t positioninAll_Snapshots (snapshots all_snapshots,snapshot_t snapshot);
dataGestures init ();
void displayAllTransition(snapshots all_snapshots,transition transitions);
dataGesture SnapshotsAngle (infoSystem system,uint16_t angle);
void displayDataGesture(dataGestures dataGestures);


#endif // GENERATESNAPSHOT_H
