#ifndef DATAFRAME_H
#define DATAFRAME_H
#include "dynarrstr.h"
#include "dynarrint.h"
#include "dynarrchar.h"
#include "helper.h"
#include "sort.h"

typedef struct 
{
    ArrayStr data;
    ArrayStr columns;
} Dataframe;

/* 
    Create a dataframe based on a csv file.
    :param *df: pointer of an empty dataframe object
    :param filename: the filename (with its path if necessary)
    :returns: void
*/
void read_csv(Dataframe * df, char * filename);

/* 
    Show the first n rows of data.
    :param df: a dataframe object
    :param n: the number of rows to be shown
    :returns: the modified dataframe
*/
Dataframe head(Dataframe df, int n);

/* 
    Show the last n rows of data.
    :param df: a dataframe object
    :param n: the number of rows to be shown
    :returns: the modified dataframe
*/
Dataframe tail(Dataframe df, int n);

/* 
    Locate the dataframe based on columns and rows.
    :param df: a dataframe object
    :param col_names: a dynamic string array of column names 
    :param row_values: a dynamic integer array of row values
    :returns: the modified dataframe
*/
Dataframe loc(Dataframe df, ArrayStr col_names, ArrayInt row_values);

/*
    Allow users to edit a specific field of the dataframe.
    :param df: a dataframe object
    :param col_name: the column name (all columns if empty)
    :param row_value: the row number (all rows if empty)
    :param key: the modified string
    :return: the modified dataframe
*/
Dataframe editField(Dataframe df, char * col_name, int row_value, char * key);

/*
    Delete a specific row from the dataframe.
    :param df: a dataframe object
    :param row_value: the row that user requests to delete
    :return: the modified dataframe
*/
Dataframe deleteRow(Dataframe df, int row_value);

/*
    Delete specific rows from the dataframe.
    :param df: a dataframe object
    :param row_values: a dynamic integer array of row numbers that user requests to delete
    :return: the modified dataframe
*/
Dataframe deleteRows(Dataframe df, ArrayInt row_names);

/*
    Delete a specific column from the dataframe.
    :param df: a dataframe object
    :param col_name: the column that user requests to delete
    :return: the modified dataframe
*/
Dataframe deleteCol(Dataframe df, char * col_name);

/*
    Delete specific columns from the dataframe.
    :param df: a dataframe object
    :param col_names: a dynamic string array of column names that user requests to delete
    :return: the modified dataframe
*/
Dataframe deleteCols(Dataframe df, ArrayStr col_names);

/*
    Add n lines of rows with initialied empty values.
    :param df: a dataframe object
    :param n: number of rows that user requests to append to the dataframe
    :return: the modified dataframe
*/
Dataframe addRows(Dataframe df, int n);

/*
    Add a column named col_name with initialied empty values.
    :param df: a dataframe object
    :param col_name: the name of the column that user requests to add
    :return: the modified dataframe
*/
Dataframe addCol(Dataframe df, char * col_name);

/*
    Print a specific row.
    :param df: a dataframe object
    :param row_value: the row number
    :return: void
*/
void printRow(Dataframe df, int row_value);

/*
    Print the entire dataframe.
    :param df: a dataframe object
    :return: void
*/
void printdf(Dataframe df);

/*
    Print all the column names of the given dataframe.
    :param df: a dataframe object
    :return: void
*/
void printColumnNames(Dataframe df);

/*
    Sort a dataframe by a specific credential in alphabetical order.
    :param df: a dataframe object
    :param credential: a column name
    :ascending: 1 for sorting in an ascending order, others for descending
    :return: the modified dataframe
*/
Dataframe sortAlphabetical(Dataframe df, char * credential, int ascending);

/*
    Sort a dataframe by a specific credential in numerical order.
    :param df: a dataframe object
    :param credential: a column name
    :ascending: 1 for sorting in an ascending order, others for descending
    :return: the modified dataframe
*/
Dataframe sortNumerical(Dataframe df, char * credential, int ascending);

/*
    Export a dataframe to a csv file.
    :param df: a dataframe object
    :param filename: the filename (including path if necessary)
    :return: void
*/
void export(Dataframe df, char * filename);

/*
    Filter a dataframe by a specific criteria numerically.
    :param df: a dataframe object
    :param col_name: a column name
    :key: the query key
    :compare: 0 for exact match, <0 for less and >0 for more
*/
Dataframe filter_number(Dataframe df, char * col_name, long key, int compare);

/*
    Filter a dataframe using strings by a specific criteria.
    :param df: a dataframe object
    :param col_name: a column name
    :key: the query key
    :compare: 0 for exact match, else for contains
*/
Dataframe filter_string(Dataframe df, char * col_name, char * key, int exact_or_contains);

/*
    Get the number of rows of a dataframe
    :param df: a dataframe object
    :return: the number of rows of the given dataframe
*/
int getRowNumbers(Dataframe df);

/*
    Get all the column names of the given dataframe.
    :param df: a dataframe object
    :return: a dynamic string array containing all column namess
*/
ArrayStr getColumnNames(Dataframe df);



/*
!!! TODO
*, add row after / add column after
*, Create dataframe easy
*, iterrows

*, Maths Functions: sum, count, median, quantile, apply, min, max, mean, std(deviation), var(variance)
*, Concat
*, Create New Column by manipulating artihmetically
*, Group
*, Merge
*, Describe
*, floating point support
*/



#endif