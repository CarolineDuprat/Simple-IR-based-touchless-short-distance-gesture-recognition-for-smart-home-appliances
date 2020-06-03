#include "fileManagement.h"

/**
 * @brief nameFile create file name
 * @param lien file location
 * @param receiver position Receiver
 * @param nbrReceiver number of Receiver
 * @param angle Angular position of the obstacle
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param positionObject position (x,y) object , it's the position of the top front left
 * @param objectMovingSpeed speed of the object
 * @param time
 * @return file name
 */
string nameFile (string lien,double receiver[][2],int nbrReceiver,int angle,double sizeLength, double sizeWidth, double positionObject[],double objectMovingSpeed,unsigned int time)
{
    string nomFichier("file");
    double distance;
    for (int compteur(0) ; compteur < nbrReceiver ; compteur++){
        nomFichier += 'R';
        nomFichier += to_string(compteur+1);
        nomFichier += '_';
        nomFichier += to_string(receiver[compteur][0]);
        nomFichier.erase(nomFichier.size() - 4);
        nomFichier += '_';
        nomFichier += to_string(receiver[compteur][1]);
        nomFichier.erase(nomFichier.size() - 4);
        nomFichier += "_";
    }
    nomFichier += "A_";
    nomFichier += to_string(angle);
    nomFichier += "_M_";
    nomFichier += to_string(sizeLength);
    nomFichier.erase(nomFichier.size() - 4);
    nomFichier += '_';
    nomFichier += to_string(sizeWidth);
    nomFichier.erase(nomFichier.size() - 4);
    nomFichier += "_D_";
    distance =  sqrt(abs(pow(positionObject[0],2) + pow(positionObject[1],2) - pow(sizeWidth/2,2) ));
    nomFichier += to_string(distance);
    nomFichier.erase(nomFichier.size() - 4);
    nomFichier += "_S_";
    nomFichier += to_string(objectMovingSpeed);
    nomFichier.erase(nomFichier.size() - 4);
    nomFichier += "_T_";
    nomFichier += to_string(time);
    nomFichier += ".txt";
    lien += nomFichier;
    return lien;

}

/**
 * @brief writeFile write data in a file
 * @param lien file location
 * @param receiver position Receiver
 * @param nbrReceiver number of Receiver
 * @param angle Angular position of the obstacle
 * @param sizeLength rectangle length
 * @param sizeWidth rectangle width
 * @param positionObject position (x,y) object , it's the position of the top front left
 * @param objectMovingSpeed speed of the object
 * @param time
 * @param data ID, time, valid
 * @param nbrID number of ID
 * @return true: the line has been added to the file
 */
bool writeFile (string lien,double receiver[][2],int nbrReceiver,int angle,double sizeLength, double sizeWidth, double positionObject[],double objectMovingSpeed,unsigned int time,double data [][3],int nbrID)
{
    string nomFichier;
    bool retour;
    nomFichier = nameFile (lien,receiver,nbrReceiver,angle,sizeLength, sizeWidth, positionObject,objectMovingSpeed,time);
    ofstream monFlux(nomFichier.c_str(),ios::app);
    if(monFlux)
    {
        for (int compteur(0) ; compteur < nbrID ; compteur++){
            monFlux << data [compteur][0] << " "<< data [compteur][1] << " "<< data [compteur][2] << " ";
        }
        monFlux << endl;
        retour=true;
    }
    else
    {
        retour=false;
    }
    return retour;
}



