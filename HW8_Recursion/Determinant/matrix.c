/**
 * Program Description
 * This file defines functions listed in its header to be used with finding a matrix's determinant
*/

#include "matrix.h"

/**
 * This function will initialize a FILE pointer to the specified file
 * @param file_name: name of the file specified
 * @param reader: pointer to the FILE* that should be inititialized
 * @modifies: reader
 * @returns nothing
*/
void find_file(char* file_name, FILE* *reader)
{
    // open file //
    (*reader) = fopen(file_name, "r");

    // error checking //
    if ((*reader) == NULL)
    {
        printf("ERROR: filename is not valid\n");
        exit(1);
    }

    // end function //
    return;
}

/**
 * This function allocates space for a square matrix given its dimensions
 * @param m: the matrix to be modified
 * @modifies: m
 * @returns nothing
*/
void allocate_matrix(Matrix *m)
{
    // allocate memory //
    m->mat = (double**) calloc(m->rows, sizeof(double*));
    for (int i = 0; i < m->rows; i++)
    {
        m->mat[i] = (double*) calloc(m->cols, sizeof(double));
    }

    // end function //
    return;
}

/**
 * This function reads a file to fill in the elements of a matrix and its dimensions
 * @param m: matrix to modify
 * @param reader: the file to scrape information from
 * @modifies: m
 * @returns nothing
*/
void read_matrix(Matrix *m, FILE* reader)
{
    // read in dimensions //
    fscanf(reader, "%i %i", &(m->rows), &(m->cols));

    // allocate memory //
    allocate_matrix(m);

    // fill elements //
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            // read in each element //
            fscanf(reader, " %lf", &(m->mat[i][j]));
        }
    }

    // end function //
    return;
}

/**
 * This function prints out matrix; useful for debugging & visualizing
 * @param m: matrix to print out
 * @modifies: nothing
 * @returns nothing
*/
void print_matrix(Matrix* m)
{
    // iterate through every element //
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            // print element //
            printf("%lf ", m->mat[i][j]);
        }
        
        // newline for every row //
        printf("\n");
    }

    // end function //
    return;
}

/**
 * This function creates a sub_matrix with all the elements not in the 0th row and specified column;
 * helper function for determinant()
 * @param m: matrix to draw elements from
 * @param col: column to not draw elements from
 * @modifies: nothing
 * @returns a pointer to the sub_matrix
*/
Matrix* sub_matrix(Matrix* m, int col)
{
    // initialize sub matrix //
    Matrix* sub = (Matrix*) calloc(1, sizeof(Matrix));
    sub->rows = m->rows - 1;
    sub->cols = m->cols - 1;
    allocate_matrix(sub);

    // variable declaration //
    int col_index; // track column for the sub matrix

    // copy elements //
    // skip first row
    for (int i = 1; i < m->rows; i++)
    {
        // reset column index //
        col_index = 0;

        for (int j = 0; j < m->cols; j++)
        {
            // skip if column specified matches
            if (j == col)
            {
                continue;
            }

            // copy element, then incremement column index
            sub->mat[i - 1][col_index++] = m->mat[i][j];
        }
    }

    // end function //
    return sub;
}

/**
 * This function recursively calculates the determinant of a matrix; assumes always a square matrix
 * @param m: matrix whose determinant is being calculated
 * @modifies: nothing
 * @returns the determinant of m
*/
double determinant(Matrix* m)
{
    // variable declaration //
    double det = 0;
    int sign = 1;

    // base case  0x0 :: error check //
    if (m->rows <= 0)
    {
        return -1;
    }

    // base case 1x1 //
    if (m->rows == 1)
    {
        // return only element //
        return m->mat[0][0];
    }

    // base case 2x2 //
    if (m->rows == 2)
    {
        // return det(2x2)
        return (m->mat[0][0] * m->mat[1][1]) - (m->mat[0][1] * m->mat[1][0]);
    }

    // general case //
    // for every column
    for (int i = 0; i < m->cols; i++)
    {
        det += sign * m->mat[0][i] * determinant(sub_matrix(m, i));
        sign *= -1;
    }

    return det;
}