#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"
#include "dynarrstr.h"
#include "helper.h"

char ** sortAlphabetMemory;
char ** sortAlphabetTemp;

void mergingAlphabet(int low, int mid, int high, int index, int ascending) {
    int l1, l2, i;
   
    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        char * destroy1 = malloc(strlen(sortAlphabetMemory[l1]) + 1);
        char * destroy2 = malloc(strlen(sortAlphabetMemory[l2]) + 1);
        strcpy(destroy1, sortAlphabetMemory[l1]);
        strcpy(destroy2, sortAlphabetMemory[l2]);
        if (ascending == 1)
        {
            if (strcmp(tokenize(destroy1, ',').array[index], tokenize(destroy2, ',').array[index]) <= 0)
                sortAlphabetTemp[i] = sortAlphabetMemory[l1++];
            else
                sortAlphabetTemp[i] = sortAlphabetMemory[l2++];
        }
        else
        {
            // !!! if original order of same occurences is reversed, change >= to >
            if (strcmp(tokenize(destroy1, ',').array[index], tokenize(destroy2, ',').array[index]) >= 0)
                sortAlphabetTemp[i] = sortAlphabetMemory[l1++];
            else
                sortAlphabetTemp[i] = sortAlphabetMemory[l2++];
        }
        
        free(destroy1);
        free(destroy2);
    }

    while(l1 <= mid)    
        sortAlphabetTemp[i++] = sortAlphabetMemory[l1++];

    while(l2 <= high)   
        sortAlphabetTemp[i++] = sortAlphabetMemory[l2++];

    for(i = low; i <= high; i++)
        sortAlphabetMemory[i] = sortAlphabetTemp[i];
}

void sortAlphabetBackend(int low, int high, int index, int ascending) {
    int mid;

    if(low < high) {
        mid = (low + high) / 2;
        sortAlphabetBackend(low, mid, index, ascending);
        sortAlphabetBackend(mid+1, high, index, ascending);
        mergingAlphabet(low, mid, high, index, ascending);
    } else { 
        return;
    }   
}

ArrayStr sortAlphabetHelper(char ** arr, int length, int index, int ascending)
{
    sortAlphabetMemory = malloc(length * sizeof(char *));
    sortAlphabetTemp = malloc(length * sizeof(char *));
    for (int i = 0; i < length; i ++) sortAlphabetMemory[i] = arr[i];
    sortAlphabetBackend(0, length - 1, index, ascending);
    ArrayStr ret;
    initArrayStr(&ret, 2);
    for (int i = 0; i < length; i ++) insertArrayStr(&ret, sortAlphabetMemory[i]);
    free(sortAlphabetMemory);
    free(sortAlphabetTemp);
    return ret;
}