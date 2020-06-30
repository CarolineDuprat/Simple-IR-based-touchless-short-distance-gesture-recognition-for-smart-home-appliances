#ifndef GESTURE_H
#define GESTURE_H
#include "structure.h"
/* This table defines the possible, valid snapshots given the number ofreceivers and shape.This example is for 4 receivers in a rectangle shape.
 * Assume we can combine receivers vertically, horizontally, or diagonally,but L-shapes are considered illegal. */
const snapshot_t all_snapshots[] = {
    /* Single individual receivers */
    {1, {1}}, /* 0 */
    {1, {2}}, /* 1 */
    {1, {4}}, /* 2 */
    {1, {8}}, /* 3 */
    /* Single combined receivers */
    {1, {3}}, /* 4 */
    {1, {5}}, /* 5 */
    {1, {6}}, /* 6 */
    {1, {9}}, /* 7 */
    {1, {10}}, /* 8 */
    {1, {12}}, /* 9 */
    /* Two receivers; receiver 0x01 and a second one. */
    /* Impossible combinations: 0x01 followed by 0x9, 0x3, 0x5 */
    {2, {1, 2}}, /* 10 */
    {2, {1, 4}}, /* 11 */
    {2, {1, 8}}, /* 12 */
    {2, {1, 6}}, /* 13 */
    {2, {1, 10}}, /* 14 */
    {2, {1, 12}}, /* 15 */
    /* Two receivers; receiver 0x02 and a second one. */
    /* Impossible combinations: 0x02 followed by 0x3, 0x6, 0xA */
    {2, {2, 1}}, /* 16 */
    {2, {2, 4}}, /* 17 */
    {2, {2, 8}}, /* 18 */
    {2, {2, 5}}, /* 19 */
    {2, {2, 9}}, /* 20 */
    {2, {2, 12}}, /* 21 */
    /* Two receivers; receiver 0x04 and a second one. */
    /* Impossible combinations: 0x04 followed by 0x5, 0x6, 0xC */
    {2, {4, 1}}, /* 22 */
    {2, {4, 2}}, /* 23 */
    {2, {4, 8}}, /* 24 */
    {2, {4, 3}}, /* 25 */
    {2, {4, 9}}, /* 26 */
    {2, {4, 10}}, /* 27 */
    /* Two receivers; receiver 0x08 and a second one. */
    /* Impossible combinations: 0x08 followed by 0x9, 0xA, 0xC */
    {2, {8, 1}}, /* 28 */
    {2, {8, 2}}, /* 29 */
    {2, {8, 4}}, /* 30 */
    {2, {8, 3}}, /* 31 */
    {2, {8, 5}}, /* 32 */
    {2, {8, 6}}, /* 33 */
    /* Two receivers; receiver 0x03 and a second one. */
    /* Possible combinations: 0x03 followed by 0x4, 0x8, or 0xC */
    {2, {3, 4}}, /* 34 */
    {2, {3, 8}}, /* 35 */
    {2, {3, 12}}, /* 36 */
    /* Two receivers; receiver 0x05 and a second one. */
    /* Possible combinations: 0x05 followed by 0x2 or 0x8 */
    {2, {5, 2}}, /* 37 */
    {2, {5, 8}}, /* 38 */
    /* Two receivers; receiver 0x06 and a second one. */
    /* Possible combinations: 0x06 followed by 0x1, 0x8, or 0x9 */
    {2, {6, 1}}, /* 39 */
    {2, {6, 8}}, /* 40 */
    {2, {6, 9}}, /* 41 */
    /* Two receivers; receiver 0x09 and a second one. */
    /* Possible combinations: 0x09 followed by 0x2, 0x4, or 0x6 */
    {2, {9, 2}}, /* 42 */
    {2, {9, 4}}, /* 43 */
    {2, {9, 6}}, /* 44 */
    /* Two receivers; receiver 0x0A and a second one. */
    /* Possible combinations: 0x0A followed by 0x1 or 0x4 */
    {2, {10, 1}}, /* 45 */
    {2, {10, 4}}, /* 46 */
    /* Two receivers; receiver 0x0C and a second one. */
    /* Possible combinations: 0x0C followed by 0x1, 0x2, or 0x3 */
    {2, {12, 1}}, /* 47 */
    {2, {12, 2}}, /* 48 */
    {2, {12, 3}}, /* 49 */
    /* Three receivers: Let's assume an L-shape is illegal, so the onlyvalid combinations of 3 receivers are diagonal:receiver, two receivers combined, and receiver */
    {3, {1, 10, 4}}, /* 50 */
    {3, {2, 5, 8}}, /* 51 */
    {3, {4, 10, 1}}, /* 52 */
    {3, {8, 5, 2}}, /* 53 */
    /* There are no valid snapshots of 4 receivers */
    /* Mark the end of the table with this special snapshot(0 receivers, receiver ID 0x00) */
    {0, {0}}, /* 54 */
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
    uint8_t gestureID;
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
};
// Pool of sparse matrix cells
// Each cell is the snapshot ID of the "to" transition and the bitwise-or of valid gesture IDs of the transition
// To simplify this example, let's assume only direct transitions in the above grpah are valid
// (not those in red)
const transitions_t transitions_pool = {
    // Valid transitions from snapshot {1,{0x00}} (entry [0] in all_snapshots array) begin here:
    // These are the black arcs in the image// >>>>>>> entries [0] to [7]
    // Transitions from all_snapshots[0] to all_snapshots[1] ({1,{0x00}} to {1,{0x01}}) belong to GESTURE_TB | GESTURE_RL | GESTURE_TRBL
    {1,GESTURE_TB | GESTURE_RL | GESTURE_TRBL},
    // Transitions from all_snapshots[0] to all_snapshots[2] ({1,{0x00}} to {1,{0x02}}) belong to GESTURE_BT | GESTURE_RL | GESTURE_BRTL
    {2,GESTURE_BT | GESTURE_RL | GESTURE_BRTL},
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
    // These are the green arcs in the image// >>>>>>> entries [8] to [12]
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
    // Transitions from ({1,{0x03}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR
    {2, GESTURE_TLBR},
    // Transitions from ({1,{0x03}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL
    {1, GESTURE_BRTL},
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
    {39, GESTURE_TLBR | GESTURE_TB},
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
    // Transitions from ({1,{0x09}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR
    {2, GESTURE_BLTR},
    // Transitions from ({1,{0x09}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL
    {4, GESTURE_BRTL},
    // Transitions from ({1,{0x09}} to {2,{0x09,0x02}}, index 43 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {43,GESTURE_TRBL | GESTURE_TB},
    // Transitions from ({1,{0x09}} to {2,{0x09,0x04}}, index 44 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {44, GESTURE_TLBR | GESTURE_TB},
    // Transitions from ({1,{0x09}} to {2,{0x09,0x06}}, index 45 in all_snapshots) belong to GESTURE_TB
    {45, GESTURE_TB},
    // All other possible transitions exiting from all_snapshots[8] are illegal (and do not appear here)
    // <<<<<<<
};

#endif // GESTURE_H