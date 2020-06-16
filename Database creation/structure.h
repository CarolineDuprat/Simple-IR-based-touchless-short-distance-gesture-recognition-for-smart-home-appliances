#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <vector>

typedef struct {
    unsigned ID;
    int time;
    bool valid;
} rec;

typedef struct {
    double hor;
    double vert;
} speed_t;

typedef struct {
    double x;
    double y;
} position_t;

typedef struct {
    position_t pos;
    speed_t speed;
} returnSpeedPos;

typedef struct {
    std::vector<double> positionReceiver;
    bool check;
} returnInit;

typedef struct {
    double length;
    double width;
} dimension;


#endif // STRUCTURE_H
