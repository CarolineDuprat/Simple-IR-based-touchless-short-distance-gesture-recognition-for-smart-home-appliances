#ifndef SIMULATIONRECEIVER_H
#define SIMULATIONRECEIVER_H
#include "structure.h"
#define PI 3.141592

uint16_t simulationTime (uint16_t distance,uint16_t speed);

returnSpeedPos HorizontalAndVerticalSpeed (double distance,double speed,double angle);

position positionMoveObject (returnSpeedPos information ,uint16_t time);

corner rotationCorner (dimension dimensionObject,uint16_t angle);

uint8_t ReceiverCovered (position positionReceiver,corner positionCorner);

corner ReelPositionCorner (position positionObject,corner positionCornerRotation);

int16_t signdet (position positionCorner1,position positionCorner2,position positionReceiver);

coef linearRelation (uint16_t direction);

uint16_t distanceMaxReceiverLinearRelationTab (uint16_t direction,infoSystem positionReceiver);

#endif // SIMULATIONRECEIVER_H
