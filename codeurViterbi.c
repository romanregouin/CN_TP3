#include <stdio.h>
#include <stdlib.h>

int* codeur(int* message, int taille) {
  int etat = 0;
  int* code = malloc(sizeof(int) * taille * 2);
  for (int j = 0; j < taille; j++) {
    switch (etat) {
      case 0:
        if (message[j] == 1) {
          code[2 * j] = 1;
          code[2 * j + 1] = 1;
          etat = 1;
        } else {
          code[2 * j] = 0;
          code[2 * j + 1] = 0;
          etat = 0;
        }

        break;
      case 1:
        if (message[j] == 1) {
          code[2 * j] = 0;
          code[2 * j + 1] = 1;
          etat = 3;
        } else {
          code[2 * j] = 1;
          code[2 * j + 1] = 0;
          etat = 2;
        }
        break;
      case 2:
        if (message[j] == 1) {
          code[2 * j] = 0;
          code[2 * j + 1] = 0;
          etat = 1;
        } else {
          code[2 * j] = 1;
          code[2 * j + 1] = 1;
          etat = 0;
        }
        break;
      case 3:
        if (message[j] == 1) {
          code[2 * j] = 1;
          code[2 * j + 1] = 0;
          etat = 3;
        } else {
          code[2 * j] = 0;
          code[2 * j + 1] = 1;
          etat = 2;
        }
        break;
      default:
        printf("Erreur, ne devrait jamais passer ici\n");
        exit(3);
    }
  }
  return code;
}

int main(int argc, char const* argv[]) {
  if (argc != 2) {
    printf("./codeurViterbi <message>\n");
    exit(2);
  }
  int i = 0;
  for (; argv[1][i] != '\0'; i++)
    ;
  int message[i];
  for (int j = 0; j < i; j++) {
    if (argv[1][j] == '1')
      message[j] = 1;
    else
      message[j] = 0;
  }
  int* code;
  code = codeur(message, i);
  for (int j = 0; j < 2 * i; j++) {
    printf("%d", code[j]);
  }
  printf("\n");
  free(code);
  return 0;
}
