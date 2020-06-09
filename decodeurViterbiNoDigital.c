#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "math.h"

typedef struct n {
  int code[2];
  float poids;
  int etat;
  struct n* precedent;
  struct n *suivant1, *suivant2;
  int final;
} noeud, *p_noeud;

noeud* nouveauNoeud(noeud* precedent, float* code, int indice, int etat,
                    float poids, int input, int* etatSuivant) {
  noeud* new = malloc(sizeof(struct n));
  new->poids = poids;
  new->final = 0;
  new->precedent = precedent;
  switch (etat) {
    case 0:
      if (!input) {
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
      } else {
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
      if (!input) {
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
      } else {
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
      if (!input) {
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
      } else {
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
      if (!input) {
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
      } else {
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

double randomizer(double a, double b) {
  return (rand() / (double)RAND_MAX) * (b - a) + a;
}

// suppose que la graine a ete initialise
double* getWord(double a, double b, int len) {
  double* word = malloc(len * sizeof(double));
  for (int i = 0; i < len; i++) {
    word[i] = (rand() / (double)RAND_MAX) * (b - a) + a;
  }
  return word;
}

void decoder(noeud* n, int* m, int taille) {
  int etat;
  for (int j = 0; j < taille; j++) {
    if (n->suivant1->final)
      n = n->suivant1;
    else
      n = n->suivant2;
    etat = n->precedent->etat;
    switch (etat) {
      case 0:
        if (n->code[0] == 1) {
          m[j] = 1;
          etat = 1;
        } else {
          m[j] = 0;
          etat = 0;
        }
        break;
      case 1:
        if (n->code[0] == 0) {
          m[j] = 1;
          etat = 3;
        } else {
          m[j] = 0;
          etat = 2;
        }
        break;
      case 2:
        if (n->code[0] == 0) {
          m[j] = 1;
          etat = 1;
        } else {
          m[j] = 0;
          etat = 0;
        }
        break;
      case 3:
        if (n->code[0] == 1) {
          m[j] = 1;
          etat = 3;
        } else {
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

int* decodeur(float* code, int taille) {
  noeud* tete;
  tete = malloc(sizeof(struct n));
  tete->precedent = NULL;
  tete->precedent = NULL;
  noeud* actuel[4];
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
  noeud* tmp2[4];
  for (int j = 2; j < (taille / 2); j++) {
    noeud* tmp;
    int indice = 0;

    for (int k = 0; k < 4; k++) {
      tmp2[k] = NULL;
      actuel[k]->suivant1 =
          nouveauNoeud(actuel[k], code, j * 2, actuel[k]->etat,
                       actuel[k]->poids, 0, &indice);
      actuel[k]->suivant2 = tmp =
          nouveauNoeud(actuel[k], code, j * 2, actuel[k]->etat,
                       actuel[k]->poids, 1, &indice);
    }
    for (int l = 0; l < 4; l++) {
      if (tmp2[actuel[l]->suivant1->etat] == NULL ||
          tmp2[l]->poids > actuel[l]->suivant1->poids)
        tmp2[actuel[l]->suivant1->etat] = actuel[l]->suivant1;
      if (tmp2[actuel[l]->suivant2->etat] == NULL ||
          tmp2[l]->poids > actuel[l]->suivant2->poids)
        tmp2[actuel[l]->suivant2->etat] = actuel[l]->suivant2;
    }
    for (int p = 0; p < 4; p++) actuel[p] = tmp2[p];
  }
  noeud* min = actuel[0];
  for (int p = 1; p < 4; p++) {
    if (min->poids > actuel[p]->poids) min = actuel[p];
  }
  while (min->precedent != NULL) {
    min->final = 1;
    min = min->precedent;
  }
  int* message = malloc(sizeof(int) * taille / 2);
  decoder(tete, message, taille / 2);

  return message;
}

void printWord(double* word, int len) {
  for (int i = 0; i < len; i++) {
    printf("%f ", word[i]);
  }
  printf("\n");
}
/*
int main(int argc, char const* argv[]) {
    if(argc!=1){
        printf("Syntaxe : ./%s",argv[0]);
    }
    srand((unsigned) time(NULL));
    double* word1 = getWord(0.0,1.0,4);
    double* word2 = getWord(0.0,1.0,6);
    printWord(word1,4);
    printWord(word2,6);
    return 0;
}
*/
int main(int argc, char const* argv[]) {
  /*if (argc != 2) {
    printf("./codeurViterbi <message>\n");
    exit(2);
  }
  int i = 0;
  for (; argv[1][i] != '\0'; i++)
    ;
  int code[i];
  for (int j = 0; j < i; j++) {
    if (argv[1][j] == '1')
      code[j] = 1;
    else
      code[j] = 0;
  }*/
  srand((unsigned)time(NULL));
  int i = 16;
  float code[i];
  for (int j = 0; j < i; j++) code[j] = randomizer(0.0, 1.0);
  ;

  int* message;
  message = decodeur(code, i);
  for (int j = 0; j < i / 2; j++) {
    printf("%d", message[j]);
  }
  printf("\n");
  free(message);

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
  for (int j = 0; j < i / 2; j++) {
    printf("%d", message[j]);
  }
  printf("\n");
  free(message);
  return 0;
}
