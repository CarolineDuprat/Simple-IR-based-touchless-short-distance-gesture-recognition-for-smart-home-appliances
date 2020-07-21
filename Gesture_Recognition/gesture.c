#include "gesture.h"




const uint16_t transitions_rows[] = {
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
    18,23,28,33,41,46,51,59,64,70,76,82,86,92,96,102,108,114,120,124,128,134,140,146,150,154,160,166,172,178,182,188,192,196,200,
    206,212,218,221,225,231,235,239,245,251,257,261,265,271,277,283,290,296,

};

// Pool of sparse matrix cells
// Each cell is the snapshot ID of the "to" transition and the bitwise-or of valid gesture IDs of the transition
// To simplify this example, let's assume only direct transitions in the above grpah are valid
// (not those in red)
const transitions_t transitions_pool[] = {

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
    {4, GESTURE_TB | GESTURE_LR | GESTURE_TLBR},
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
    // Transitions from ({1,{0x01}} to {2,{0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {11, GESTURE_TRBL| GESTURE_RL},
    // Transitions from ({1,{0x01}} to {2,{0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {13, GESTURE_TRBL| GESTURE_TB},
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
    // Transitions from ({1,{0x02}} to {2,{0x02, 0x01}}, index 17 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {17, GESTURE_BRTL| GESTURE_RL},
    // Transitions from ({1,{0x02}} to {2,{0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {18, GESTURE_BRTL| GESTURE_BT},
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
    // Transitions from ({1,{0x04}} to {2,{0x04, 0x02}}, index 24 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {24, GESTURE_BLTR | GESTURE_BT},
    // Transitions from ({1,{0x04}} to {2,{0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {25, GESTURE_BLTR | GESTURE_LR},
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
    // Transitions from ({1,{0x08}} to {2,{0x08, 0x01}}, index 29 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {29, GESTURE_TLBR | GESTURE_TB},
    // Transitions from ({1,{0x08}} to {2,{0x08, 0x04}}, index 31 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {31, GESTURE_TLBR | GESTURE_LR},
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
    // >>>>>>> entries [33] to [40]

    // Transitions from ({1,{0x05}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {1, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from ({1,{0x05}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {3, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from ({1,{0x05}} to {2,{0x05,0x02}}, index 38 in all_snapshots) belong to GESTURE_TLBR
    {38,GESTURE_TLBR},
    // Transitions from ({1,{0x05}} to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // Transitions from ({1,{0x05}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11,GESTURE_TLBR| GESTURE_LR },
    // Transitions from ({1,{0x05}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // Transitions from ({1,{0x05}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TLBR  | GESTURE_TB
    {18,GESTURE_TLBR| GESTURE_TB},
    // Transitions from ({1,{0x05}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL| GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[6] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x06}} (entry [7] in all_snapshots array) begin here:
    // >>>>>>> entries [41] to [45]

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
    // >>>>>>> entries [46] to [50]

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
    // >>>>>>> entries [51] to [58]

    // Transitions from ({1,{0x0A}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL
    {4, GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from ({1,{0x0A}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL
    {2, GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from ({1,{0x0A}} to {2,{0x0A,0x01}}, index 46 in all_snapshots) belong to GESTURE_BLTR
    {15,GESTURE_BLTR},
    // Transitions from ({1,{0x0A}} to {2,{0x0A,0x04}}, index 47 in all_snapshots) belong to GESTURE_TRBL
    {47, GESTURE_TRBL},
    // Transitions from ({1,{0x0A}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {11,GESTURE_BLTR | GESTURE_LR},
    // Transitions from ({1,{0x0A}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from ({1,{0x0A}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {13,GESTURE_BLTR | GESTURE_BT},
    // Transitions from ({1,{0x0A}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {25, GESTURE_TRBL  | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[9] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {1,{0x0C}} (entry [10] in all_snapshots array) begin here:
    // >>>>>>> entries [59] to [63]

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
    // >>>>>>> entries [64] to [69]

    // Transitions from {2, {0x01, 0x02}}  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {2, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x01, 0x02}}  to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {1, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x01, 0x02}}  to {2, {0x01, 0x0A}, index 15 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {15, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x01, 0x02}}  to {2,{0x05,0x02}}, index 38 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {38, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x01, 0x02}}  to {2,{0x01,0x0C}}, index 16 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {16, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x01, 0x02}}  to {2,{0x02,0x0C}}, index 22 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {22, GESTURE_TRBL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[11] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x04}}  (entry [12] in all_snapshots array) begin here:
    // >>>>>>> entries [70] to [75]

    // Transitions from {2, {0x01, 0x04}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {1, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x01, 0x04}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {3, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x01, 0x04}} to {2,{0x04,0x02}}, index 24 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {24,GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x01, 0x04}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL },
    // Transitions from {2, {0x01, 0x04}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x01, 0x04}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[12] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x08}},   (entry [13] in all_snapshots array) begin here:
    // >>>>>>> entries [76] to [81]

    // Transitions from {2, {0x01, 0x08}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR
    {1, GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR},
    // Transitions from {2, {0x01, 0x08}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_TB | GESTURE_BT | GESTURE_TRBL},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x01,0x0A}}, index 15 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {15,GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x08,0x05}}, index 33 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {33, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x01,0x06}}, index 14 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {14, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x01, 0x08}} to {2,{0x08,0x06}}, index 34 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {34, GESTURE_TRBL | GESTURE_TB},
    // All other possible transitions exiting from all_snapshots[13] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x01, 0x06}},    (entry [14] in all_snapshots array) begin here:
    // >>>>>>> entries [82] to [85]

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
    // >>>>>>> entries [86] to [91]

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
    // >>>>>>> entries [92] to [95]

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
    // >>>>>>> entries [96] to [101]

    // Transitions from {2, {0x02, 0x01}}  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {2, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x02, 0x01}}  to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {1, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x02, 0x01}}  to {2, {0x01, 0x0A}, index 15 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {15, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x02, 0x01}}  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {20, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x02, 0x01}}  to {2,{0x01,0x0C}}, index 16 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {16, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x02, 0x01}}  to {2,{0x02,0x0C}}, index 22 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {22, GESTURE_TRBL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[17] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x04}},    (entry [18] in all_snapshots array) begin here:
    // >>>>>>> entries [102] to [107]

    // Transitions from {2, {0x02, 0x04}},  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR
    {2, GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR},
    // Transitions from {2, {0x02, 0x04}},  to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT
    {3, GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {20,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x04,0x0A}}, index 28 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {28, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x02,0x09}}, index 21 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {21, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x02, 0x04}},  to {2,{0x04,0x02}}, index 24 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {24, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[18] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x08}},  (entry [19] in all_snapshots array) begin here:
    // >>>>>>> entries [108] to [113]

    // Transitions from {2, {0x02, 0x08}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from {2, {0x02, 0x08}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR
    {2, GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x02, 0x01}}, index 17 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {17, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x08, 0x01}}, index 29 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {29, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x02, 0x08}} to {2, {0x08, 0x04}}, index 31 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {31, GESTURE_TRBL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[19] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x05}},     (entry [20] in all_snapshots array) begin here:
    // >>>>>>> entries [114] to [119]

    // Transitions from {2, {0x02, 0x05}} to {1,{0x05}}, index 6 in all_snapshots) belong to GESTURE_BRTL
    {6, GESTURE_BRTL},
    // Transitions from {2, {0x02, 0x05}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR
    {2, GESTURE_TLBR},
    // Transitions from {2, {0x02, 0x05}} to {2,{0x02,0x04}}, index 18 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {18, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x02, 0x05}} to {2,{0x02,0x01}}, index 17 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {17, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x02, 0x05}} to {3,{0x02,0x05,0x08}}, index 52 in all_snapshots) belong to GESTURE_BRTL
    {52, GESTURE_BRTL},
    // Transitions from {2, {0x02, 0x05}} to {2,{0x05,0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[20] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x02, 0x09}},    (entry [21] in all_snapshots array) begin here:
    // >>>>>>> entries [120] to [123]

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
    // >>>>>>> entries [124] to [127]

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
    // >>>>>>> entries [128] to [133]

    // Transitions from {2, {0x04, 0x01}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {1, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x04, 0x01}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_BRTL | GESTURE_TLBR
    {3, GESTURE_BRTL | GESTURE_TLBR},
    // Transitions from {2, {0x04, 0x01}} to {2,{0x04,0x02}}, index 24 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {24,GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x04, 0x01}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL },
    // Transitions from {2, {0x04, 0x01}} to {2,{0x01,0x02}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x01}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[23] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x02}},    (entry [24] in all_snapshots array) begin here:
    // >>>>>>> entries [134] to [139]

    // Transitions from {2, {0x04, 0x02}},  to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR
    {2, GESTURE_TLBR | GESTURE_TB | GESTURE_BT | GESTURE_BLTR},
    // Transitions from {2, {0x04, 0x02}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT
    {3, GESTURE_TB | GESTURE_TRBL | GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}}  to {2,{0x02,0x05}}, index 20 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {20,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}} to {2,{0x04,0x0A}}, index 28 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {28, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}}  to {2,{0x02,0x09}}, index 21 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {21, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x04, 0x02}}  to {2,{0x04,0x09}}, index 27 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {27, GESTURE_BRTL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[24] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x08}},     (entry [25] in all_snapshots array) begin here:
    // >>>>>>> entries [140] to [145]

    // Transitions from {2, {0x04, 0x08}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {3, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2, {0x04, 0x0A}, index 28 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {47, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2,{0x08,0x05}}, index 33 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {39, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2,{0x04,0x09}}, index 27 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {44, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x08}}  to {2,{0x08,0x06}}, index 34 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {34, GESTURE_BLTR | GESTURE_LR},
    // All other possible transitions exiting from all_snapshots[25] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x03}},   (entry [26] in all_snapshots array) begin here:
    // >>>>>>> entries [146] to [149]

    // Transitions from {2, {0x04, 0x03}} to {1, {0x04}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {2, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x04, 0x03}} to {1, {0x03}}, index 10 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {10,GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x04, 0x03}} to {2, {0x04, 0x02}}, index 24 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {24, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x04, 0x03}} to {2, {0x04, 0x01}}}, index 23 in all_snapshots) belong to GESTURE_BRTL
    {23, GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[26] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x09}},   (entry [27] in all_snapshots array) begin here:
    // >>>>>>> entries [150] to [153]

    // Transitions from {2, {0x04, 0x09}} to {1, {0x04}}, index 2 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {2, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x04, 0x09}} to {1, {0x09}}, index 8 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {8,GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x04, 0x09}} to {2, {0x04, 0x09}}, index 27 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {27, GESTURE_TLBR | GESTURE_TB},
    // Transitions from {2, {0x04, 0x09}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[27] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x04, 0x0A}},   (entry [28] in all_snapshots array) begin here:
    // >>>>>>> entries [154] to [159]

    // Transitions from {2, {0x04, 0x0A}} to {1, {0x04}}, index 3 in all_snapshots) belong to GESTURE_TRBL
    {3, GESTURE_TRBL },
    // Transitions from {2, {0x04, 0x0A}} to {1, {0x0A}}, index 9 in all_snapshots) belong to GESTURE_BLTR
    {9, GESTURE_BLTR},
    // Transitions from {2, {0x04, 0x0A}} to {2, {0x02, 0x04}}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x04, 0x0A}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_TRBL  | GESTURE_RL
    {25, GESTURE_TRBL  | GESTURE_RL},
    // Transitions from {2, {0x04, 0x0A}} to {3, {0x04, 0x0A, 0x01}}, index 53 in all_snapshots) belong to GESTURE_BLTR
    {53, GESTURE_BLTR},
    // Transitions from {2, {0x04, 0x0A}} to {2, {0x0A, 0x01}}, index 46 in all_snapshots) belong to GESTURE_BLTR
    {46, GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[28] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x01}},   (entry [29] in all_snapshots array) begin here:
    // >>>>>>> entries [160] to [165]

    // Transitions from {2, {0x08, 0x01}} to {1,{0x01}}, index 1 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR
    {1, GESTURE_BLTR | GESTURE_TB | GESTURE_BT | GESTURE_TLBR},
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
    // >>>>>>> entries [166] to [171]

    // Transitions from {2, {0x08, 0x02}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_TRBL},
    // Transitions from {2, {0x08, 0x02}} to {1,{0x02}}, index 2 in all_snapshots) belong to GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR
    {2, GESTURE_BLTR | GESTURE_TRBL | GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x02, 0x01}}, index 17 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {17, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {18, GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x08, 0x01}}, index 29 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {29, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x08, 0x02}} to {2, {0x08, 0x02}}, index 30 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {30, GESTURE_TRBL | GESTURE_RL},
    // All other possible transitions exiting from all_snapshots[30] are illegal (and do not appear here)
    // <<<<<<<
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x04}},    (entry [31] in all_snapshots array) begin here:
    // >>>>>>> entries [172] to [177]

    // Transitions from {2, {0x08, 0x04}} to {1,{0x04}}, index 3 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR
    {3, GESTURE_TLBR | GESTURE_TRBL | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR
    {4, GESTURE_BRTL | GESTURE_BLTR | GESTURE_RL | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2, {0x04, 0x0A}, index 28 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {28, GESTURE_BLTR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2,{0x08,0x05}}, index 33 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {33, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2,{0x04,0x09}}, index 27 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {27, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x04}}  to {2,{0x08,0x06}}, index 34 in all_snapshots) belong to GESTURE_BLTR | GESTURE_LR
    {34, GESTURE_BLTR | GESTURE_LR},
    // All other possible transitions exiting from all_snapshots[31] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x03}},    (entry [32] in all_snapshots array) begin here:
    // >>>>>>> entries [178] to [181]

    // Transitions from {2, {0x08, 0x03}} to {1, {0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {4,GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x08, 0x03}} to {1, {0x03}}, index 10 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {10,GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x08, 0x03}} to {2, {0x08, 0x02}}, index 30 in all_snapshots) belong to GESTURE_TRBL | GESTURE_RL
    {30, GESTURE_TRBL | GESTURE_RL},
    // Transitions from {2, {0x08, 0x03}} to {2, {0x08, 0x01}}}, index 29 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {29, GESTURE_BT | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[32] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x05}},    (entry [33] in all_snapshots array) begin here:
    // >>>>>>> entries [182] to [187]

    // Transitions from {2, {0x08, 0x05}} to {1,{0x05}}, index 6 in all_snapshots) belong to GESTURE_TLBR
    {6, GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x05}} to {1,{0x08}}, index 4 in all_snapshots) belong to GESTURE_BRTL
    {4, GESTURE_BRTL},
    // Transitions from {2, {0x08, 0x05}} to {2,{0x04,0x08}}, index 25 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL
    {25, GESTURE_BRTL | GESTURE_RL},
    // Transitions from {2, {0x08, 0x05}} to {2,{0x01,0x08}}, index 13 in all_snapshots) belong to GESTURE_BRTL | GESTURE_BT
    {13, GESTURE_BRTL | GESTURE_BT},
    // Transitions from {2, {0x08, 0x05}} to {3,{0x08,0x05,0x02}}, index 54 in all_snapshots) belong to GESTURE_TLBR
    {54, GESTURE_TLBR},
    // Transitions from {2, {0x08, 0x05}} to {2,{0x05,0x02}}, index 38 in all_snapshots) belong to GESTURE_TLBR
    {38, GESTURE_TLBR},
    // All other possible transitions exiting from all_snapshots[33] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x08, 0x06}},   (entry [34] in all_snapshots array) begin here:
    // >>>>>>> entries [188] to [191]

    // Transitions from {2, {0x08, 0x06}} to {1, {0x08}}, index 4 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {4,GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x08, 0x06}} to {1, {0x06}}, index 7 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {7,GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x08, 0x06}} to {2, {0x08, 0x06}}, index 34 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {34, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x08, 0x06}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_RL | GESTURE_TRBL
    {13, GESTURE_RL | GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[34] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x03, 0x04}},    (entry [35] in all_snapshots array) begin here:
    // >>>>>>> entries [192] to [195]

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
    // >>>>>>> entries [196] to [199]

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
    // >>>>>>> entries [200] to [205]

    // Transitions from {2, {0x03, 0x0C}} to {1,{0x03}}, index 5 in all_snapshots) belong to GESTURE_LR
    {5, GESTURE_LR},
    // Transitions from {2, {0x03, 0x0C}} to {1,{0x0C}}, index 10 in all_snapshots) belong to GESTURE_RL
    {10, GESTURE_RL},
    // Transitions from {2, {0x03, 0x0C}} to {2, {0x01, 0x0C}}, index 16 in all_snapshots) belong to GESTURE_RL | GESTURE_BRTL
    {16, GESTURE_RL | GESTURE_BRTL},
    // Transitions from {2, {0x03, 0x0C}} to {2, {0x02, 0x0C}}, index 22 in all_snapshots) belong to GESTURE_RL | GESTURE_TRBL
    {22,GESTURE_RL | GESTURE_TRBL},
    // Transitions from {2, {0x03, 0x0C}} to {2, {0x03, 0x04}}, index 35 in all_snapshots) belong to GESTURE_LR | GESTURE_TLBR
    {35, GESTURE_LR | GESTURE_TLBR},
    // Transitions from {2, {0x03, 0x0C}} to {2, {0x03, 0x08}}, index 41 in all_snapshots) belong to GESTURE_LR | GESTURE_BLTR
    {41,GESTURE_LR | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[37] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x05, 0x02}},   (entry [38] in all_snapshots array) begin here:
    // >>>>>>> entries [206] to [211]

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
    // >>>>>>> entries [212] to [217]

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
    // >>>>>>> entries [218] to [220]

    // Transitions from {2, {0x06, 0x01}} to {1, {0x06}}, index 7 in all_snapshots) belong to GESTURE_TLBR | GESTURE_TB
    {7, GESTURE_TLBR | GESTURE_TB },
    // Transitions from {2, {0x06, 0x01}} to {2, {0x01, 0x02}}}, index 11 in all_snapshots) belong to GESTURE_TLBR | GESTURE_LR
    {11, GESTURE_TLBR | GESTURE_LR},
    // Transitions from {2, {0x06, 0x01}} to {2, {0x01, 0x04}}}, index 12 in all_snapshots) belong to GESTURE_BRTL | GESTURE_RL | GESTURE_BT
    {12, GESTURE_BRTL | GESTURE_RL | GESTURE_BT},
    // All other possible transitions exiting from all_snapshots[40] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x06, 0x08}},   (entry [41] in all_snapshots array) begin here:
    // >>>>>>> entries [221] to [224]

    // Transitions from {2, {0x06, 0x08}} to {1, {0x08}}, index 4 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {4,GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x06, 0x08}} to {1, {0x06}}, index 7 in all_snapshots) belong to GESTURE_TRBL | GESTURE_TB
    {7,GESTURE_TRBL | GESTURE_TB},
    // Transitions from {2, {0x06, 0x08}} to {2, {0x02, 0x08}}, index 19 in all_snapshots) belong to GESTURE_BLTR | GESTURE_BT
    {19, GESTURE_BLTR | GESTURE_BT},
    // Transitions from {2, {0x06, 0x08}} to {2, {0x04, 0x08}}}, index 25 in all_snapshots) belong to GESTURE_RL | GESTURE_TRBL
    {13, GESTURE_RL | GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[34] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x06, 0x09}},    (entry [42] in all_snapshots array) begin here:
    // >>>>>>> entries [225] to [230]

    // Transitions from {2, {0x06, 0x09}} to {1,{0x06}}, index 7 in all_snapshots) belong to GESTURE_TB
    {7, GESTURE_TB},
    // Transitions from {2, {0x06, 0x09}} to {1,{0x09}}, index 8 in all_snapshots) belong to GESTURE_BT
    {8, GESTURE_BT},
    // Transitions from {2, {0x06, 0x09}} to {2, {0x09, 0x02}}, index 43 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {43, GESTURE_BT | GESTURE_BLTR},
    // Transitions from {2, {0x06, 0x09}} to {2, {0x09, 0x04}}, index 44 in all_snapshots) belong to GESTURE_BT | GESTURE_BRTL
    {44,GESTURE_BT | GESTURE_BRTL},
    // Transitions from {2, {0x06, 0x09}} to {2, {0x01, 0x06}}, index 14 in all_snapshots) belong to GESTURE_TB | GESTURE_TLBR
    {14, GESTURE_LR | GESTURE_TLBR},
    // Transitions from {2, {0x06, 0x09}} to {2, {0x06, 0x08}}, index 41 in all_snapshots) belong to GESTURE_TB| GESTURE_TRBL
    {41,GESTURE_LR | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[42] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x09, 0x02}},   (entry [43] in all_snapshots array) begin here:
    // >>>>>>> entries [231] to [234]

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
    // >>>>>>> entries [235] to [238]

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
    // >>>>>>> entries [239] to [244]

    // Transitions from {2, {0x09, 0x06}} to {1,{0x06}}, index 7 in all_snapshots) belong to GESTURE_TB
    {7, GESTURE_TB},
    // Transitions from {2, {0x09, 0x06}} to {1,{0x09}}, index 8 in all_snapshots) belong to GESTURE_BT
    {8, GESTURE_BT},
    // Transitions from {2, {0x09, 0x06}} to {2, {0x09, 0x02}}, index 43 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {43, GESTURE_BT | GESTURE_BLTR},
    // Transitions from {2, {0x09, 0x06}} to {2, {0x09, 0x04}}, index 44 in all_snapshots) belong to GESTURE_BT | GESTURE_BRTL
    {44,GESTURE_BT | GESTURE_BRTL},
    // Transitions from {2, {0x09, 0x06}} to {2, {0x01, 0x06}}, index 14 in all_snapshots) belong to GESTURE_TB | GESTURE_TLBR
    {14, GESTURE_LR | GESTURE_TLBR},
    // Transitions from {2, {0x09, 0x06}} to {2, {0x06, 0x08}}, index 41 in all_snapshots) belong to GESTURE_TB| GESTURE_TRBL
    {41,GESTURE_LR | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[44] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {2, {0x0A, 0x01}},    (entry [46] in all_snapshots array) begin here:
    // >>>>>>> entries [245] to [250]

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
    // >>>>>>> entries [251] to [256]

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
    // >>>>>>> entries [257] to [260]

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
    // >>>>>>> entries [261] to [264]

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
    // >>>>>>> entries [265] to [270]

    // Transitions from {2, {0x0C, 0x03}} to {1,{0x03}}, index 5 in all_snapshots) belong to GESTURE_LR
    {5, GESTURE_LR},
    // Transitions from {2, {0x0C, 0x03}} to {1,{0x0C}}, index 10 in all_snapshots) belong to GESTURE_RL
    {10, GESTURE_RL},
    // Transitions from {2, {0x0C, 0x03}} to {2, {0x01, 0x0C}}, index 16 in all_snapshots) belong to GESTURE_RL | GESTURE_BRTL
    {16, GESTURE_RL | GESTURE_BRTL},
    // Transitions from {2, {0x0C, 0x03}} to {2, {0x02, 0x0C}}, index 22 in all_snapshots) belong to GESTURE_RL | GESTURE_TRBL
    {22,GESTURE_RL | GESTURE_TRBL},
    // Transitions from {2, {0x0C, 0x03}} to {2, {0x03, 0x04}}, index 35 in all_snapshots) belong to GESTURE_LR | GESTURE_TLBR
    {35, GESTURE_LR | GESTURE_TLBR},
    // Transitions from {2, {0x0C, 0x03}} to {2, {0x03, 0x08}}, index 41 in all_snapshots) belong to GESTURE_LR | GESTURE_BLTR
    {41,GESTURE_LR | GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[50] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {3, {0x01, 0x0A, 0x04}},    (entry [51] in all_snapshots array) begin here:
    // >>>>>>> entries [271] to [276]

    // Transitions from {3, {0x01, 0x0A, 0x04}} to {2, {0x01, 0x0A}}, index 15 in all_snapshots) belong to GESTURE_BLTR
    {15, GESTURE_BLTR},
    // Transitions from {3, {0x01, 0x0A, 0x04}} to {2, {0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_LR | GESTURE_BLTR
    {11, GESTURE_LR | GESTURE_BLTR},
    // Transitions from {3, {0x01, 0x0A, 0x04}} to {2, {0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {13, GESTURE_BT | GESTURE_BLTR},
    // Transitions from {3, {0x01, 0x0A, 0x04}} to {2, {0x0A, 0x04}}, index 47 in all_snapshots) belong to GESTURE_TRBL
    {47, GESTURE_TRBL},
    // Transitions from {3, {0x01, 0x0A, 0x04}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL
    {18, GESTURE_TB | GESTURE_TRBL},
    // Transitions from {3, {0x01, 0x0A, 0x04}} to {2, {0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_RL | GESTURE_TRBL
    {25, GESTURE_RL | GESTURE_TRBL},
    // All other possible transitions exiting from all_snapshots[51] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {3, {0x02, 0x05, 0x08}},   (entry [52] in all_snapshots array) begin here:
    // >>>>>>> entries [277] to [282]

    // Transitions from {3, {0x02, 0x05, 0x08}} to {2, {0x05, 0x02}}, index 38 in all_snapshots) belong to GESTURE_TLBR
    {38, GESTURE_TLBR},
    // Transitions from {3, {0x02, 0x05, 0x08}} to {2, {0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_LR | GESTURE_TLBR
    {11, GESTURE_LR | GESTURE_TLBR},
    // Transitions from {3, {0x02, 0x05, 0x08}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TB | GESTURE_TLBR
    {18, GESTURE_TB | GESTURE_TLBR},
    // Transitions from {3, {0x02, 0x05, 0x08}} to {2, {0x05, 0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // Transitions from {3, {0x02, 0x05, 0x08}} to {2, {0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_BT | GESTURE_BRTL
    {13, GESTURE_BT | GESTURE_BRTL},
    // Transitions from {3, {0x02, 0x05, 0x08}} to {2, {0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_RL | GESTURE_BRTL
    {25, GESTURE_RL | GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[52] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {3, {0x04, 0x0A, 0x01}},     (entry [53] in all_snapshots array) begin here:
    // >>>>>>> entries [283] to [289]

    // Transitions from {3, {0x04, 0x0A, 0x01}}} to {2, {0x01, 0x0A}}, index 15 in all_snapshots) belong to GESTURE_BLTR
    {15, GESTURE_BLTR},
    // Transitions from {3, {0x04, 0x0A, 0x01}}} to {2, {0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_LR | GESTURE_BLTR
    {11, GESTURE_LR | GESTURE_BLTR},
    // Transitions from {3, {0x04, 0x0A, 0x01}}} to {2, {0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_BT | GESTURE_BLTR
    {13, GESTURE_BT | GESTURE_BLTR},
    // Transitions from {3, {0x04, 0x0A, 0x01}} to {2, {0x0A, 0x04}}, index 47 in all_snapshots) belong to GESTURE_TRBL
    {47, GESTURE_TRBL},
    // Transitions from {3, {0x04, 0x0A, 0x01}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TB | GESTURE_TRBL
    {18, GESTURE_TB | GESTURE_TRBL},
    // Transitions from {3, {0x04, 0x0A, 0x01}} to {2, {0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_RL | GESTURE_TRBL
    {25, GESTURE_RL | GESTURE_TRBL},
    // Transitions from {3, {0x04, 0x0A, 0x01}} to {2, {0x0A, 0x01}}, index 46 in all_snapshots) belong to GESTURE_BLTR
    {46, GESTURE_BLTR},
    // All other possible transitions exiting from all_snapshots[53] are illegal (and do not appear here)
    // <<<<<<<

    // Valid transitions from snapshot {3, {0x08, 0x05, 0x02}},   (entry [54] in all_snapshots array) begin here:
    // >>>>>>> entries [290] to [295]

    // Transitions from {3, {0x08, 0x05, 0x02}} to {2, {0x05, 0x02}}, index 38 in all_snapshots) belong to GESTURE_TLBR
    {38, GESTURE_TLBR},
    // Transitions from {3, {0x08, 0x05, 0x02}} to {2, {0x01, 0x02}}, index 11 in all_snapshots) belong to GESTURE_LR | GESTURE_TLBR
    {11, GESTURE_LR | GESTURE_TLBR},
    // Transitions from {3, {0x08, 0x05, 0x02}} to {2, {0x02, 0x04}}, index 18 in all_snapshots) belong to GESTURE_TB | GESTURE_TLBR
    {18, GESTURE_TB | GESTURE_TLBR},
    // Transitions from {3, {0x08, 0x05, 0x02}} to {2, {0x05, 0x08}}, index 39 in all_snapshots) belong to GESTURE_BRTL
    {39, GESTURE_BRTL},
    // Transitions from {3, {0x08, 0x05, 0x02}} to {2, {0x01, 0x08}}, index 13 in all_snapshots) belong to GESTURE_BT | GESTURE_BRTL
    {13, GESTURE_BT | GESTURE_BRTL},
    // Transitions from {3, {0x08, 0x05, 0x02}} to {2, {0x04, 0x08}}, index 25 in all_snapshots) belong to GESTURE_RL | GESTURE_BRTL
    {25, GESTURE_RL | GESTURE_BRTL},
    // All other possible transitions exiting from all_snapshots[54] are illegal (and do not appear here)
    // <<<<<<<
};

const uint16_t *get_transitions_rows(void)
{
    return transitions_rows;
}

const transitions_t *get_transitions_pool(void)
{
    return transitions_pool;
}
