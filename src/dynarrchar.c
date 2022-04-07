#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynarrchar.h"

void initArrayChar(ArrayChar *a, size_t initialSize) 
{
  a->array = malloc(initialSize * sizeof(char *));
  a->used = 0;
  a->size = initialSize;
}

void insertArrayChar(ArrayChar *a, char element) 
{
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char *));
  }
  a->array[a->used++] = element;
}

void freeArrayChar(ArrayChar *a) 
{
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

ArrayChar getWord(ArrayChar *a)
{
  ArrayChar ret;
  initArrayChar(&ret, a->used);
  for (int i = 0; i < a->used; i ++)
  {
    insertArrayChar(&ret, a->array[i]);
  }
  return ret;
}