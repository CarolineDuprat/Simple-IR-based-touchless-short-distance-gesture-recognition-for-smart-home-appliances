#ifndef GENERATESNAPSHOT_H
#define GENERATESNAPSHOT_H
#include "structure.h"

uint16_t calculBinomialCoeff (uint16_t n,uint16_t k);
coefLine linearRelation (position A,position B);
uint8_t pointsAligned(position A,position B,position C);
uint8_t checkIfSnapshopInAllSnap (snapshot_t all_snapshots[],uint16_t numberSnapshot,snapshot_t newSnapshot);
infoSystem initSystem ();
void createAllSnap (infoSystem system);
#endif // GENERATESNAPSHOT_H
