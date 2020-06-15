#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>
#include "structure.h"

bool writeFile (std::string lien ,std::string nameFile,rec data[],int nbrID);
std::string nameFile (int nbrReceiver,position_t positionReceiver[],int angle, double distance,double speed,dimension dimensionObject);

#endif // FILEMANAGEMENT_H
