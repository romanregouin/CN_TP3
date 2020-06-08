#include <stdio.h>
#include <stdlib.h>

typedef struct n {
  int code[2];
  int poids;
  int debut;
  struct n* suivant;
} noeud, *p_noeud;

noeud* nouveauNoeud(int* code, int indice, int etat, int poids, int input,
                    int* etatSuivant, int debut) {
  noeud* new = malloc(sizeof(struct n));
  new->poids = poids;
  new->debut = debut;
  switch (etat) {
    case 0:
      if (!input) {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 0;
        new->code[1] = 0;
        *etatSuivant = 0;
      } else {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 1;
        new->code[1] = 1;
        *etatSuivant = 1;
      }
      break;
    case 1:
      if (!input) {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 1;
        new->code[1] = 0;
        *etatSuivant = 2;
      } else {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 0;
        new->code[1] = 1;
        *etatSuivant = 3;
      }
      break;
    case 2:
      if (!input) {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 1;
        new->code[1] = 1;
        *etatSuivant = 0;
      } else {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 0;
        new->code[1] = 0;
        *etatSuivant = 1;
      }
      break;
    case 3:
      if (!input) {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 0;
        new->code[1] = 1;
        *etatSuivant = 2;
      } else {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 1;
        new->code[1] = 0;
        *etatSuivant = 3;
      }
      break;
  }
  new->suivant = NULL;
  return new;
}

void decoder(noeud* n, int etat, int* m, int taille) {
  for (int j = 1; j < taille; j++) {
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

int* decodeur(int* code, int taille) {
  noeud *debut[2], *debut2[4];
  noeud* actuel[4];
  noeud* new = malloc(sizeof(struct n));
  new->code[0] = 0;
  new->code[1] = 0;
  debut[0] = new;
  new = malloc(sizeof(struct n));
  new->code[0] = 1;
  new->code[1] = 1;
  debut[1] = new;
  if (code[0] == 1)
    debut[0]->poids++;
  else
    debut[1]->poids++;
  if (code[1] == 1)
    debut[0]->poids++;
  else
    debut[1]->poids++;
  new = malloc(sizeof(struct n));
  new->code[0] = 0;
  new->code[1] = 0;
  new->poids += debut[0]->poids;
  new->debut = 0;
  actuel[0] = new;
  new = malloc(sizeof(struct n));
  new->code[0] = 1;
  new->code[1] = 1;
  new->poids += debut[0]->poids;
  new->debut = 1;
  actuel[1] = new;
  new = malloc(sizeof(struct n));
  new->code[0] = 1;
  new->code[1] = 0;
  new->poids += debut[1]->poids;
  new->debut = 2;
  actuel[2] = new;
  new = malloc(sizeof(struct n));
  new->code[0] = 0;
  new->code[1] = 1;
  new->poids += debut[1]->poids;
  new->debut = 3;
  actuel[3] = new;
  if (code[2] == 1) {
    actuel[0]->poids++;
    actuel[3]->poids++;
  } else {
    actuel[1]->poids++;
    actuel[2]->poids++;
  }
  if (code[3] == 1) {
    actuel[0]->poids++;
    actuel[2]->poids++;
  } else {
    actuel[1]->poids++;
    actuel[3]->poids++;
  }
  debut2[0] = actuel[0];
  debut2[1] = actuel[1];
  debut2[2] = actuel[2];
  debut2[3] = actuel[3];
  for (int j = 2; j < (taille / 2); j++) {
    noeud* tmp;
    int indice = 0;
    for (int k = 0; k < 4; k++) {
      tmp = nouveauNoeud(code, j * 2, k, actuel[k]->poids, 0, &indice,
                         actuel[indice]->debut);
      if (actuel[indice]->suivant == NULL ||
          actuel[indice]->suivant->poids > tmp->poids)
        actuel[indice]->suivant = tmp;
      tmp = nouveauNoeud(code, j * 2, k, actuel[k]->poids, 1, &indice,
                         actuel[indice]->debut);
      if (actuel[indice]->suivant == NULL ||
          actuel[indice]->suivant->poids > tmp->poids)
        actuel[indice]->suivant = tmp;
    }
    for (int l = 0; l < 4; l++) actuel[l] = actuel[l]->suivant;
  }
  noeud* min = actuel[0];
  for (int p = 1; p < 4; p++) {
    if (min->poids > actuel[p]->poids) min = actuel[p];
  }
  int* message = malloc(sizeof(int) * taille / 2);
  if (min->debut == 0 || min->debut == 1)
    message[0] = 0;
  else
    message[0] = 1;

  decoder(debut2[min->debut], min->debut, message, taille / 2);

  return message;
}

int main(int argc, char const* argv[]) {
  if (argc != 2) {
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
  }
  int* message;
  message = decodeur(code, i);
  for (int j = 0; j < i / 2; j++) {
    printf("%d", message[j]);
  }
  printf("\n");
  free(message);
  return 0;
}
