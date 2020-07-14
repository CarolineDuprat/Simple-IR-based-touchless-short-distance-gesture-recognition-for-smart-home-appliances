#ifndef SNAPSHOTANALYSIS_H
#define SNAPSHOTANALYSIS_H

#include "structure.h"
//#include "gesture.h"
//#include "snapshot.h"

uint16_t snapshotEqualAll_snapshots (const snapshot_t snapshot,uint16_t counter);
uint16_t snapshotResearchAll_snapshots (const snapshot_t snapshot);
uint16_t snapshotResearchTransitions_pool (const snapshot_t snapshot,uint16_t position);
uint16_t snapshotsGesture (snapshot snapshots);
void nameGesture (uint16_t gestureID );

#endif // SNAPSHOTANALYSIS_H
