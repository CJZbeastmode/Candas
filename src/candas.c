#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "candas.h"
#include "helper.h"
#include "dynarrstr.h"
#include "dynarrint.h"
#include "dynarrchar.h"
#include "sort.h"

ArrayStr toSort;
ArrayStr toSortcp;
ArrayInt toSortInt;
ArrayInt toSortIntcp;

void read_csv(Dataframe * df, char * filename)
{
    if (checkCsv(filename) == 0) exit(EXIT_FAILURE);
    char * content = read_file(filename);
    char * contentcpy = read_file(filename);
    char * colline = strtok(contentcpy, "\n");
    char * token;

    // Split columns into array and store
    ArrayStr columns;
    initArrayStr(&columns, 2);
    while ((token = strsep(&colline, ","))) insertArrayStr(&columns, trim(token));
    df->columns = columns;

    // Split data into array and store
    ArrayStr data;
    initArrayStr(&data, 2);
    while ((token = strsep(&content, "\n"))) insertArrayStr(&data, trim(token));
    removeElementStr(&data, 0);
    df->data = data;
}

Dataframe head(Dataframe df, int n) 
{
    if (n >= df.data.used) return df;
    Dataframe retDf;
    retDf.columns = df.columns;
    ArrayStr retArray;
    initArrayStr(&retArray, n);
    for (int i = 0; i < n; i ++) insertArrayStr(&retArray, df.data.array[i]);
    retDf.data = retArray;
    return retDf;
}

Dataframe tail(Dataframe df, int n) 
{
    if (n >= df.data.used) return df;
    Dataframe retDf;
    retDf.columns = df.columns;
    ArrayStr retArray;
    initArrayStr(&retArray, n);
    for (int i = df.data.used - n; i < df.data.used; i ++) insertArrayStr(&retArray, df.data.array[i]);
    retDf.data = retArray;
    return retDf;
}

Dataframe loc(Dataframe df, ArrayStr col_names, ArrayInt row_values) 
{
    Dataframe retDf;

    if (row_values.used == 0) retDf.data = df.data;
    else {
        ArrayStr retDfData; 
        initArrayStr(&retDfData, 2);
        int curRow;
        for (int i = 0; i < row_values.used; i ++) 
        {
            curRow = row_values.array[i];
            if (curRow >= df.data.used) 
            {
                printf("Row %d does not exist. Ignored.\n", curRow);
                continue;
            }
            insertArrayStr(&retDfData, df.data.array[row_values.array[i]]);
        }
        retDf.data = retDfData;
    }
    if (col_names.used == 0)
    {
        retDf.columns = df.columns;
        return retDf;
    }

    // Check whether column exists
    int exists;
    int index = 0;
    ArrayInt indices;
    int curInd;
    initArrayInt(&indices, col_names.used);

    for (int i = 0; i < col_names.used; i ++) 
    {
        exists = 0;
        curInd = -1;
        for (int j = 0; j < df.columns.used; j ++) 
        {
            if (strcmp(df.columns.array[j], col_names.array[i]) == 0) 
            {
                exists = 1;
                curInd = j;
                break;
            }
        }
        if (exists == 0) 
        {
            printf("Not all the columns exist!");
            exit(EXIT_FAILURE);
        }
        insertArrayInt(&indices, curInd);
    }

    // loop column
    ArrayStr retDfColumns; 
    initArrayStr(&retDfColumns, 2);
    for (int i = 0; i < col_names.used; i ++) 
    {
        insertArrayStr(&retDfColumns, col_names.array[i]);
    }
    retDf.columns = retDfColumns;

    // pick out data
    ArrayStr resDat;
    initArrayStr(&resDat, retDf.data.used);
    for (int i = 0; i < retDf.data.used; i ++)
    {
        ArrayStr tmp = tokenize(retDf.data.array[i], ',');
        
        ArrayStr mod;
        initArrayStr(&mod, indices.used);
        for (int j = 0; j < indices.used; j ++) insertArrayStr(&mod, tmp.array[indices.array[j]]);
        
        ArrayChar res;
        initArrayChar(&res, 2);
        for (int j = 0; j < mod.used; j ++)
        {
            char * word = mod.array[j];
            for (int i = 0; i < strlen(word); i ++) insertArrayChar(&res, word[i]);
            if (j != mod.used - 1)
            {
                insertArrayChar(&res, ',');
                insertArrayChar(&res, ' ');
            }
        }
        insertArrayStr(&resDat, getWord(&res).array);
    }
    retDf.data = resDat;
    return retDf;
}

Dataframe editField(Dataframe df, char * col_name, int row_value, char * key) 
{
    // find col index
    int exists = 0;
    int index;
    for (int i = 0; i < df.columns.used; i ++)
    {
        if (strcmp(col_name, df.columns.array[i]) == 0) 
        {
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0)
    {
        printf("Column does not exist!\n");
        exit(EXIT_FAILURE);
    }
    
    // get row
    if (row_value >= df.data.used)
    {
        printf("Row does not exist!\n");
        exit(EXIT_FAILURE);
    }
    char * mod = df.data.array[row_value];
    ArrayStr tokenized = tokenize(mod, ',');
    ArrayChar line;
    initArrayChar(&line, 2);
    for (int i = 0; i < tokenized.used; i ++)
    {
        char * cp = i == index ? key : tokenized.array[i];
        for (int j = 0; j < strlen(cp); j ++)
        {
            insertArrayChar(&line, cp[j]);
        }
        if (i != tokenized.used - 1) insertArrayChar(&line, ',');
    }
    df.data.array[row_value] = getWord(&line).array;
    return df;
}

Dataframe deleteRow(Dataframe df, int row_value) 
{
    if (row_value >= df.data.used)
    {
        printf("Row does not exist! No changes made.\n");
        exit(EXIT_FAILURE);
    }
    removeElementStr(&(df.data), row_value);
    return df;
}

Dataframe deleteRows(Dataframe df, ArrayInt row_values) 
{
    // TODO: sort row_values
    for (int i = 0; i < row_values.used; i ++)
    {
        if (row_values.array[i] >= df.data.used)
        {
            printf("Row %d does not exist!\n", row_values.array[i]);
            continue;
        }
        removeElementStr(&(df.data), row_values.array[i]);
        for (int j = 0; j < row_values.used; j ++) row_values.array[j] --;
    }
    return df;
}

Dataframe deleteCol(Dataframe df, char * col_name)
{  
    // find col index
    int exists = 0;
    int index;
    for (int i = 0; i < df.columns.used; i ++)
    {
        if (strcmp(col_name, df.columns.array[i]) == 0) 
        {
            exists = 1;
            index = i;
            break;
        }
    }

    if (exists == 0)
    {
        printf("Column does not exist!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < df.data.used; i ++)
    {
        char * mod = df.data.array[i];
        ArrayStr tokenized = tokenize(mod, ',');
        removeElementStr(&tokenized, index);
        ArrayChar line;
        initArrayChar(&line, 2);
        for (int j = 0; j < tokenized.used; j ++)
        {
            for (int k = 0; k < strlen(tokenized.array[j]); k ++)
            {
                insertArrayChar(&line, tokenized.array[j][k]);
            }
            if (j != tokenized.used - 1) insertArrayChar(&line, ',');
        }
        df.data.array[i] = getWord(&line).array;
    }

    removeElementStr(&(df.columns), index);
    return df;
}

Dataframe deleteCols(Dataframe df, ArrayStr col_names) 
{
    for (int i = 0; i < col_names.used; i ++) df = deleteCol(df, col_names.array[i]);
    return df;
}

Dataframe addRows(Dataframe df, int n) 
{
    int size = df.columns.used;
    ArrayChar commas;
    initArrayChar(&commas, size);
    int i;
    for (i = 0; i < size - 1; i ++) insertArrayChar(&commas, ',');
    for (i = 0; i < n; i ++) insertArrayStr(&(df.data), getWord(&commas).array);
    return df;
}

Dataframe addCol(Dataframe df, char * col_name) 
{
    insertArrayStr(&(df.columns), col_name);
    for (int i = 0; i < df.data.used; i ++) 
    {
        ArrayChar ac;
        initArrayChar(&ac, 2);
        for (int j = 0; j < strlen(df.data.array[i]); j ++) insertArrayChar(&ac, df.data.array[i][j]);
        insertArrayChar(&ac, ',');
        char * res = getWord(&ac).array;
        df.data.array[i] = res;
    }
    return df;
}

int getRowNumbers(Dataframe df)
{
    return df.data.used;
}

ArrayStr getColumnNames(Dataframe df)
{
    ArrayStr ret;
    initArrayStr(&ret, df.columns.used);
    for (int i = 0; i < df.columns.used; i ++) insertArrayStr(&ret, df.columns.array[i]);
    return ret;
}

void printColumnNames(Dataframe df)
{
    for (int i = 0; i < df.columns.used; i ++) printf("%s,", df.columns.array[i]);
    printf("\b \b\n");
}

void printRow(Dataframe df, int row_value) 
{
    printColumnNames(df);
    printf("%s\n", df.data.array[row_value < df.data.used ? row_value : df.data.used - 1]);
}

void printdf(Dataframe df) 
{
    printColumnNames(df);
    for (int i = 0; i < df.data.used; i ++) printf("%s\n", df.data.array[i]);
}

Dataframe sortAlphabetical(Dataframe df, char * credential, int ascending) 
{
    // find col index
    int exists = 0;
    int index;
    for (int i = 0; i < df.columns.used; i ++)
    {
        if (strcmp(credential, df.columns.array[i]) == 0) 
        {
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0)
    {
        printf("Column does not exist!\n");
        exit(EXIT_FAILURE);
    }

    char ** toSort = malloc(df.data.used);
    for (int i = 0; i < df.data.used; i ++) toSort[i] = df.data.array[i];
    ArrayStr res = sortAlphabetHelper(toSort, df.data.used, index, ascending);
    df.data = res;
    free(toSort);
    return df;
}

Dataframe sortNumerical(Dataframe df, char * credential, int ascending) 
{
    // find col index
    int exists = 0;
    int index;
    for (int i = 0; i < df.columns.used; i ++)
    {
        if (strcmp(credential, df.columns.array[i]) == 0) 
        {
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0)
    {
        printf("Column does not exist!\n");
        exit(EXIT_FAILURE);
    }
    
    // Check whether is number
    for (int i = 0; i < df.data.used; i ++)
    {
        char mod[strlen(df.data.array[i])];
        strcpy(mod, df.data.array[i]);

        ArrayStr tokenized = tokenize(mod, ',');
        if (isNumber(tokenized.array[index]) == 0)
        {
            printf("The datatype of this column is not number!");
            exit(EXIT_FAILURE);
        }
    }

    char ** toSort = malloc(df.data.used);
    for (int i = 0; i < df.data.used; i ++) toSort[i] = df.data.array[i];
    ArrayStr res = sortNumberHelper(toSort, df.data.used, index, ascending);
    df.data = res;
    free(toSort);
    return df;

}

void export(Dataframe df, char * filename) 
{
    FILE * f = fopen(filename, "w");
    for (int i = 0; i < df.columns.used; i ++)
    {
        fputs(df.columns.array[i], f);
        if (i != df.columns.used - 1) fputs(", ", f);
    }
    fputs("\n", f);
    for (int i = 0; i < df.data.used; i ++)
    {
        fputs(df.data.array[i], f);
        if (i != df.columns.used) fputs("\n", f);
    }
}

Dataframe filter_number(Dataframe df, char * col_name, long key, int compare) 
{
    Dataframe ret;

    // find col index
    int exists = 0;
    int index;
    for (int i = 0; i < df.columns.used; i ++)
    {
        if (strcmp(col_name, df.columns.array[i]) == 0) 
        {
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0)
    {
        printf("Column does not exist!\n");
        exit(EXIT_FAILURE);
    }

    // Create Return Dataframe
    ArrayStr cpcolumns;
    initArrayStr(&cpcolumns, df.columns.used);
    for (int i = 0; i < df.columns.used; i ++) insertArrayStr(&cpcolumns, df.columns.array[i]);
    ret.columns = cpcolumns;

    // Filter
    ArrayStr filterRows;
    initArrayStr(&filterRows, 2);

    int premise;
    for (int i = 0; i < df.data.used; i ++)
    {
        char mod[strlen(df.data.array[i])];
        char modDestroy[strlen(df.data.array[i])];
        strcpy(mod, df.data.array[i]);
        strcpy(modDestroy, mod);
        ArrayStr tokenized = tokenize(modDestroy, ',');
        if (isNumber(tokenized.array[index]) == 0)
        {
            printf("The datatype of this column is not number!");
            exit(EXIT_FAILURE);
        }
        long curNum = strtol(tokenized.array[index], NULL, 10);

        premise = compare == 0 ? curNum == key : compare < 0 ? curNum < key : curNum > key;

        ArrayChar tmp; 
        initArrayChar(&tmp, strlen(mod));
        for (int j = 0; j < strlen(mod); j ++) insertArrayChar(&tmp, mod[j]);
        char * modAdd = getWord(&tmp).array;
        if (premise == 1) 
        {
            ArrayChar tmp; 
            initArrayChar(&tmp, strlen(mod));
            for (int j = 0; j < strlen(mod); j ++) insertArrayChar(&tmp, mod[j]);
            char * modAdd = getWord(&tmp).array;
            insertArrayStr(&filterRows, modAdd);
        }
    }
    ret.data = filterRows;
    return ret;
}

Dataframe filter_string(Dataframe df, char * col_name, char * key, int exact_or_contains) 
{
    Dataframe ret;

    // find col index
    int exists = 0;
    int index;
    for (int i = 0; i < df.columns.used; i ++)
    {
        if (strcmp(col_name, df.columns.array[i]) == 0) 
        {
            exists = 1;
            index = i;
            break;
        }
    }
    if (exists == 0)
    {
        printf("Column does not exist!\n");
        exit(EXIT_FAILURE);
    }

    // Create Return Dataframe
    ArrayStr cpcolumns;
    initArrayStr(&cpcolumns, df.columns.used);
    for (int i = 0; i < df.columns.used; i ++) insertArrayStr(&cpcolumns, df.columns.array[i]);
    ret.columns = cpcolumns;

    // Filter
    ArrayStr filterRows;
    initArrayStr(&filterRows, 2);

    int premise;
    for (int i = 0; i < df.data.used; i ++)
    {
        char mod[strlen(df.data.array[i])];
        char modDestroy[strlen(df.data.array[i])];
        strcpy(mod, df.data.array[i]);
        strcpy(modDestroy, mod);
        ArrayStr tokenized = tokenize(modDestroy, ',');
        premise = exact_or_contains == 0 ? strcmp(tokenized.array[index], key) : contains(tokenized.array[index], key);
        if (premise == 0) 
        {
            ArrayChar tmp; 
            initArrayChar(&tmp, strlen(mod));
            for (int j = 0; j < strlen(mod); j ++) insertArrayChar(&tmp, mod[j]);
            char * modAdd = getWord(&tmp).array;
            insertArrayStr(&filterRows, modAdd);
        }
    }
    ret.data = filterRows;
    return ret;
}