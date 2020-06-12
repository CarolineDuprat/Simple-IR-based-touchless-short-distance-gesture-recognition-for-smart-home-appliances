#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

typedef struct {
    unsigned ID;
    int time;
    bool valid;
} rec;

bool writeFile (std::string nameFile,rec data,int nbrID);
std::vector<unsigned> iDBinaire  (int nbrID);

#endif // FILEMANAGEMENT_H
