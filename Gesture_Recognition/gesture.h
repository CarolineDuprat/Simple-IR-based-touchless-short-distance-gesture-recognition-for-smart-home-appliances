#ifndef GESTURE_H
#define GESTURE_H
#include "structure.h"

/* Gesture*/
// T = TOP, B = BOTTOM, L = LEFT, R = RIGHT
#define GESTURE_TB   0x01 /* Vertical top to bottom */
#define GESTURE_BT   0x02 /* Vertical bottom to top */
#define GESTURE_LR   0x04 /* Horizontal left to right */
#define GESTURE_RL   0x08 /* Horizontal right to left */
#define GESTURE_TLBR 0x10 /* Diagonal top-left to bottom-right */
#define GESTURE_TRBL 0x20 /* Diagonal top-right to bottom-left */
#define GESTURE_BLTR 0x40 /* Diagonal bottom-left to top-right */
#define GESTURE_BRTL 0x80 /* Diagonal bottom-right to top-left */
#define GESTURE_ALL  0xff
#define GESTURE_NONE 0x00

typedef struct {
    uint16_t snapshotID;
    uint16_t gestureID;
} transitions_t;


const uint16_t *get_transitions_rows(void);
const transitions_t *get_transitions_pool(void);

#endif // GESTURE_H
