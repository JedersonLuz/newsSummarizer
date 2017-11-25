/*
 *@authors: Jederson Luz, Vit�ria Carvalho e Jo�o Victor
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "in_out.h"

typedef struct {
  char word[20];
  int frequency;
}Word;

Word * insertionSortWords (Word *importantWords, int countWords);

Word * selectImportantWords (char **words, int size);

void stringLwr(char *s);

void realocChar (char **words, int size);

void removeSpecialChar (char **words, int size);

char ** recoveryData (char **words, char *path, int size);

int main(int argc, char const *argv[]) {
  char **words;
  Word *importantWords = malloc(sizeof(Word));
  int i;

  //int option = str4int(input("Informe o tipo de conteúdo (1-website, 2-arquivo de texto puro): "));
  char *path = input("Informe o caminho para o arquivo de texto: ");
  int sizeResume = str4int(input("Informe o tamanho do resumo (a quantidade de palavras): "));

  int size = determineSize(path);

  words = recoveryData(words, path, size);

  removeSpecialChar(words, size);

  importantWords = selectImportantWords(words, size);

  printf("\n");
  for (i = 0; i < sizeResume; i++) {
    printf("%s | %d\n", importantWords[i].word, importantWords[i].frequency);
  }
  printf("\n");

  return 0;
}

Word * insertionSortWords (Word *importantWords, int countWords) {
  int i, y;
  Word aux;

  for(i = 1; i < countWords; i++) {
    y = i;

    while((y != 0) && (importantWords[y].frequency > importantWords[y - 1].frequency)) {
      aux = importantWords[y];
      importantWords[y] = importantWords[y - 1];
      importantWords[y - 1] = aux;
      y--;
    }
  }

  return importantWords;
}

int determineSize (char *path) {
  int i;
  FILE *newsFile = fopen(path, "r");
  char words[30];

  for (i = 0; !feof(newsFile); i++) {
    fscanf(newsFile, "%s ", words);
  }

  fclose(newsFile);

  return i+1;
}

Word * selectImportantWords (char **words, int size) {
  int i, y, flag, countWords = 0, k;
  Word *importantWords = malloc(sizeof(Word)*200);
  char **stopWords;
  stopWords = recoveryData(stopWords, "stopWords.txt", 82);

  for (i = 0; i < size; i++) {
    for (y = 0; y < 82; y++) {
      flag = strcmp(words[i], stopWords[y]);
      if (flag == 0){
        break;
      }
    }
    if (flag != 0) {
      int existe = 0;
      for (k=0; k<countWords; k++) {
        if ((strcmp(importantWords[k].word,words[i]))==0) {
          importantWords[k].frequency++;
          existe = 1;
          break;
        }
      }
      if (existe==0) {
        strcpy(importantWords[countWords].word,words[i]);
        importantWords[countWords].frequency = 1;
        countWords++;
      }
    }
  }

  importantWords = insertionSortWords(importantWords, countWords);

  return importantWords;
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
  int i;
  FILE *newsFile = fopen(path, "r");
  words = malloc(size * sizeof(newsFile));
  for (i = 0; i < size; i++){
    words[i] = malloc(sizeof(30));
  }

  for (i = 0; i < size; i++) {
    fscanf(newsFile, "%s ", words[i]);
  }

  fclose(newsFile);

  return words;
}
