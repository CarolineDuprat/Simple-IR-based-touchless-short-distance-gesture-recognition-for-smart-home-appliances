/**
  * @file The program must return a file with the information returned by the receivers (ID, time, valid).
  *
  * For this, we will create a file whose name is created in the main for the command line and in the function nameFile for interaction with the user.
  * We will then add a row to this file per millisecond.
  * The function "writeFile" allows to add a row.
  */

#include "fileManagement.h"
using namespace std;

/**
 * @brief writeFile write row data in a file : Id (hex) , time (us), valid (boolean)
 * @param lien where you want to create the file
 * @param nameFile name of the file
 * @param data ID, time, valid
 * @param nbrID number of ID
 * @return true: the line has been added to the file
 */
bool writeFile (string lien , string nameFile,rec data[],int nbrID)
{
    bool retour(false);
    nameFile += ".txt" ;
    lien += nameFile;
    // open the file
    ofstream monFlux(lien.c_str(),ios::app);
    if(monFlux)
    {
        for (int compteur(0) ; compteur < nbrID ; compteur++){
            monFlux << "0x" << std::hex << data[compteur].ID << std::dec << ' ' << data [compteur].time << ' ' <<  std::dec << data [compteur].valid << ' ';
        }

        monFlux << endl;
        retour=true;
    }
    return retour;
}
/**
 * @brief nameFile create the file name
 * @param nbrReceiver number of receiver
 * @param positionReceiver position x and y of all paramaters [cm]
 * @param angle Angular position of the obstacle [°]
 * @param distance distance from object center to device center [cm]
 * @param speed speed of the object [m/s]
 * @param dimensionObject dimension of the object [cm]
 * @return the file name
 */
string nameFile (int nbrReceiver,position_t positionReceiver[],int angle, double distance,double speed,dimension dimensionObject)
{
    string nameFile;

    nameFile += to_string(nbrReceiver);
    for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
        nameFile += to_string(positionReceiver[compteur].x);
        nameFile.erase(nameFile.size() - 4);
        nameFile += '_';
        nameFile += to_string(positionReceiver[compteur].y);
        nameFile.erase(nameFile.size() - 4);
        nameFile += "_";
    }
    nameFile += to_string(angle);
    nameFile += to_string(distance);
    nameFile.erase(nameFile.size() - 4);
    nameFile += to_string(speed);
    nameFile.erase(nameFile.size() - 4);
    nameFile += to_string(dimensionObject.width);
    nameFile.erase(nameFile.size() - 4);
    nameFile += '_';
    nameFile += to_string(dimensionObject.length);
    nameFile.erase(nameFile.size() - 4);

    return nameFile;
}

