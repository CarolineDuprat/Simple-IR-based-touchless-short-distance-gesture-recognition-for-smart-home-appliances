#ifndef GESTURE_H
#define GESTURE_H
#include "structure.h"
/* This table defines the possible, valid snapshots given the number ofreceivers and shape.This example is for 4 receivers in a rectangle shape.
 * Assume we can combine receivers vertically, horizontally, or diagonally,but L-shapes are considered illegal. */
const snapshot_t all_snapshots[] = {
    /* Single individual receivers */
    {1, {0x01}}, /* 0 */
    {1, {0x02}}, /* 1 */
    {1, {0x04}}, /* 2 */
    {1, {0x08}}, /* 3 */
    /* Single combined receivers */
    {1, {0x03}}, /* 4 */
    {1, {0x05}}, /* 5 */
    {1, {0x06}}, /* 6 */
    {1, {0x09}}, /* 7 */
    {1, {0x0A}}, /* 8 */
    {1, {0x0C}}, /* 9 */
    /* Two receivers; receiver 0x01 and a second one. */
    /* Impossible combinations: 0x01 followed by 0x9, 0x3, 0x5 */
    {2, {0x01, 0x02}}, /* 10 */
    {2, {0x01, 0x04}}, /* 11 */
    {2, {0x01, 0x08}}, /* 12 */
    {2, {0x01, 0x06}}, /* 13 */
    {2, {0x01, 0x0A}}, /* 14 */
    {2, {0x01, 0x0C}}, /* 15 */
    /* Two receivers; receiver 0x02 and a second one. */
    /* Impossible combinations: 0x02 followed by 0x3, 0x6, 0xA */
    {2, {0x02, 0x01}}, /* 16 */
    {2, {0x02, 0x04}}, /* 17 */
    {2, {0x02, 0x08}}, /* 18 */
    {2, {0x02, 0x05}}, /* 19 */
    {2, {0x02, 0x09}}, /* 20 */
    {2, {0x02, 0x0C}}, /* 21 */
    /* Two receivers; receiver 0x04 and a second one. */
    /* Impossible combinations: 0x04 followed by 0x5, 0x6, 0xC */
    {2, {0x04, 0x01}}, /* 22 */
    {2, {0x04, 0x02}}, /* 23 */
    {2, {0x04, 0x08}}, /* 24 */
    {2, {0x04, 0x03}}, /* 25 */
    {2, {0x04, 0x09}}, /* 26 */
    {2, {0x04, 0x0A}}, /* 27 */
    /* Two receivers; receiver 0x08 and a second one. */
    /* Impossible combinations: 0x08 followed by 0x9, 0xA, 0xC */
    {2, {0x08, 0x01}}, /* 28 */
    {2, {0x08, 0x02}}, /* 29 */
    {2, {0x08, 0x04}}, /* 30 */
    {2, {0x08, 0x03}}, /* 31 */
    {2, {0x08, 0x05}}, /* 32 */
    {2, {0x08, 0x06}}, /* 33 */
    /* Two receivers; receiver 0x03 and a second one. */
    /* Possible combinations: 0x03 followed by 0x4, 0x8, or 0xC */
    {2, {0x03, 0x04}}, /* 34 */
    {2, {0x03, 0x08}}, /* 35 */
    {2, {0x03, 0x0C}}, /* 36 */
    /* Two receivers; receiver 0x05 and a second one. */
    /* Possible combinations: 0x05 followed by 0x2 or 0x8 */
    {2, {0x05, 0x02}}, /* 37 */
    {2, {0x05, 0x08}}, /* 38 */
    /* Two receivers; receiver 0x06 and a second one. */
    /* Possible combinations: 0x06 followed by 0x1, 0x8, or 0x9 */
    {2, {0x06, 0x01}}, /* 39 */
    {2, {0x06, 0x08}}, /* 40 */
    {2, {0x06, 0x09}}, /* 41 */
    /* Two receivers; receiver 0x09 and a second one. */
    /* Possible combinations: 0x09 followed by 0x2, 0x4, or 0x6 */
    {2, {0x09, 0x02}}, /* 42 */
    {2, {0x09, 0x04}}, /* 43 */
    {2, {0x09, 0x06}}, /* 44 */
    /* Two receivers; receiver 0x0A and a second one. */
    /* Possible combinations: 0x0A followed by 0x1 or 0x4 */
    {2, {0x0A, 0x01}}, /* 45 */
    {2, {0x0A, 0x04}}, /* 46 */
    /* Two receivers; receiver 0x0C and a second one. */
    /* Possible combinations: 0x0C followed by 0x1, 0x2, or 0x3 */
    {2, {0x0C, 0x01}}, /* 47 */
    {2, {0x0C, 0x02}}, /* 48 */
    {2, {0x0C, 0x03}}, /* 49 */
    /* Three receivers: Let's assume an L-shape is illegal, so the onlyvalid combinations of 3 receivers are diagonal:receiver, two receivers combined, and receiver */
    {3, {0x01, 0x0A, 0x04}}, /* 50 */
    {3, {0x02, 0x05, 0x08}}, /* 51 */
    {3, {0x04, 0x0A ,0x01}}, /* 52 */
    {3, {0x08, 0x05, 0x02}}, /* 53 */
    /* There are no valid snapshots of 4 receivers */
    /* Mark the end of the table with this special snapshot(0 receivers, receiver ID 0x00) */
    {0, {0x00}}, /* 54 */
};

/* Gesture */
// T = TOP, B = BOTTOM, L = LEFT, R = RIGHT
#define GESTURE_TB 0x01 /* Vertical top to bottom */
#define GESTURE_BT 0x02 /* Vertical bottom to top */
#define GESTURE_LR 0x04 /* Horizontal left to right */
#define GESTURE_RL 0x08 /* Horizontal right to left */
#define GESTURE_TLBR 0x10 /* Diagonal top-left to bottom-right */
#define GESTURE_TRBL 0x20 /* Diagonal top-right to bottom-left */
#define GESTURE_BLTR 0x40 /* Diagonal bottom-left to top-right */
#define GESTURE_BRTL 0x80 /* Diagonal bottom-right to top-left */
#define GESTURE_ALL 0xff
#define GESTURE_NONE 0x00

typedef struct {
    unsigned int snapshotID;
    uint16_t gestureID;
} transitions_t;

const int transitions_rows[] = {
    // Transitions exiting from snaphost entry [0] in all_snapshots (snapshot {1, {0x00}}) use the entries [0] to [y-1] in the pool
    // y is the number of valid transitions exiting from this snapshot:
    // 8 direct transitions in the above graph -- all eight directions, black--, so y = 8 -> entries [0] to [7]
    0,
    // Transitions exiting from snaphost entry [1] in all_snapshots (snapshot {1, {0x01}}) use the entries [x] to [x+y-1] in the pool
    // x is the first available index from all previous transitions (8),
    // y is the number of valid transitions exiting from this snapshot: 5, green (one to RL, one to TB, 3 to TPBL)
    8,
    // Transitions exiting from snaphost entry [2] in all_snapshots (snapshot {1, {0x02}}) use the entries [x] to [x+y-1] in the pool
    // x is the first available index from all previous transitions (8+5 = 13),
    13,
    // y is the number of valid transitions exiting from this snapshot...
    // And so on...
    18,
    23,
    28,
    33,
    37,
    42,
    47,
    51,
    56,
    62,
};
// Pool of sparse matrix cells
// Each cell is the snapshot ID of the "to" transition and the bitwise-or of valid gesture IDs of the transition
// To simplify this example, let's assume only direct transitions in the above grpah are valid
// (not those in red)
const transitions_t transitions_pool = {

    // Valid transitions from snapshot {1,{0x00}} (entry [0] in all_snapshots array) begin here:
    // These are the black arcs in the image
    // >>>>>>> entries [0] to [7]

    // Transitions from all_snapshots[0] to all_snapshots[1] ({1,{0x00}} to {1,{0x01}}) belong to GESTURE_TB | GESTURE_RL | GESTURE_TRBL
    {1, GESTURE_TB | GESTURE_RL | GESTURE_TRBL},
    // Transitions from all_snapshots[0] to all_snapshots[2] ({1,{0x00}} to {1,{0x02}}) belong to GESTURE_BT | GESTURE_RL | GESTURE_BRTL
    {2, GESTURE_BT | GESTURE_RL | GESTURE_BRTL},
    // Transitions from all_snapshots[0] to all_snapshots[3] ({1,{0x00}} to {1,{0x04}}) belong to GESTURE_BT | GESTURE_LR | GESTURE_BLTR
    {3, GESTURE_BT | GESTURE_LR | GESTURE_BLTR},
    // Transitions from all_snapshots[0] to all_snapshots[4] ({1,{0x00}} to {1,{0x08}}) belong to GESTURE_TB | GESTURE_LR | GESTURE_TLBR
    {4, GESTURE_BT | GESTURE_LR | GESTURE_BLTR},
    // Transitions from all_snapshots[0] to all_snapshots[5] ({1,{0x00}} to {1,{0x03}}) belong to GESTURE_RL
    {5, GESTURE_RL},
    // Transitions from all_snapshots[0] to all_snapshots[7] ({1,{0x00}} to {1,{0x06}}) belong to GESTURE_BT
    {7, GESTURE_BT},
    // Transitions from all_snapshots[0] to all_snapshots[8] ({1,{0x00}} to {1,{0x09}}) belong to GESTURE_TB
    {8, GESTURE_TB},
    // Transitions from all_snapshots[0] to all_snapshots[10] ({1,{0x00}} to {1,{0x0C}}) belong to GESTURE_LR
    {10, GESTURE_LR},
    // All other possible transitions exiting from all_snapshots[0] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x01}} (entry [1] in all_snapshots array) begin here:
    // These are the green arcs in the image
    // >>>>>>> entries [8] to [12]

    // Transitions from ({1,{0x01}} to {1,{0x03}}, index 5 in all_snapshots) belong to GESTURE_RL
    {5, GESTURE_RL},
    // Transitions from ({1,{0x01}} to {1,{0x09}}, index 8 in all_snapshots) belong to GESTURE_TB
    {8, GESTURE_TB},
    // Transitions from ({1,{0x01}} to {2,{0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_TRBL
    {11, GESTURE_TRBL},
    // Transitions from ({1,{0x01}} to {2,{0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_TRBL
    {13, GESTURE_TRBL},
    // Transitions from ({1,{0x01}} to {2,{0x01, 0x0A}}, index 15 in all_snapshots) belong to GESTURE_TRBL
    {15, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[1] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x02}} (entry [2] in all_snapshots array) begin here:
    // >>>>>>> entries [13] to [17]

    // Transitions from ({1,{0x02}} to {1,{0x03}}, index 5 in all_snapshots) belong to GESTURE_RL
    {5, GESTURE_RL},
    // Transitions from ({1,{0x02}} to {1,{0x06}}, index 7 in all_snapshots) belong to GESTURE_BT
    {7, GESTURE_BT},
    // Transitions from ({1,{0x02}} to {2,{0x02, 0x01}}, index 17 in all_snapshots) belong to GESTURE_BRTL
    {17, GESTURE_BRTL},
    // Transitions from ({1,{0x02}} to {2,{0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_BRTL
    {18, GESTURE_BRTL},
    // Transitions from ({1,{0x02}} to {2,{0x02, 0x05}}, index 20 in all_snapshots) belong to GESTURE_BRTL
    {20, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[2] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x04}} (entry [3] in all_snapshots array) begin here:
    // >>>>>>> entries [18] to [22]

    // Transitions from ({1,{0x04}} to {1,{0x06}}, index 7 in all_snapshots) belong to GESTURE_BT
    {7, GESTURE_BT},
    // Transitions from ({1,{0x04}} to {1,{0x0C}}, index 10 in all_snapshots) belong to GESTURE_LR
    {10, GESTURE_LR},
    // Transitions from ({1,{0x04}} to {2,{0x04, 0x02}}, index 24 in all_snapshots) belong to GESTURE_BLTR
    {24, GESTURE_BLTR},
    // Transitions from ({1,{0x04}} to {2,{0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_BLTR
    {25, GESTURE_BLTR},
    // Transitions from ({1,{0x04}} to {2,{0x04, 0x0A}}, index 28 in all_snapshots) belong to GESTURE_BLTR
    {28, GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[3] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x08}} (entry [4] in all_snapshots array) begin here:
    // >>>>>>> entries [23] to [27]

    // Transitions from ({1,{0x08}} to {1,{0x09}}, index 8 in all_snapshots) belong to GESTURE_TB
    {8, GESTURE_TB},
    // Transitions from ({1,{0x08}} to {1,{0x0C}}, index 10 in all_snapshots) belong to GESTURE_LR
    {10, GESTURE_LR},
    // Transitions from ({1,{0x08}} to {2,{0x08, 0x01}}, index 29 in all_snapshots) belong to GESTURE_TLBR
    {9, GESTURE_TLBR},
    // Transitions from ({1,{0x08}} to {2,{0x08, 0x04}}, index 31 in all_snapshots) belong to GESTURE_TLBR
    {31, GESTURE_TLBR},
    // Transitions from ({1,{0x08}} to {2,{0x08, 0x05}}, index 33 in all_snapshots) belong to GESTURE_TLBR
    {33, GESTURE_TLBR},
    // All other possible transitions exiting from all_snapshots[4] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x03}} (entry [5] in all_snapshots array) begin here:
    // >>>>>>> entries [28] to [32]

    // Transitions from ({1,{0x03}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {2, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from ({1,{0x03}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {1, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from ({1,{0x03}} to {2,{0x03,0x04}}, index 35 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {35, GESTURE_BRTL | GESTURE_RL},
    // Transitions from ({1,{0x03}} to {2,{0x03,0x08}}, index 36 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {36, GESTURE_TRBL | GESTURE_RL},
    // Transitions from ({1,{0x03}} to {2,{0x03,0x0C}}, index 37 in all_snapshots) belong to GESTURE_RL
    {37, GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[5] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x05}} (entry [6] in all_snapshots array) begin here:
    // >>>>>>> entries [33] to [36]

    // Transitions from ({1,{0x05}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {1, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from ({1,{0x05}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {3, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from ({1,{0x05}} to {2,{0x05,0x02}}, index 38 in all_snapshots) belong to GESTURE_TLBR
    {38,GESTURE_TLBR},
    // Transitions from ({1,{0x05}} to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[6] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x06}} (entry [7] in all_snapshots array) begin here:
    // >>>>>>> entries [37] to [41]

    // Transitions from ({1,{0x06}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL | GESTURE_BT | GESTURE_BRTL
    {3, GESTURE_TB | GESTURE_TRBL | GESTURE_BT | GESTURE_BRTL},
    // Transitions from ({1,{0x06}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TB | GESTURE_TLBR | GESTURE_BT | GESTURE_BLTR
    {2, GESTURE_TB | GESTURE_TLBR | GESTURE_BT | GESTURE_BLTR},
    // Transitions from ({1,{0x06}} to {2,{0x06,0x01}}, index 40 in all_snapshots) belong to GESTURE_BT | GESTURE_BRTL
    {40,GESTURE_BT | GESTURE_BRTL },
    // Transitions from ({1,{0x06}} to {2,{0x06,0x08}}, index 41 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {41, GESTURE_BT | GESTURE_BLTR},
    // Transitions from ({1,{0x06}} to {2,{0x06,0x09}}, index 42 in all_snapshots) belong to GESTURE_BT
    {42, GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[7] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x09}} (entry [8] in all_snapshots array) begin here:
    // >>>>>>> entries [42] to [46]

    // Transitions from ({1,{0x09}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR
    {2, GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR},
    // Transitions from ({1,{0x09}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL},
    // Transitions from ({1,{0x09}} to {2,{0x09,0x02}}, index 43 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {43,GESTURE_TRBL | GESTURE_TB},
    // Transitions from ({1,{0x09}} to {2,{0x09,0x04}}, index 44 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {44, GESTURE_TLBR | GESTURE_TB},
    // Transitions from ({1,{0x09}} to {2,{0x09,0x06}}, index 45 in all_snapshots) belong to GESTURE_TB
    {45, GESTURE_TB},
    // All other possible transitions exiting from all_snapshots[8] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x0A}} (entry [9] in all_snapshots array) begin here:
    // >>>>>>> entries [47] to [50]

    // Transitions from ({1,{0x0A}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL
    {4, GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from ({1,{0x0A}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL
    {2, GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from ({1,{0x0A}} to {2,{0x0A,0x01}}, index 46 in all_snapshots) belong to GESTURE_BLTR
    {46,GESTURE_BLTR},
    // Transitions from ({1,{0x0A}} to {2,{0x0A,0x04}}, index 47 in all_snapshots) belong to GESTURE_TRBL
    {47, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[9] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x0C}} (entry [10] in all_snapshots array) begin here:
    // >>>>>>> entries [51] to [55]

    // Transitions from ({1,{0x0C}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {3, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from ({1,{0x0C}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from ({1,{0x0C}} to {2,{0x0C,0x01}}, index 48 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {48, GESTURE_TLBR | GESTURE_LR},
    // Transitions from ({1,{0x0C}} to {2,{0x0C,0x02}}, index 49 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {49, GESTURE_BLTR | GESTURE_LR},
    // Transitions from ({1,{0x0C}} to {2,{0x0C,0x03}}, index 50 in all_snapshots) belong to GESTURE_LR
    {50, GESTURE_LR},
    // All other possible transitions exiting from all_snapshots[10] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x02}}  (entry [11] in all_snapshots array) begin here:
    // >>>>>>> entries [56] to [61]

    // Transitions from {2, {0x01, 0x02}}  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {2, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x01, 0x02}}  to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {1, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x01, 0x02}}  to {2, {0x01, 0x0A}, index 15 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {15, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x01, 0x02}}  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {20, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x01, 0x02}}  to {2,{0x01,0x0C}}, index 16 in all_snapshots) belong to GESTURE_BRTL
    {16, GESTURE_BRTL},
    // Transitions from {2, {0x01, 0x02}}  to {2,{0x02,0x0C}}, index 22 in all_snapshots) belong to GESTURE_TRBL
    {22, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[11] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x04}}  (entry [12] in all_snapshots array) begin here:
    // >>>>>>> entries [62] to [67]

    // Transitions from {2, {0x01, 0x04}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {1, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x01, 0x04}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {3, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x01, 0x04}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {18,GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x01, 0x04}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL },
    // Transitions from {2, {0x01, 0x04}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x01, 0x04}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[12] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x08}},   (entry [13] in all_snapshots array) begin here:
    // >>>>>>> entries [68] to [73]

    // Transitions from {2, {0x01, 0x08}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR
    {1, GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR},
    // Transitions from {2, {0x01, 0x08}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x01,0x0A}}, index 15 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {15,GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {39, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x01,0x06}}, index 14 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {14, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x06,0x08}}, index 41 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {41, GESTURE_TRBL | GESTURE_TB},
    // All other possible transitions exiting from all_snapshots[13] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x06}},    (entry [14] in all_snapshots array) begin here:
    // >>>>>>> entries [74] to [77]

    // Transitions from {2, {0x01, 0x06}} to {1, {0x06}}, index 7 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {7, GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x01, 0x06}} to {1, {0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL| GESTURE_BT
    {1, GESTURE_BRTL| GESTURE_BT },
    // Transitions from {2, {0x01, 0x06}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x01, 0x06}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL | GESTURE_BT
    {12, GESTURE_BRTL | GESTURE_RL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[14] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x0A}},    (entry [15] in all_snapshots array) begin here:
    // >>>>>>> entries [78] to [83]

    // Transitions from {2, {0x01, 0x0A}} to {1, {0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR
    {1, GESTURE_BLTR },
    // Transitions from {2, {0x01, 0x0A}} to {1, {0x0A}}, index 9 in all_snapshots) belong to GESTURE_TRBL
    {9, GESTURE_TRBL},
    // Transitions from {2, {0x01, 0x0A}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x01, 0x0A}} to {2, {0x01, 0x08}}}, index 13 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {13, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x01, 0x0A}} to {3, {0x01, 0x0A, 0x04}}, index 51 in all_snapshots) belong to GESTURE_TRBL
    {51, GESTURE_TRBL},
    // Transitions from {2, {0x01, 0x0A}} to {2, {0x0A, 0x04}}, index 47 in all_snapshots) belong to GESTURE_TRBL
    {47, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[15] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x0C}},    (entry [16] in all_snapshots array) begin here:
    // >>>>>>> entries [84] to [87]

    // Transitions from {2, {0x01, 0x0C}} to {1, {0x01}}, index 1 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {1, GESTURE_TLBR | GESTURE_LR },
    // Transitions from {2, {0x01, 0x0C}} to {1, {0x0C}}, index 10 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {10, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x01, 0x0C}} to {2, {0x01, 0x08}}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x01, 0x0C}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_TLBR
    {12, GESTURE_TLBR},
    // All other possible transitions exiting from all_snapshots[16] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x01}},    (entry [17] in all_snapshots array) begin here:
    // >>>>>>> entries [88] to [93]

    // Transitions from {2, {0x02, 0x01}},  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {2, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x02, 0x01}},  to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {1, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x02, 0x01}},  to {2, {0x01, 0x0A}, index 15 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {15, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x02, 0x01}},  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {20, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x02, 0x01}},  to {2,{0x01,0x0C}}, index 16 in all_snapshots) belong to GESTURE_BRTL
    {16, GESTURE_BRTL},
    // Transitions from {2, {0x02, 0x01}},  to {2,{0x02,0x0C}}, index 22 in all_snapshots) belong to GESTURE_TRBL
    {22, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[17] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x04}},    (entry [18] in all_snapshots array) begin here:
    // >>>>>>> entries [94] to [99]

    // Transitions from {2, {0x02, 0x04}},  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR
    {2, GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR},
    // Transitions from {2, {0x02, 0x04}},  to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT
    {3, GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {20,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x0A,0x04}}, index 47 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {47, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x09,0x02}}, index 43 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {43, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x09,0x04}}, index 44 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {44, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[18] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x08}},  (entry [19] in all_snapshots array) begin here:
    // >>>>>>> entries [100] to [105]

    // Transitions from {2, {0x02, 0x08}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from {2, {0x02, 0x08}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR
    {2, GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {13, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {18, GESTURE_TRBL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[19] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x05}},     (entry [20] in all_snapshots array) begin here:
    // >>>>>>> entries [106] to [111]

    // Transitions from {2, {0x02, 0x05}} to {1,{0x05}}, index 6 in all_snapshots) belong to GESTURE_BRTL
    {6, GESTURE_BRTL},
    // Transitions from {2, {0x02, 0x05}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR
    {2, GESTURE_TLBR},
    // Transitions from {2, {0x02, 0x05}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {18, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x02, 0x05}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x02, 0x05}} to {3,{0x02,0x05,0x08}}, index 52 in all_snapshots) belong to GESTURE_BRTL
    {52, GESTURE_BRTL},
    // Transitions from {2, {0x02, 0x05}} to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[20] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x09}},    (entry [21] in all_snapshots array) begin here:
    // >>>>>>> entries [112] to [115]

    // Transitions from {2, {0x02, 0x09}} to {1, {0x02}}, index 2 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {2, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x02, 0x09}} to {1, {0x09}}, index 8 in all_snapshots) belong to GESTURE_BLTR| GESTURE_BT
    {8,GESTURE_BLTR| GESTURE_BT },
    // Transitions from {2, {0x02, 0x09}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x02, 0x09}} to {2, {0x02, 0x08}}}, index 19 in all_snapshots) belong to GESTURE_TRBL
    {19, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[21] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x0C}},    (entry [22] in all_snapshots array) begin here:
    // >>>>>>> entries [116] to [119]

    // Transitions from {2, {0x02, 0x0C}} to {1, {0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {2, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x02, 0x0C}} to {1, {0x0C}}, index 10 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {10,GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x02, 0x0C}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x02, 0x0C}} to {2, {0x02, 0x08}}}, index 19 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {19, GESTURE_BLTR | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[22] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x01}},   (entry [23] in all_snapshots array) begin here:
    // >>>>>>> entries [120] to [125]

    // Transitions from {2, {0x04, 0x01}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {1, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x04, 0x01}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {3, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x04, 0x01}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {18,GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x04, 0x01}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL },
    // Transitions from {2, {0x04, 0x01}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x01}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[23] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x02}},    (entry [24] in all_snapshots array) begin here:
    // >>>>>>> entries [126] to [131]

    // Transitions from {2, {0x04, 0x02}}  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR
    {2, GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR},
    // Transitions from {2, {0x04, 0x02}}  to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT
    {3, GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}},  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {20,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}}  to {2,{0x0A,0x04}}, index 47 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {47, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}}  to {2,{0x09,0x02}}, index 43 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {43, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}}  to {2,{0x09,0x04}}, index 44 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {44, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[24] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x08}},     (entry [25] in all_snapshots array) begin here:
    // >>>>>>> entries [132] to [137]

    // Transitions from {2, {0x04, 0x08}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {3, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2, {0x0A, 0x04}, index 47 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {47, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {39, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2,{0x09,0x04}}, index 44 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {44, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2,{0x06,0x08}}, index 41 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {41, GESTURE_BLTR | GESTURE_LR},
    // All other possible transitions exiting from all_snapshots[25] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x03}},   (entry [26] in all_snapshots array) begin here:
    // >>>>>>> entries [138] to [141]

    // Transitions from {2, {0x04, 0x03}} to {1, {0x04}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {2, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x03}} to {1, {0x03}}, index 10 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {10,GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x04, 0x03}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x04, 0x03}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_BRTL
    {12, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[26] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x09}},   (entry [27] in all_snapshots array) begin here:
    // >>>>>>> entries [142] to [145]

    // Transitions from {2, {0x04, 0x09}} to {1, {0x04}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {2, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x04, 0x09}} to {1, {0x09}}, index 8 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {8,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x04, 0x09}} to {2, {0x01, 0x04}}, index 12 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {12, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x04, 0x09}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[27] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x0A}},   (entry [28] in all_snapshots array) begin here:
    // >>>>>>> entries [146] to [151]

    // Transitions from {2, {0x04, 0x0A}} to {1, {0x04}}, index 3 in all_snapshots) belong to GESTURE_TRBL
    {3, GESTURE_TRBL },
    // Transitions from {2, {0x04, 0x0A}} to {1, {0x0A}}, index 9 in all_snapshots) belong to GESTURE_BLTR
    {9, GESTURE_BLTR},
    // Transitions from {2, {0x04, 0x0A}} to {2, {0x02, 0x04}}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x04, 0x0A}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_TRBL  | GESTURE_RL
    {25, GESTURE_TRBL  | GESTURE_RL},
    // Transitions from {2, {0x04, 0x0A}} to {3, {0x01, 0x0A, 0x04}}, index 51 in all_snapshots) belong to GESTURE_BLTR
    {51, GESTURE_BLTR},
    // Transitions from {2, {0x04, 0x0A}} to {2, {0x01, 0x0A}}, index 15 in all_snapshots) belong to GESTURE_BLTR
    {47, GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[28] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x01}},   (entry [29] in all_snapshots array) begin here:
    // >>>>>>> entries [152] to [157]

    // Transitions from {2, {0x08, 0x01}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR
    {2, GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x01}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL},
    // Transitions from {2, {0x08, 0x01}} to {2,{0x01,0x0A}}, index 15 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {15,GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x08, 0x01}} to {2,{0x08,0x05}}, index 33 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {33, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x08, 0x01}} to {2,{0x01,0x06}}, index 14 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {14, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x08, 0x01}} to {2,{0x08,0x06}}, index 34 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {34, GESTURE_TRBL | GESTURE_TB},
    // All other possible transitions exiting from all_snapshots[29] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x02}},   (entry [30] in all_snapshots array) begin here:
    // >>>>>>> entries [158] to [163]

    // Transitions from {2, {0x08, 0x02}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from {2, {0x08, 0x02}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR
    {2, GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {13, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {18, GESTURE_TRBL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[30] are illegal (and do not appear here)
    // <<<<<<<
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x04}},    (entry [31] in all_snapshots array) begin here:
    // >>>>>>> entries [164] to [169]

    // Transitions from {2, {0x08, 0x04}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {3, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2, {0x0A, 0x04}, index 47 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {47, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {39, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2,{0x09,0x04}}, index 44 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {44, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2,{0x06,0x08}}, index 41 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {41, GESTURE_BLTR | GESTURE_LR},
    // All other possible transitions exiting from all_snapshots[31] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x03}},    (entry [32] in all_snapshots array) begin here:
    // >>>>>>> entries [170] to [173]

    // Transitions from {2, {0x08, 0x03}} to {1, {0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {4,GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x08, 0x03}} to {1, {0x03}}, index 10 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {10,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x03}} to {2, {0x02, 0x08}}, index 19 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {19, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x08, 0x03}} to {2, {0x01, 0x08}}}, index 13 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {13, GESTURE_BT | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[32] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x05}},    (entry [33] in all_snapshots array) begin here:
    // >>>>>>> entries [174] to [179]

    // Transitions from {2, {0x08, 0x05}} to {1,{0x05}}, index 6 in all_snapshots) belong to GESTURE_TLBR
    {6, GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x05}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL
    {4, GESTURE_BRTL},
    // Transitions from {2, {0x08, 0x05}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x08, 0x05}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x08, 0x05}} to {3,{0x02,0x05,0x08}}, index 52 in all_snapshots) belong to GESTURE_TLBR
    {52, GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x05}} to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_TLBR
    {39, GESTURE_TLBR},
    // All other possible transitions exiting from all_snapshots[33] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x06}},   (entry [34] in all_snapshots array) begin here:
    // >>>>>>> entries [180] to []

    // Valid transitions from snapshot {2, {0x03, 0x04}},    (entry [35] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x03, 0x04}} to {1, {0x04}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {2, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x03, 0x04}} to {1, {0x03}}, index 10 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {10,GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x03, 0x04}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x03, 0x04}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_BRTL
    {12, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[35] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x03, 0x08}},   (entry [36] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x03, 0x08}} to {1, {0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {4,GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x03, 0x08}} to {1, {0x03}}, index 10 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {10,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x03, 0x08}} to {2, {0x02, 0x08}}, index 19 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {19, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x03, 0x08}} to {2, {0x01, 0x08}}}, index 13 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {13, GESTURE_BT | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[36] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x03, 0x0C}},   (entry [37] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {2, {0x05, 0x02}},   (entry [38] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x05, 0x02}} to {1,{0x05}}, index 6 in all_snapshots) belong to GESTURE_BRTL
    {6, GESTURE_BRTL},
    // Transitions from {2, {0x05, 0x02}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR
    {2, GESTURE_TLBR},
    // Transitions from {2, {0x05, 0x02}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {18, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x05, 0x02}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x05, 0x02}} to {3,{0x02,0x05,0x08}}, index 52 in all_snapshots) belong to GESTURE_BRTL
    {52, GESTURE_BRTL},
    // Transitions from {2, {0x05, 0x02}} to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[20] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x05, 0x08}},  (entry [39] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x05, 0x08}} to {1,{0x05}}, index 6 in all_snapshots) belong to GESTURE_TLBR
    {6, GESTURE_TLBR},
    // Transitions from {2, {0x05, 0x08}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL
    {4, GESTURE_BRTL},
    // Transitions from {2, {0x05, 0x08}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x05, 0x08}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x05, 0x08}} to {3,{0x02,0x05,0x08}}, index 52 in all_snapshots) belong to GESTURE_TLBR
    {52, GESTURE_TLBR},
    // Transitions from {2, {0x05, 0x08}} to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_TLBR
    {39, GESTURE_TLBR},
    // All other possible transitions exiting from all_snapshots[39] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x06, 0x01}},    (entry [40] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x06, 0x01}} to {1, {0x06}}, index 7 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {7, GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x06, 0x01}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x06, 0x01}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL | GESTURE_BT
    {12, GESTURE_BRTL | GESTURE_RL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[40] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x06, 0x08}},   (entry [41] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {2, {0x06, 0x09}},    (entry [42] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {2, {0x09, 0x02}},   (entry [43] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x09, 0x02}} to {1, {0x02}}, index 2 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {2, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x09, 0x02}} to {1, {0x09}}, index 8 in all_snapshots) belong to GESTURE_BLTR| GESTURE_BT
    {8,GESTURE_BLTR| GESTURE_BT },
    // Transitions from {2, {0x09, 0x02}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x09, 0x02}} to {2, {0x02, 0x08}}}, index 19 in all_snapshots) belong to GESTURE_TRBL
    {19, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[14] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x09, 0x04}},    (entry [44] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x09, 0x04}} to {1, {0x04}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {2, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x09, 0x04}} to {1, {0x09}}, index 8 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {8,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x09, 0x04}} to {2, {0x01, 0x04}}, index 12 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {12, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x09, 0x04}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[44] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x09, 0x06}},   (entry [45] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {2, {0x0A, 0x01}},    (entry [46] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x0A, 0x01}} to {1, {0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR
    {1, GESTURE_BLTR },
    // Transitions from {2, {0x0A, 0x01}} to {1, {0x0A}}, index 9 in all_snapshots) belong to GESTURE_TRBL
    {9, GESTURE_TRBL},
    // Transitions from {2, {0x0A, 0x01}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x0A, 0x01}} to {2, {0x01, 0x08}}}, index 13 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {13, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x0A, 0x01}} to {3, {0x01, 0x0A, 0x04}}, index 51 in all_snapshots) belong to GESTURE_TRBL
    {51, GESTURE_TRBL},
    // Transitions from {2, {0x0A, 0x01}} to {2, {0x0A, 0x04}}, index 47 in all_snapshots) belong to GESTURE_TRBL
    {47, GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[46] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x0A, 0x04}},   (entry [47] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x0A, 0x04}} to {1, {0x04}}, index 3 in all_snapshots) belong to GESTURE_TRBL
    {3, GESTURE_TRBL },
    // Transitions from {2, {0x0A, 0x04}} to {1, {0x0A}}, index 9 in all_snapshots) belong to GESTURE_BLTR
    {9, GESTURE_BLTR},
    // Transitions from {2, {0x0A, 0x04}} to {2, {0x02, 0x04}}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x0A, 0x04}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_TRBL  | GESTURE_RL
    {25, GESTURE_TRBL  | GESTURE_RL},
    // Transitions from {2, {0x0A, 0x04}} to {3, {0x01, 0x0A, 0x04}}, index 51 in all_snapshots) belong to GESTURE_BLTR
    {51, GESTURE_BLTR},
    // Transitions from {2, {0x0A, 0x04}} to {2, {0x01, 0x0A}}, index 15 in all_snapshots) belong to GESTURE_BLTR
    {47, GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[47] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x0C, 0x01}},     (entry [48] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x0C, 0x01}} to {1, {0x01}}, index 1 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {1, GESTURE_TLBR | GESTURE_LR },
    // Transitions from {2, {0x0C, 0x01}} to {1, {0x0C}}, index 10 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {10, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x0C, 0x01}} to {2, {0x01, 0x08}}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x0C, 0x01}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_TLBR
    {12, GESTURE_TLBR},
    // All other possible transitions exiting from all_snapshots[48] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x0C, 0x02}},    (entry [49] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Transitions from {2, {0x0C, 0x02}} to {1, {0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {2, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x0C, 0x02}} to {1, {0x0C}}, index 10 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {10,GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x0C, 0x02}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x0C, 0x02}} to {2, {0x02, 0x08}}}, index 19 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {19, GESTURE_BLTR | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[49] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x0C, 0x03}},    (entry [50] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {3, {0x01, 0x0A, 0x04}},    (entry [51] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {3, {0x02, 0x05, 0x08}},   (entry [52] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {3, {0x04, 0x0A, 0x01}},     (entry [53] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []

    // Valid transitions from snapshot {3, {0x08, 0x05, 0x02}},   (entry [54] in all_snapshots array) begin here:
    // >>>>>>> entries [] to []


};

#endif // GESTURE_H
