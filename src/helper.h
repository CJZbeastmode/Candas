#ifndef HELPER_H
#define HELPER_H
#include "dynarrstr.h"

int isNumber(char * s);
char* read_file(char * filename);
char* trim(char * s);
int checkCsv(char * filename);
ArrayStr tokenize(char * str, char delimeter);
int contains(char * one, char * two);

#endif