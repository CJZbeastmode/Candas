#ifndef DYNARRCHAR_H
#define DYNARRCHAR_H

typedef struct {
  char * array;
  size_t used;
  size_t size;
} ArrayChar;

void initArrayChar(ArrayChar *a, size_t initialSize);
void insertArrayChar(ArrayChar *a, char element);
void freeArrayChar(ArrayChar *a);
ArrayChar getWord(ArrayChar *a);

#endif