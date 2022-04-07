#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sort.h"
#include "dynarrstr.h"
#include "helper.h"

char ** sortNumberMemory;
char ** sortNumberTemp;

void mergingNumber(int low, int mid, int high, int index, int ascending) {
    int l1, l2, i;

    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        char * destroy1 = malloc(strlen(sortNumberMemory[l1]) + 1);
        char * destroy2 = malloc(strlen(sortNumberMemory[l2]) + 1);
        strcpy(destroy1, sortNumberMemory[l1]);
        strcpy(destroy2, sortNumberMemory[l2]);
        if (ascending == 1)
        {
            if (strtol(tokenize(destroy1, ',').array[index], NULL, 10) <= strtol(tokenize(destroy2, ',').array[index], NULL, 10))
                sortNumberTemp[i] = sortNumberMemory[l1++];
            else
                sortNumberTemp[i] = sortNumberMemory[l2++];
        }
        else
        {
            // !!! if original order of same occurences is reversed, change >= to >
            if (strtol(tokenize(destroy1, ',').array[index], NULL, 10) >= strtol(tokenize(destroy2, ',').array[index], NULL, 10))
                sortNumberTemp[i] = sortNumberMemory[l1++];
            else
                sortNumberTemp[i] = sortNumberMemory[l2++];
        }

        free(destroy1);
        free(destroy2);
    }

    while(l1 <= mid)    
        sortNumberTemp[i++] = sortNumberMemory[l1++];

    while(l2 <= high)   
        sortNumberTemp[i++] = sortNumberMemory[l2++];

    for(i = low; i <= high; i++)
        sortNumberMemory[i] = sortNumberTemp[i];
}

void sortNumberBackend(int low, int high, int index, int ascending) {
    int mid;

    if(low < high) {
        mid = (low + high) / 2;
        sortNumberBackend(low, mid, index, ascending);
        sortNumberBackend(mid+1, high, index, ascending);
        mergingNumber(low, mid, high, index, ascending);
    } else { 
        return;
    }   
}

ArrayStr sortNumberHelper(char ** arr, int length, int index, int ascending)
{
    sortNumberMemory = malloc(length * sizeof(char *));
    sortNumberTemp = malloc(length * sizeof(char *));
    for (int i = 0; i < length; i ++) sortNumberMemory[i] = arr[i];
    sortNumberBackend(0, length - 1, index, ascending);
    ArrayStr ret;
    initArrayStr(&ret, 2);
    for (int i = 0; i < length; i ++) insertArrayStr(&ret, sortNumberMemory[i]);
    free(sortNumberMemory);
    free(sortNumberTemp);
    return ret;
}