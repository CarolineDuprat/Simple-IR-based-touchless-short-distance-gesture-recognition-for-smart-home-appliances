#include "readFile.h"
/**
  * @file In this first part, we will translate the information from the file
  * We will open the file, count the number of lines and the number of receiver.
  * Then we will read each line. We will recover for each receiver ID, time, valid. We will put this information in a table of allreceivers_info.
  * We will close the file.
  */

/**
 * @brief numberOfLines This function allows to count the number of lines in a file.
 * For this, we will read each character of the file and we will count the number of times that the file has the character '\n', it means that there is a line break.
 * @param file
 * @return number of lines
 */
uint16_t numberOfLines (FILE* file){
    int character;
    uint16_t numberLines = 0;

    //As long as the character read is not equal to EOF, EOF means either that we are at the end of the file, or that there is an error
    while((character=fgetc(file)) != EOF)
    {
        // '\n' :Line break
        if(character=='\n')
            numberLines++;
    }

    printf("number of lines = %d\n",numberLines);

    //Returns the cursor to the beginning of the file
    rewind(file);

    return numberLines;
}
/**
 * @brief numberReceiver This function allows you to count the number of receivers.
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
 * @brief translateInfoFromFile This function allows you to read the information in the file and put it in the struct allreceivers_info.
 * @param lien Link of the file to study
 * @return all information of the simulation: id, time, valid for each receiver for each time
 */
allreceivers_info translateInfoFromFile (char *lien){
    char line[SIZE_MAX_CHARACTER] = "";
    uint16_t iD,valid,time;
    allreceivers_info receivers;

    //Creation of the pointer to read in the file
    FILE* file = NULL;
    //Opening the file in reading mode
    file = fopen(lien, "r");

    //If the file is open
    if (file != NULL)
    {
        //calculate the number of lines in the file
        receivers.timeSimulationTotal = numberOfLines (file);
        //calculate the number of receivers
        receivers.numberReceivers=numberReceiver (fgets(line, SIZE_MAX_CHARACTER, file));
        //Returns the cursor to the beginning of the file because we just read a line from the file and the pointer has advanced
        rewind(file);

        //for each line in the file
        for (uint16_t counter=0;counter<receivers.timeSimulationTotal;counter++){
            //for each receiver
            for (uint16_t i=0;i<receivers.numberReceivers;i++){
                //read its ID, time and valid
                fscanf(file,"0x%d %d %d ",&iD,&time,&valid);
                //add this information in the struct receivers
                receivers.t[counter].receivers[i].id=iD;
                receivers.t[counter].receivers[i].time=time;
                receivers.t[counter].receivers[i].valid=valid;
                printf("ID = %d\n",iD);
                printf("time = %d\n",time);
                printf("valid = %d\n",valid);
            }
            printf("time simulation = %d\n",counter);
            printf("\n");
        }
        //file closing
        fclose(file);
    }
    else
    {
        receivers.timeSimulationTotal =0;
        printf("Impossible to open the file");
    }

    return receivers;
}
/**
 * @brief checkFunction The function allows to create a file with the data you just recovered. This makes it possible to verify that the function
 * "translateInfoFromFile" works correctly.
 * @param receivers all information of the simulation: id, time, valid for each receiver for each time
 * @return 1 : the file is create; else 0
 */
void checkFunction (allreceivers_info receivers){
    FILE* file = NULL;
    char chaine[20]="",line[SIZE_MAX_CHARACTER]="";

    //lecture et écriture, avec suppression du contenu au préalable.
    file = fopen("verification.txt", "w+");
    if (file != NULL)
    {
        //for each line in the file
        for (uint16_t counter=0;counter<receivers.timeSimulationTotal;counter++){
            //for each receiver
            for (uint16_t i=0;i<receivers.numberReceivers;i++){
                // the function "sprintf" allows to write in a chain
                sprintf(chaine, "0x%d %d %d ", receivers.t[counter].receivers[i].id,receivers.t[counter].receivers[i].time,receivers.t[counter].receivers[i].valid );
                // We concatenate chaine into line
                strcat(line, chaine);
                //delete the elements in the chaine
                chaine[0] = '\0';
            }
            // We concatenate "\n" into line
            strcat(line, "\n");
            //addition of characters in the text
            fputs(line, file);
            //delete the elements in the line
            line[0]='\0';
        }
        //file closing
        fclose(file);
    }
    else
    {
        printf("Impossible to open the file");
    }
}
