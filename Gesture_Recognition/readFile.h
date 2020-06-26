#ifndef READFILE_H
#define READFILE_H
#include "structure.h"

uint16_t numberOfLines (FILE* file);
uint16_t numberReceiver (char chaine[SIZE_MAX_CHARACTER]);
allreceivers_info translateInfoFromFile (char *lien);
void checkFunction (allreceivers_info receivers);

#endif // READFILE_H