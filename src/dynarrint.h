#ifndef DYNARRINT_H
#define DYNARRINT_H

typedef struct {
  int *array;
  size_t used;
  size_t size;
} ArrayInt;

void initArrayInt(ArrayInt *a, size_t initialSize);
void insertArrayInt(ArrayInt *a, int element);
void removeElementInt(ArrayInt *a, int position);
void freeArrayInt(ArrayInt *a);
size_t getArrayIntSize(ArrayInt a);

#endif