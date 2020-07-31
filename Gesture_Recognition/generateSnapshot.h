#ifndef GENERATESNAPSHOT_H
#define GENERATESNAPSHOT_H
#include "structure.h"
#include "simulationReceiver.h"

uint8_t checkIfSnapshopInAllSnap (snapshot_t all_snapshots[],uint16_t numberSnapshot,snapshot_t newSnapshot);

positionReceivers positionReceiverInSnapshot (snapshot_t snapshot,infoSystem system);
void displayAllSnap(snapshots all_snapshots,uint16_t number);

dataGesture SnapshotsAngle (infoSystem system,uint16_t angle,uint16_t speed,uint16_t id);
dataGestures createDataBase (infoSystem system);
snapshots extractSnapshot (dataGestures dataGestures);
transition extractTransition (dataGestures dataGestures,snapshots all_snapshots);
uint16_t positioninAll_Snapshots (snapshots all_snapshots,snapshot_t snapshot);
dataGestures init ();
void displayAllTransition(snapshots all_snapshots,transition transitions);


void displayDataGesture(dataGestures dataGestures);


#endif // GENERATESNAPSHOT_H
