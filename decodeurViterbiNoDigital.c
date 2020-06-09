#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "math.h"

typedef struct n
{
    int code[2];
    float poids;
    int etat;
    struct n *precedent;
    struct n *suivant1, *suivant2;
    int final;
} noeud, *p_noeud;

noeud *nouveauNoeud(noeud *precedent, float *code, int indice, int etat,
                    float poids, int input, int *etatSuivant)
{
    noeud *new = malloc(sizeof(struct n));
    new->poids = poids;
    new->final = 0;
    new->precedent = precedent;
    switch (etat)
    {
    case 0:
        if (!input)
        {
            new->code[0] = 0;
            new->code[1] = 0;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 0;
            new->etat = 0;
        }
        else
        {
            new->code[0] = 1;
            new->code[1] = 1;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 1;
            new->etat = 1;
        }
        break;
    case 1:
        if (!input)
        {
            new->code[0] = 1;
            new->code[1] = 0;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 2;
            new->etat = 2;
        }
        else
        {
            new->code[0] = 0;
            new->code[1] = 1;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 3;
            new->etat = 3;
        }
        break;
    case 2:
        if (!input)
        {
            new->code[0] = 1;
            new->code[1] = 1;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 0;
            new->etat = 0;
        }
        else
        {
            new->code[0] = 0;
            new->code[1] = 0;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 1;
            new->etat = 1;
        }
        break;
    case 3:
        if (!input)
        {
            new->code[0] = 0;
            new->code[1] = 1;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 2;
            new->etat = 2;
        }
        else
        {
            new->code[0] = 1;
            new->code[1] = 0;
            new->poids = new->poids * new->poids;
            new->poids +=
                (code[indice] - new->code[0]) * (code[indice] - new->code[0]);
            new->poids += (code[indice + 1] - new->code[1]) *
                          (code[indice + 1] - new->code[1]);
            new->poids = sqrt(new->poids);
            *etatSuivant = 3;
            new->etat = 3;
        }
        break;
    }
    new->suivant1 = NULL;
    return new;
}

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

void decoder(noeud *n, int *m, int taille)
{
    int etat;
    for (int j = 0; j < taille; j++)
    {
        if (n->suivant1->final)
            n = n->suivant1;
        else
            n = n->suivant2;
        etat = n->precedent->etat;
        switch (etat)
        {
        case 0:
            if (n->code[0] == 1)
            {
                m[j] = 1;
                etat = 1;
            }
            else
            {
                m[j] = 0;
                etat = 0;
            }
            break;
        case 1:
            if (n->code[0] == 0)
            {
                m[j] = 1;
                etat = 3;
            }
            else
            {
                m[j] = 0;
                etat = 2;
            }
            break;
        case 2:
            if (n->code[0] == 0)
            {
                m[j] = 1;
                etat = 1;
            }
            else
            {
                m[j] = 0;
                etat = 0;
            }
            break;
        case 3:
            if (n->code[0] == 1)
            {
                m[j] = 1;
                etat = 3;
            }
            else
            {
                m[j] = 0;
                etat = 2;
            }
            break;
        default:
            printf("Erreur, ne devrait jamais passer ici\n");
            exit(3);
        }
    }
}

int *decodeur(float *code, int taille)
{
    noeud *tete;
    tete = malloc(sizeof(struct n));
    tete->precedent = NULL;
    tete->precedent = NULL;
    noeud *actuel[4];
    int useless;
    tete->suivant1 = nouveauNoeud(tete, code, 0, 0, 0, 0, &useless);
    tete->suivant2 = nouveauNoeud(tete, code, 0, 0, 0, 1, &useless);
    tete->suivant1->suivant1 =
        nouveauNoeud(tete->suivant1, code, 2, tete->suivant1->etat,
                     tete->suivant1->poids, 0, &useless);
    tete->suivant1->suivant2 =
        nouveauNoeud(tete->suivant1, code, 2, tete->suivant1->etat,
                     tete->suivant1->poids, 1, &useless);
    tete->suivant2->suivant1 =
        nouveauNoeud(tete->suivant2, code, 2, tete->suivant2->etat,
                     tete->suivant2->poids, 0, &useless);
    tete->suivant2->suivant2 =
        nouveauNoeud(tete->suivant2, code, 2, tete->suivant2->etat,
                     tete->suivant2->poids, 1, &useless);

    actuel[0] = tete->suivant1->suivant1;
    actuel[1] = tete->suivant1->suivant2;
    actuel[2] = tete->suivant2->suivant1;
    actuel[3] = tete->suivant2->suivant2;
    noeud *tmp2[4];
    for (int j = 2; j < (taille / 2); j++)
    {
        noeud *tmp;
        int indice = 0;

        for (int k = 0; k < 4; k++)
        {
            tmp2[k] = NULL;
            actuel[k]->suivant1 =
                nouveauNoeud(actuel[k], code, j * 2, actuel[k]->etat,
                             actuel[k]->poids, 0, &indice);
            actuel[k]->suivant2 = tmp =
                nouveauNoeud(actuel[k], code, j * 2, actuel[k]->etat,
                             actuel[k]->poids, 1, &indice);
        }
        for (int l = 0; l < 4; l++)
        {
            if (tmp2[actuel[l]->suivant1->etat] == NULL ||
                tmp2[l]->poids > actuel[l]->suivant1->poids)
                tmp2[actuel[l]->suivant1->etat] = actuel[l]->suivant1;
            if (tmp2[actuel[l]->suivant2->etat] == NULL ||
                tmp2[l]->poids > actuel[l]->suivant2->poids)
                tmp2[actuel[l]->suivant2->etat] = actuel[l]->suivant2;
        }
        for (int p = 0; p < 4; p++)
            actuel[p] = tmp2[p];
    }
    noeud *min = actuel[0];
    for (int p = 1; p < 4; p++)
    {
        if (min->poids > actuel[p]->poids)
            min = actuel[p];
    }
    while (min->precedent != NULL)
    {
        min->final = 1;
        min = min->precedent;
    }
    int *message = malloc(sizeof(int) * taille / 2);
    decoder(tete, message, taille / 2);

    return message;
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

//stocke les mots dans un fichier result.txt si il nexiste pas le cree
int mainV2(int argc, char const *argv[])
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

int main(int argc, char const *argv[])
{

    printf("Valeur aléatoire\n\n");
    srand((unsigned)time(NULL));
    int i = 16;
    float code[i];
    for (int j = 0; j < i; j++)
        code[j] = randomizer(0.0, 1.0);
    ;

    int *message;
    message = decodeur(code, i);
    for (int j = 0; j < i / 2; j++)
    {
        printf("%d", message[j]);
    }
    printf("\n\n");
    free(message);

    printf(
        "Test valeur fixé (avec erreur):\n\nCode : 0.70 0.14 0.77 0.76 0.58 0.64 "
        "0.19 0.37 "
        "0.99 0.15 0.66 0.11\nMessage :");
    i = 12;

    code[0] = 0.70;
    code[1] = 0.14;
    code[2] = 0.77;
    code[3] = 0.76;
    code[4] = 0.58;
    code[5] = 0.64;
    code[6] = 0.19;
    code[7] = 0.37;
    code[8] = 0.99;
    code[9] = 0.15;
    code[10] = 0.66;
    code[11] = 0.11;

    message = decodeur(code, i);
    for (int j = 0; j < i / 2; j++)
    {
        printf("%d", message[j]);
    }
    printf("\n\n");
    free(message);
    return 0;
}
