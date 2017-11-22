/*
 *@authors: Jederson Luz, Vit�ria Carvalho e Jo�o Victor
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_out.h"

typedef struct {
  char *word;
  int frequency;
}word;

char ** selectImportantWords (char **words, int size) {
  int i;
  for (i = 0; i < size; i++) {
	
  }
  return words;
}

void stringLwr(char *s) {
    int i=0;
    while(s[i]!='\0') {
        if(s[i]>='A' && s[i]<='Z') {
            s[i]=s[i]+32;
        }
        ++i;
    }
}

// Realoca os caracteres especiais que abre frases, tais como parenteses e aspas simples e duplas
void realocChar (char **words, int size) {
  int i, y, j;
  for (i = 0; i < size; i++) {
    for (y = 0; y < 30; y++) {
      if ((words[i][y] == '(') || (words[i][y] == '"') || (words[i][y] == '\'')) {
        for (j = 0; j < 30; j++) {
          words[i][j] = words[i][j+1];
          if (words[i][j] == '"')
            words[i][j] = '\0';
        }
      }
    }
    stringLwr(words[i]);
  }
}

void removeSpecialChar (char **words, int size) {
  int i, y;
  for (i = 0; i < size; i++) {
    for (y = 0; y < 30; y++) {
      if ((words[i][y] == '\n') || (words[i][y] == ':') || (words[i][y] == '.') || (words[i][y] == ',') || (words[i][y] == ';') || (words[i][y] == '!') || (words[i][y] == '?') || (words[i][y] == ')')) {
        if (!(((words[i][y-1] >= 48) && (words[i][y-1] <= 57)) && ((words[i][y+1] >= 48) && (words[i][y+1] <= 57))))
          words[i][y] = '\0';

        if (words[i][y] != ',')
          words[i][y] = '\0';

        if (words[i][y] == '\0')
          break;
      }
    }
  }

  realocChar(words, size);
}

char ** recoveryData (char **words, char *path, int size) {
  int i, y;
  FILE *newsFile = fopen(path, "r");
  words = malloc(size * sizeof(newsFile));
  for (i = 0; i < size; i++){
    words[i] = malloc(sizeof(30));
  }

  char *aux;

  for (i = 0; i < size; i++) {
    fscanf(newsFile, "%s ", words[i]);
  }

  fclose(newsFile);
  printf("Operação concluída com sucesso!\n");

  return words;
}

int main(int argc, char const *argv[]) {
  char **words, **importantWords;
  int i;

  //int option = str4int(input("Informe o tipo de conteúdo (1-website, 2-arquivo de texto puro): "));
  char *path = input("Informe o caminho para o website ou arquivo de texto: ");
  int size = str4int(input("Informe o tamanho do resumo (a quantidade de palavras): "));

  words = recoveryData(words, path, size);

  importantWords = malloc(size * sizeof(words));
  for (i = 0; i < size; i++){
    importantWords[i] = malloc(sizeof(30));
  }

  removeSpecialChar(words, size);

  for (i = 0; i < size; i++) {
    printf("%s\n", words[i]);
  }

  return 0;
}
