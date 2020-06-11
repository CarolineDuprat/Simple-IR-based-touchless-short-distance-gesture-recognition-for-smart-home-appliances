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
            monFlux << "Ox" << std::hex << data [compteur][0] << std::dec << " "<< data [compteur][1] << " "<<  std::dec << data [compteur][2] << " ";
        }
        monFlux << endl;
        retour=true;
    }
    return retour;
}
/**
 * @brief iDDecimal generated an ID for each receiver in decimal. We will displaythis number in hexa in the function writeFile
 * R1 : 00000001, R2 : 00000010, .... R8 : 10000000
 * @param nbrID number of ID
 * @return the iD list
 *
 * With doubles: nbrID = 0 => pow(2,0) = 1.0 -> binary != 000001
 */
std::vector<unsigned> iDBinaire  (int nbrID){
    std::vector<unsigned> iD(nbrID);
    for (int i(0);i<nbrID;i++){
        iD[i] = 1 << nbrID;
    }
    return iD;
}


