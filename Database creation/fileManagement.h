#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

bool writeFile (std::string nameFile,double data [][3],int nbrID);
std::vector<double> iDDecimal (int nbrID);

#endif // FILEMANAGEMENT_H
