#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "helper.h"
#include "dynarrstr.h"

int isNumber(char * s)
{
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (isdigit(s[i]) == 0) return 0;
    }
    return 1;
}

char* read_file(char * filename) 
{
	char * buffer = 0;
	long length;
	FILE * f = fopen (filename, "rb");

	if (f)
	{
	  fseek (f, 0, SEEK_END);
	  length = ftell (f);
	  fseek (f, 0, SEEK_SET);
	  buffer = malloc (length);
	  if (buffer)
	  {
	    fread (buffer, 1, length, f);
	  }
	  fclose (f);
	}
	return buffer;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

int checkCsv(char * filename)
{
    return 1 ? strcmp(&filename[strlen(filename) - 4], ".csv") == 0 : 0;
}

ArrayStr tokenize(char * str, char delimeter)
{
	ArrayStr retVal;
    initArrayStr(&retVal, 2);
	char * token;
    while ((token = strsep(&str, &delimeter))) insertArrayStr(&retVal, trim(token));
	return retVal;
}

/* return 0 if true else 1 */
int contains(char * one, char * two)
{
	if (strlen(one) < strlen(two)) return 1;
	if (strcmp(one, two) == 0) return 0;
	int found;
	for (int i = 0; i < strlen(one) - strlen(two) + 1; i ++)
	{
		found = 1;
		for (int j = 0; j < strlen(two); j ++)
		{
			if (one[j + i] != two[j])
			{
				found = 0;
				break;
			}
		}
		if (found == 1) return 0;
	}
	return 1;
}