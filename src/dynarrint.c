#include <stdlib.h>
#include <stdio.h>
#include "dynarrint.h"

void initArrayInt(ArrayInt *a, size_t initialSize) 
{
  a->array = malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArrayInt(ArrayInt *a, int element) 
{
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void removeElementInt(ArrayInt *a, int position)
{
  for (;position < a->used - 1; position ++)
  {
    a->array[position] = a->array[position + 1];
  }
  a->array[a->used-- - 1] = 0;
}

void freeArrayInt(ArrayInt *a) 
{
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

size_t getArrayIntSize(ArrayInt a) 
{
  return a.used;
}