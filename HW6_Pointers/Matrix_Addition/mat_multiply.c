#include <stdio.h>
#include <stdlib.h>
#include "mat_multiply.h"

/**
 * Display the given prompt to the user, then read two integers from the
 * user storing the result in num_rows and num_cols
 * @param prompt: The prompt to show to the user
 * @param num_rows: the address of where to store the first number entered by the user
 * @param num_cols: the address of where to store the second number entered by the user
 * @returns: nothing
 * @modifies: num_rows, num_cols 
*/
void get_matrix_dimensions_from_user(char* prompt, int *num_rows, int *num_cols)
{
    printf("%s", prompt);
    scanf(" %i %i", num_rows, num_cols);

    // end function
    return;
}

/**
 * Dynamically create a row_dim X col_dim matrix
 * A matrix here is an array of array of integers
 * You do not need to initialize the values of the numbers in
 * the matrix but you can if you want
 * @param row_dim: the number of rows the matrix should have
 * @param col_dum: the number of columns the matrix should have
 * @returns: a row_dim X col_dim matrix of integers
 * @modifies: nothing
*/
int** make_empty_matrix(int row_dim, int col_dim)
{
    int** matrix = (int**) calloc(row_dim, sizeof(int*));

    for (int i = 0; i < row_dim; i++)
    {
        matrix[i] = calloc(col_dim, sizeof(int));
    }

    return matrix;
}

/**
 * Fill in the row_dim X col_dim matrix with values entered by the user
 * The user will enter in row_dim rows that each have col_dim elements in it.
 * For example if row_dim = 3 and col_dim = 4 the user could enter something like
 * 11 25 43 45
 * 10 45 63 17
 * -8 25 -9 24
 * 
 * These values should be stored into matrix
 * @param matrix: the matrix to be filled in
 * @param row_dim: the number of rows matrix has
 * @param col_dum: the number of columns matrix has
 * @returns: nothing
 * @modifies: matrix
*/
void fill_matrix_from_user_input(int** matrix, int row_dim, int col_dim)
{
    for (int i = 0; i < row_dim; i++)
    {
        for (int j = 0; j < col_dim; j++)
        {
            scanf(" %i", &matrix[i][j]);
        }
    }

    // end function
    return;
}

/**
 * Multiply matrix_a and matrix_b together, returning the resulting matrix
 * Set out_num_rows_c to be the number of rows in the resulting matrix
 * Set out_num_cols_c to be the number of cols in the resulting matrix
 * 
 * @param matrix_a: the A in C = A X B
 * @param num_rows_a: the number of rows in matrix a
 * @param num_cols_a: the number of columns in matrix a
 * @param matrix_b: the B in C = A X B
 * @param num_rows_b: the number of rows in matrix b
 * @param num_cols_b: the number of columns in matrix b
 * @param out_num_rows_c: where to store the number of rows of the resulting matrix
 * @param out_num_cols_c: where to store the number of columns of the resulting matrix
 * @returns: matrix_a X matrix_b
 * @modifies: out_num_rows_c, out_num_cols_c
*/
int** matrix_multiply(int** matrix_a, int num_rows_a, int num_cols_a,
                      int** matrix_b, int num_rows_b, int num_cols_b,
                      int* out_num_rows_c, int* out_num_cols_c)
{
    // calculate dimensions
    *out_num_rows_c = num_rows_a;
    *out_num_cols_c = num_cols_b;

    // generate output matrix
    int** matrix_c = make_empty_matrix(*out_num_rows_c, *out_num_cols_c);

    // calculate product
    // for every element in matrix c
    for (int i = 0; i < *out_num_rows_c; i++)
    {
        for (int j = 0; j < *out_num_cols_c; j++)
        {
            // calculate invididual sums and add to total
            for (int k = 0; k < num_cols_a; k++)
            {
                matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
            }
        }
    }

    return matrix_c;
}

/**
 * Print matrix to the screen
 * @param matrix: the matrix to be printed
 * @param row_dim: the number of rows in matrix
 * @param col_dim: the number of columns in matrix
 * @returns: nothing
 * @modifies: nothing
*/
void print_matrix(int** matrix, int row_dim, int col_dim)
{
    for (int i = 0; i < row_dim; i++)
    {
        for (int j = 0; j < col_dim - 1; j++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("%i\n", matrix[i][col_dim - 1]);
    }

    // end function
    return;
}

/**
 * Delete matrix AND set it to NULL.
 * @param matrix: the address of the matrix to be deleted
 * @param row_dim: the number of rows in matrix
 * @param col_dim: the number of columns in matrix
 * @returns: nothing
 * @modifies: matrix
*/
void delete_matrix(int** *matrix, int row_dim, int col_dim)
{
    for (int i = 0; i < row_dim; i++)
    {
        // return null for every pointer
        free((*matrix)[i]);
        (*matrix)[i] = NULL;
    }

    free((*matrix));
    (*matrix) = NULL;
}
