#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <vector>

using namespace std;
std::string nameFile (std::string lien,double receiver[][2],int nbrReceiver,int angle,double sizeLength, double sizeWidth, std::vector <double> positionObject,double objectMovingSpeed,unsigned int time);
bool writeFile (std::string lien,double receiver[][2],int nbrReceiver,int angle,double sizeLength, double sizeWidth, std::vector <double> positionObject,double objectMovingSpeed,unsigned int time,double data [][3],int nbrID);

#endif // FILEMANAGEMENT_H
