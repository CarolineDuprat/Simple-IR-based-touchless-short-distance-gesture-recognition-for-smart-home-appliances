#include "readFile.h"
/**
  * @file In this first part, we will read one line of the file.
  * For this, we will open the file in the function openFile
  * As long as the file is not finished, we will read one line and transform the information in allreceivers_info_t
  */


/**
 * @brief numberReceiver This function allows to count the number of receivers.
 * Each receiver is characterized by its ID which is displayed in hex, it is therefore in the form: 0x.
 * We will count the number of occurrences in a line of 'x' to know the number of receptors.
 * @param line file line
 * @return number of receivers
 */
uint16_t numberReceiver (char line[SIZE_MAX_CHARACTER]){
    uint16_t nbReceiver=0;

    //study each character one by one, and see if the character is equal to 'x'
    for(int i =0;i<SIZE_MAX_CHARACTER;i++){
        if (line[i]=='x'){
            nbReceiver ++;
        }
    }
    printf("%d\n",nbReceiver);

    return nbReceiver;
}
/**
 * @brief openFile The function open the file and count the number of receiver
 * @param lien Link of the file to study
 * @return the pointer of the file and the number of receiver
 */
infoFile openFile (char *lien){
    char line[SIZE_MAX_CHARACTER] = "";
    //Creation of the pointer to read in the file
    infoFile informationFile;
    informationFile.file=NULL;
    //Opening the file in reading mode
    informationFile.file = fopen(lien, "r");
    if (informationFile.file != NULL)
    {
        informationFile.numberSnapshot=numberReceiver (fgets(line, SIZE_MAX_CHARACTER, informationFile.file));
        //Returns the cursor to the beginning of the file because we just read a line from the file and the pointer has advanced
        rewind(informationFile.file);
    }
    else
    {
        printf("Impossible to open the file");
    }
    return informationFile;
}
/**
 * @brief readLineFile The function read 1 line of the file and take the information about the ID, Valid and time of each receiver
 * @param informationFile the pointer of the file and the number of receiver
 * @return id, time, valid for each receiver
 */
allreceivers_info_t readLineFile (infoFile informationFile){
    allreceivers_info_t infoReceivers;
    uint16_t iD,valid,time;
    infoReceivers.numberReceivers=informationFile.numberSnapshot;

    //for each receiver
    for (uint16_t i=0;i<informationFile.numberSnapshot;i++){
        //read its ID, time and valid
        fscanf(informationFile.file,"0x%d %d %d ",&iD,&time,&valid);
        //add this information in the struct receivers
        infoReceivers.receivers[i].id=iD;
        infoReceivers.receivers[i].time=time;
        infoReceivers.receivers[i].valid=valid;
        printf("ID = %d\n",iD);
        printf("time = %d\n",time);
        printf("valid = %d\n",valid);
    }

    return infoReceivers;
}
/**
 * @brief checkEndFile the function check if the file is finish
 * @param informationFile the pointer of the file and the number of receiver
 * @return 1 : End of the file, else 0
 */
uint8_t checkEndFile (infoFile informationFile){
    uint8_t check=0;
    //feof returns a value other than zero, if the pointer of the file has reached the end of the file; otherwise the value of the result is zero.
    if (feof( informationFile.file )!=0){
        check=1;
        //file closing
        fclose(informationFile.file);
    }
    return check;
}

