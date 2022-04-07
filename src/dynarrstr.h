#ifndef DYNARRSTR_H
#define DYNARRSTR_H

typedef struct {
  char **array;
  size_t used;
  size_t size;
} ArrayStr;

void initArrayStr(ArrayStr *a, size_t initialSize);
void insertArrayStr(ArrayStr *a, char* element);
void freeArrayStr(ArrayStr *a);
size_t getArrayStrSize(ArrayStr a);
void removeElementStr(ArrayStr *a, int position);

#endif