#include <stdio.h>
#include <stdlib.h>

char * input (char *message) {
  char *valor = malloc(255);
  printf("%s", message);
  setbuf(stdin, NULL);
  scanf("%[^\n]s", valor);
  return valor;
}

int str4int (char *message) {
  int valor = atoi(message);
  return valor;
}

float str4float (char *message) {
  float valor = atof(message);
  return valor;
}

void sysPause (char *message) {
  printf("%s", message);
  setbuf(stdin, NULL);
  getchar();
}

int invertInt (int number) {
  int numberInverted = 0;
  while (number > 0) {
    numberInverted *= 10;
    numberInverted += number % 10;
    number /= 10;
  }
  return numberInverted;
}

void bubbleSortInt(int *vector, int size) {
  int i, j, aux;

  for(i = 0; i < size; i++) {
    for(j = i+1; j < size; j++) {
      if(vector[j] < vector[i]) {
        aux = vector[i];
        vector[i] = vector[j];
        vector[j] = aux;
      }
    }
  }
}

void selctionSortInt(int *vector, int size) {
  int i, j, min, aux;

  for (i = 0; i < (size-1); i++) {
    min = i;
    for (j = (i+1); j < size; j++) {
      if(vector[j] < vector[min])
        min = j;
    }
    if (vector[i] != vector[min]) {
      aux = vector[i];
      vector[i] = vector[min];
      vector[min] = aux;
    }
  }
}

void inserctionSortInt(int *vector, int size) {
  int i, j, aux;

  for (i = 0; i < size; i++) {
    aux = vector[i];
    j = i - 1;
    while ((j >= 0) && (aux < vector[j])) {
      vector[j+1] = vector[j];
      j--;
    }
    vector[j+1] = aux;
  }
}
