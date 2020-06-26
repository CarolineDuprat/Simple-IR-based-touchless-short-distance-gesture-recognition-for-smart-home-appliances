#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_RECEIVERS 6

//Maximum number of characters per line
#define SIZE_MAX_CHARACTER MAX_RECEIVERS*20

#define MAX_TIME_MS 1000

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint64_t;

typedef struct {
    uint16_t id;
    uint16_t valid;
    uint16_t time;
} receiver_info_t;

typedef struct {
    receiver_info_t receivers[MAX_RECEIVERS];
} allreceivers_info_t;

typedef struct {
    uint16_t numberReceivers;
    uint16_t timeSimulationTotal;
    allreceivers_info_t t [MAX_TIME_MS];
} allreceivers_info;



typedef struct {
    uint16_t nreceivers;
    uint8_t receivers[MAX_RECEIVERS];
} snapshot_t;

typedef struct {
    uint16_t numberSnapshot;
    uint8_t snapshot_t[MAX_TIME_MS];
} snapshot;

#endif // STRUCTURE_H
