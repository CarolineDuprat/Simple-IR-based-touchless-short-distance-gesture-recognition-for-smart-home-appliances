#ifndef SNAPSHOTANALYSIS_H
#define SNAPSHOTANALYSIS_H

#include "structure.h"
//#include "gesture.h"
//#include "snapshot.h"

uint16_t snapshotEqualAll_snapshots (const snapshot_t snapshot,uint16_t counter);
uint16_t snapshotResearchAll_snapshots (const snapshot_t snapshot);
uint16_t snapshotResearchTransitions_pool (const snapshot_t snapshot,uint16_t position);
void snapshotsGestureName (char *lien);
int16_t gestureSearch(uint16_t idGesture,uint16_t numberGesture);
#endif // SNAPSHOTANALYSIS_H
