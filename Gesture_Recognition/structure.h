#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdlib.h>
#include <stdio.h>


#define NBRRECEIVERS 4

#define SIZE_MAX_CHARACTER NBRRECEIVERS*20


typedef unsigned char uint8_t;
typedef unsigned int uint16_t;
typedef unsigned long uint64_t;

typedef struct {
    uint8_t id;
    uint16_t valid;
    uint64_t time;
} receiver_info_t;

typedef struct {
    unsigned int nReceivers;
    receiver_info_t receivers[NBRRECEIVERS];
} allreceivers_info_t;


#endif // STRUCTURE_H
