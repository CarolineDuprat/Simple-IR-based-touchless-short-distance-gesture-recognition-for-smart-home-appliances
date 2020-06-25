#include <stdlib.h>
#include <stdio.h>
#include "structure.h"
#include "readFile.h"


int main()
{
    FILE* fichier = NULL;
    fichier = fopen("Data\\4_1_1_1_-1_-1_-1_-1_1_310_10_5_4_4_.txt", "r");
    char chaine[SIZE_MAX_CHARACTER] = "";
    uint16_t number;
    if (fichier != NULL)
    {
        number = numberOfLines (fichier);
        for (uint16_t i = 0; i< number;i++){
            fgets(chaine, SIZE_MAX_CHARACTER, fichier);
            printf("%s", chaine);
        }

        /*
         * Retrieve information for each receiver
        int valid;
        int time;
        fscanf(fichier,"0x%s %d %d ",&chaine,&time,&valid);
        printf("ID = %s\n",chaine);
        printf("time = %d\n",time);
        printf("valid = %d\n",valid);
        */

        fclose(fichier);
    }
    else
    {
        printf("Impossible to open the file");
    }

    return 0;
}
