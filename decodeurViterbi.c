#include <stdio.h>
#include <stdlib.h>

typedef struct n {
  int code[2];
  int poids;
  int etat;
  struct n* precedent;
  struct n *suivant1, *suivant2;
  int final;
} noeud, *p_noeud;

noeud* nouveauNoeud(noeud* precedent, int* code, int indice, int etat,
                    int poids, int input, int* etatSuivant) {
  noeud* new = malloc(sizeof(struct n));
  new->poids = poids;
  new->final = 0;
  new->precedent = precedent;
  switch (etat) {
    case 0:
      if (!input) {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 0;
        new->code[1] = 0;
        *etatSuivant = 0;
        new->etat = 0;
      } else {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 1;
        new->code[1] = 1;
        *etatSuivant = 1;
        new->etat = 1;
      }
      break;
    case 1:
      if (!input) {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 1;
        new->code[1] = 0;
        *etatSuivant = 2;
        new->etat = 2;
      } else {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 0;
        new->code[1] = 1;
        *etatSuivant = 3;
        new->etat = 3;
      }
      break;
    case 2:
      if (!input) {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 1;
        new->code[1] = 1;
        *etatSuivant = 0;
        new->etat = 0;
      } else {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 0;
        new->code[1] = 0;
        *etatSuivant = 1;
        new->etat = 1;
      }
      break;
    case 3:
      if (!input) {
        if (code[indice] == 1) new->poids++;
        if (code[indice + 1] == 0) new->poids++;
        new->code[0] = 0;
        new->code[1] = 1;
        *etatSuivant = 2;
        new->etat = 2;
      } else {
        if (code[indice] == 0) new->poids++;
        if (code[indice + 1] == 1) new->poids++;
        new->code[0] = 1;
        new->code[1] = 0;
        *etatSuivant = 3;
        new->etat = 3;
      }
      break;
  }
  new->suivant1 = NULL;
  return new;
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

int* decodeur(int* code, int taille) {
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

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    printf("./decodeurViterbi <code>\n");
    exit(2);
  }
  FILE* f = fopen(argv[1], "r");
  int n1, n2;
  fscanf(f, "%d", &n1);
  int code1[n1];
  for (int i = 0; i < n1; i++) fscanf(f, "%d", &code1[i]);
  fscanf(f, "%d", &n2);
  int code2[n2];
  for (int i = 0; i < n2; i++) fscanf(f, "%d", &code2[i]);
  fclose(f);
  int* message;
  for (int j = 0; j < n1; j++) {
    printf("%d ", code1[j]);
  }
  message = decodeur(code1, n1);
  for (int j = 0; j < n1 / 2; j++) {
    printf("%d", message[j]);
  }
  printf("\n\n");
  free(message);

  for (int j = 0; j < n2; j++) {
    printf("%d ", code2[j]);
  }
  message = decodeur(code2, n2);
  for (int j = 0; j < n2 / 2; j++) {
    printf("%d", message[j]);
  }
  printf("\n\n");
  free(message);
  return 0;
}
