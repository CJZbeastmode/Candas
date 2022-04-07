#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynarrstr.h"

void initArrayStr(ArrayStr *a, size_t initialSize) 
{
  a->array = malloc(initialSize * sizeof(char *));
  a->used = 0;
  a->size = initialSize;
}

void insertArrayStr(ArrayStr *a, char* element) 
{
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char *));
  }
  a->array[a->used++] = element;
}

void removeElementStr(ArrayStr *a, int position)
{
  for (;position < a->used - 1; position ++)
  {
    a->array[position] = a->array[position + 1];
  }
  a->array[a->used-- - 1] = "\0";
}

void freeArrayStr(ArrayStr *a) 
{
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

size_t getArrayStrSize(ArrayStr a) 
{
  return a.used;
}