/**
 * PROGRAM DESCRIPTION
 * This program will perform matrix addition on two user inputted matrices 
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void construct_matrix(int** *matrix, const int num_rows, const int num_cols);
void fill_matrix(int** matrix, const int num_rows, const int num_cols);
void add_matrix(int** matrix_final, int** matrix_one, int** matrix_two, const int num_rows, const int num_cols);
void print_matrix(int** matrix, const int num_rows, const int num_cols);

int main(void)
{
    // variable declaration //
    int num_rows, num_cols;

    int** matrix_A = NULL;
    int** matrix_B = NULL;
    int** matrix_AB = NULL;

    // user input //
    printf("Please enter the number of rows: ");
    scanf(" %i", &num_rows);

    printf("Please enter the number of columns: ");
    scanf(" %i", &num_cols);

    printf("Enter Matrix A\n");
    construct_matrix(&matrix_A, num_rows, num_cols);
    fill_matrix(matrix_A, num_rows, num_cols);

    printf("Enter Matrix B\n");
    construct_matrix(&matrix_B, num_rows, num_cols);
    fill_matrix(matrix_B, num_rows, num_cols);

    construct_matrix(&matrix_AB, num_rows, num_cols);

    // calculations //
    add_matrix(matrix_AB, matrix_A, matrix_B, num_rows, num_cols);

    // output //
    printf("A + B =\n");
    print_matrix(matrix_AB, num_rows, num_cols);

    // end program //
    return 0;
}

/**
 * Initializes a matrix with the given number of rows and columns in memory, all values set to zero
 * @param matrix: a pointer to the matrix pointer
 * @param num_rows: the number of rows that the matrix will have
 * @param num_cols: the number of columns that the matrix will have
 * @return: nothing, void function that passes in by pointer
*/
void construct_matrix(int** *matrix, const int num_rows, const int num_cols)
{
    // allocate memory for array of pointers
    (*matrix) = (int**) calloc(num_rows, sizeof(int*));

    // allocate memory for each pointer
    for (int i = 0; i < num_rows; i++)
    {
        (*matrix)[i] = (int*) calloc(num_cols, sizeof(int));
    }

    // end function
    return;
}

/**
 * Gets and uses user input to fill the matrix with values
 * @param matrix: the pointer to the matrix
 * @param num_rows: the number of rows that the matrix will have
 * @param num_cols: the number of columns that the matrix will have
 * @return: nothing, void function that passes in by pointer
*/
void fill_matrix(int** matrix, const int num_rows, const int num_cols)
{
    // for each element, scan in an integer
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            scanf(" %i", &matrix[i][j]);
        }
    }

    // end function
    return;
}

/**
 * Initializes a matrix with the given number of rows and columns in memory, all values set to zero
 * @param matrix_final: the pointer to the matrix that will contain the result of the two added matrices
 * @param matrix_one: the pointer to the first matrix to be added
 * @param matrix_two: the pointer to the second matrix to be added
 * @param num_rows: the number of rows that the matrix will have
 * @param num_cols: the number of columns that the matrix will have
 * @return: nothing, void function that passes in by pointer
*/
void add_matrix(int** matrix_final, int** matrix_one, int** matrix_two, const int num_rows, const int num_cols)
{
    // iterate through the matrix
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols; j++)
        {
            // element-wise adding
            matrix_final[i][j] = matrix_one[i][j] + matrix_two[i][j];
        }
    }

    // end function
    return;
}

/**
 * Prints the values of a matrix to console
 * @param matrix_final: the pointer to the matrix that will be printed
 * @param num_rows: the number of rows that the matrix will have
 * @param num_cols: the number of columns that the matrix will have
 * @return: nothing, void function that passes in by pointer
*/
void print_matrix(int** matrix, const int num_rows, const int num_cols)
{
    // iterate through each value and print each number
    for (int i = 0; i < num_rows; i++)
    {
        for (int j = 0; j < num_cols - 1; j++)
        {
            // print every number that isn't the last in the row
            printf("%i ", matrix[i][j]);
        }

        // print the last number in the row and get a new line
        printf("%i\n", matrix[i][num_cols - 1]);
    }

    // end function
    return;
}