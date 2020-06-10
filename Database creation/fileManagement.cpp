#include "fileManagement.h"
using namespace std;

/**
 * @brief writeFile write line data in a file
 * @param nameFile name of the file
 * @param data ID, time, valid
 * @param nbrID number of ID
 * @return true: the line has been added to the file
 */
bool writeFile (string nameFile,double data [][3],int nbrID)
{
    bool retour(false);
    nameFile += ".txt" ;
    // open the file
    ofstream monFlux(nameFile.c_str(),ios::app);
    if(monFlux)
    {
        for (int compteur(0) ; compteur < nbrID ; compteur++){
            monFlux << data [compteur][0] << " "<< data [compteur][1] << " "<< data [compteur][2] << " ";
        }
        monFlux << endl;
        retour=true;
    }
    return retour;
}

