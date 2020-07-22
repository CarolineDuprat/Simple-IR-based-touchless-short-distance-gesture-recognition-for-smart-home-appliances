#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define MAX_RECEIVERS 10
#define MAX_GESTURE 10

//Maximum number of characters per line
#define SIZE_MAX_CHARACTER MAX_RECEIVERS*20

#define MAX_TIME_MS 1000

typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef signed int int16_t;
typedef unsigned long uint64_t;


/* Receivers */
typedef struct {
    uint16_t id;
    uint16_t valid;
    uint16_t time;
} receiver_info_t;

typedef struct {
    uint16_t numberReceivers;
    receiver_info_t receivers[MAX_RECEIVERS];
} allreceivers_info_t;

/* Snapshot */
typedef struct {
    uint16_t nreceivers;
    uint16_t receivers[MAX_RECEIVERS];
} snapshot_t;

typedef struct {
    uint16_t nreceivers;
    uint16_t receivers[MAX_RECEIVERS];
    uint16_t time[MAX_RECEIVERS];
} snapshot_t_time;


typedef struct {
    FILE* file;
    uint16_t numberSnapshot;
} infoFile;

typedef struct {
    double x;
    double y;
    uint16_t id;
} position;

typedef struct {
    uint16_t numberReceivers;
    position pos[MAX_RECEIVERS];
    uint16_t numberGesture;
    uint16_t gesture[MAX_GESTURE];
} infoSystem;

#endif // STRUCTURE_H
