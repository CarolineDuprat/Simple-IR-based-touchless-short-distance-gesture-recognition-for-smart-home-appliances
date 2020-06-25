#include "readFile.h"
/**
  * @file In this first part, we will translate the information from the file
  * We will open the file, and count the number of lines.
  * Then we will read each line. We will recover for each receiver ID, time, valid. We will put this information in a table of allreceivers_info_t.
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

    printf("numberOfLines = %d\n",numberLines);

    //Returns the cursor to the beginning of the file
    rewind(file);

    return numberLines;
}
