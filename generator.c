#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

//stocke les mots dans un fichier result.txt si il nexiste pas le cree
int main(int argc, char const *argv[])
{
    if (argc != 3)
    {
        printf("Syntaxe : %s [lenWord1] [lenWord2]\n", argv[0]);
        return EXIT_FAILURE;
    }
    int len1 = atoi(argv[1]);
    int len2 = atoi(argv[2]);
    FILE *resultFile = fopen("result.txt", "w");
    if (resultFile == NULL)
    {
        printf("Erreur overture fichier\n");
        return EXIT_FAILURE;
    }
    srand((unsigned)time(NULL));
    double *word1 = getWord(0.0, 1.0, len1);
    double *word2 = getWord(0.0, 1.0, len2);
    printWord(word1, NULL, len1, 0);
    printWord(word2, NULL, len2, 0);
    ecrireWord(word1, len1, resultFile);
    ecrireWord(word2, len2, resultFile);
    fclose(resultFile);
    int *word1Binaries = toBinariesWithErrors(word1, len1);
    int *word2Binaries = toBinariesWithErrors(word2, len2);
    printWord(NULL, word1Binaries, len1, 1);
    printWord(NULL, word2Binaries, len2, 1);
    return 0;
}