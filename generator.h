#ifndef _GENERATOR_
#define _GENERATOR_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double randomizer(double a, double b)
{
    return (rand() / (double)RAND_MAX) * (b - a) + a;
}

// suppose que la graine a ete initialise
double *getWord(double a, double b, int len)
{
    double *word = malloc(len * sizeof(double));
    for (int i = 0; i < len; i++)
    {
        word[i] = (rand() / (double)RAND_MAX) * (b - a) + a;
    }
    return word;
}

//bin = 1 si le mot est en binaire
void printWord(double *word, int *wordBin, int len, int bin)
{
    for (int i = 0; i < len; i++)
    {
        if (bin)
        {
            printf("%d ", wordBin[i]);
        }
        else
        {
            printf("%f ", word[i]);
        }
    }
    printf("\n");
}

// suppose que le descripteur est deja ouvert
void ecrireWord(double *word, int len, FILE *f)
{
    fprintf(f, "%d\n", len);
    for (int i = 0; i < len; i++)
    {
        fprintf(f, "%f ", word[i]);
    }
    fprintf(f, "\n");
}

//code : reel <= 0.5 -> 0 / > 0.5 -> 1 , introduit une erreur si reel = 0.5 [+-0.1]
int *toBinariesWithErrors(double *word, int len)
{
    int *result = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        double tmp = word[i];
        if (tmp <= 0.5)
        {
            //introduction d'erreur
            if (tmp + 0.1 >= 0.5)
            {
                result[i] = 1;
            }
            else
            {
                result[i] = 0;
            }
        }
        else
        {
            //introduction d'erreur
            if (tmp - 0.1 <= 0.5)
            {
                result[i] = 0;
            }
            else
            {
                result[i] = 1;
            }
        }
    }
    return result;
}
#endif