#ifndef SNAPSHOTANALYSIS_H
#define SNAPSHOTANALYSIS_H

#include "structure.h"
//#include "gesture.h"
//#include "snapshot.h"

uint16_t snapshotEqualAll_snapshots (const snapshot_t snapshot,uint16_t counter,snapshots all_snapshots);

uint16_t snapshotResearchAll_snapshots (const snapshot_t snapshot,snapshots all_snapshots);

uint16_t snapshotResearchTransitions_pool (const snapshot_t snapshot,uint16_t position,snapshots all_snapshots,transition transitions);

void snapshotsGestureName (char *lien,snapshots all_snapshots,transition transitions,infoSystem system);

int16_t gestureSearch(uint16_t idGesture,infoSystem system);

#endif // SNAPSHOTANALYSIS_H
