#ifndef ALL_SNAPSHOTS_H
#define ALL_SNAPSHOTS_H
#include "structure.h"
/* This table defines the possible, valid snapshots given the number ofreceivers and shape.This example is for 4 receivers in a rectangle shape.
 * Assume we can combine receivers vertically, horizontally, or diagonally,but L-shapes are considered illegal. */
const snapshot_t all_snapshots[] = {
    /* Single individual receivers */
    {0, 1, {0x01}},
    {1, 1, {0x02}},
    {2, 1, {0x04}},
    {3, 1, {0x08}},
    /* Single combined receivers */
    {4, 1, {0x03}},
    {5, 1, {0x05}},
    {6, 1, {0x06}},
    {7, 1, {0x09}},
    {8, 1, {0x0A}},
    {9, 1, {0x0C}},
    /* Two receivers; receiver 0x01 and a second one. */
    /* Impossible combinations: 0x01 followed by 0x9, 0x3, 0x5 */
    {10, 2, {0x01, 0x02}},
    {11, 2, {0x01, 0x04}},
    {12, 2, {0x01, 0x08}},
    {13, 2, {0x01, 0x06}},
    {14, 2, {0x01, 0x0A}},
    {15, 2, {0x01, 0x0C}},
    /* Two receivers; receiver 0x02 and a second one. */
    /* Impossible combinations: 0x02 followed by 0x3, 0x6, 0xA */
    {16, 2, {0x02, 0x01}},
    {17, 2, {0x02, 0x04}},
    {18, 2, {0x02, 0x08}},
    {19, 2, {0x02, 0x05}},
    {20, 2, {0x02, 0x09}},
    {21, 2, {0x02, 0x0C}},
    /* Two receivers; receiver 0x04 and a second one. */
    /* Impossible combinations: 0x04 followed by 0x5, 0x6, 0xC */
    {22, 2, {0x04, 0x01}},
    {23, 2, {0x04, 0x02}},
    {24, 2, {0x04, 0x08}},
    {25, 2, {0x04, 0x03}},
    {26, 2, {0x04, 0x09}},
    {27, 2, {0x04, 0x0A}},
    /* Two receivers; receiver 0x08 and a second one. */
    /* Impossible combinations: 0x08 followed by 0x9, 0xA, 0xC */
    {28, 2, {0x08, 0x01}},
    {29, 2, {0x08, 0x02}},
    {30, 2, {0x08, 0x04}},
    {31, 2, {0x08, 0x03}},
    {32, 2, {0x08, 0x05}},
    {33, 2, {0x08, 0x06}},
    /* Two receivers; receiver 0x03 and a second one. */
    /* Possible combinations: 0x03 followed by 0x4, 0x8, or 0xC */
    {34, 2, {0x03, 0x04}},
    {35, 2, {0x03, 0x08}},
    {36, 2, {0x03, 0x0C}},
    /* Two receivers; receiver 0x05 and a second one. */
    /* Possible combinations: 0x05 followed by 0x2 or 0x8 */
    {37, 2, {0x05, 0x02}},
    {38, 2, {0x05, 0x08}},
    /* Two receivers; receiver 0x06 and a second one. */
    /* Possible combinations: 0x06 followed by 0x1, 0x8, or 0x9 */
    {39, 2, {0x06, 0x01}},
    {40, 2, {0x06, 0x08}},
    {41, 2, {0x06, 0x09}},
    /* Two receivers; receiver 0x09 and a second one. */
    /* Possible combinations: 0x09 followed by 0x2, 0x4, or 0x6 */
    {42, 2, {0x09, 0x02}},
    {43, 2, {0x09, 0x04}},
    {44, 2, {0x09, 0x06}},
    /* Two receivers; receiver 0x0A and a second one. */
    /* Possible combinations: 0x0A followed by 0x1 or 0x4 */
    {45, 2, {0x0A, 0x01}},
    {46, 2, {0x0A, 0x04}},
    /* Two receivers; receiver 0x0C and a second one. */
    /* Possible combinations: 0x0C followed by 0x1, 0x2, or 0x3 */
    {47, 2, {0x0C, 0x01}},
    {48, 2, {0x0C, 0x02}},
    {49, 2, {0x0C, 0x03}},
    /* Three receivers: Let's assume an L-shape is illegal, so the onlyvalid combinations of 3 receivers are diagonal:receiver, two receivers combined, and receiver */
    {50, 3, {0x01, 0x0A, 0x04}},
    {51, 3, {0x02, 0x05, 0x08}},
    {52, 3, {0x04, 0x0A, 0x01}},
    {53, 3, {0x08, 0x05, 0x02}},
    /* There are no valid snapshots of 4 receivers */
    /* Mark the end of the table with this special snapshot(0 receivers, receiver ID 0x00) */
    {54, 0, {0x00}},};
#endif // ALL_SNAPSHOTS_H
