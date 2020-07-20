#ifndef READFILE_H
#define READFILE_H
#include "structure.h"

uint16_t numberOfLines (FILE* file);
uint16_t numberReceiver (char chaine[SIZE_MAX_CHARACTER]);
allreceivers_info translateInfoFromFile (char *lien);
void checkFunction (allreceivers_info receivers);

infoFile openFile (char *lien);
allreceivers_info_t readLineFile (infoFile informationFile);
uint8_t checkEndFile (infoFile informationFile);

#endif // READFILE_H
