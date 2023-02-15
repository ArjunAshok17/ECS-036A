/**
 * PROGRAM DESCRIPTION
 * This program will print out a user-specified number of rows of Pascal's Triangle
*/

#include <stdio.h>
#include <stdlib.h>

void construct_triangle(int** *pascals_triangle, int num_levels);
void calculate_triangle(int** pascals_triangle, int num_levels);
void print_pascals(int** pascals_triangle, const int num_levels);

int main(void)
{
    // variable declaration //
    int num_levels;
    int** pascals_triangle = NULL;

    // user input //
    printf("Please enter how many levels of Pascal's Triangle you would like to see: ");
    scanf(" %i", &num_levels);

    // calculations //
    construct_triangle(&pascals_triangle, num_levels);
    calculate_triangle(pascals_triangle, num_levels);

    // output //
    print_pascals(pascals_triangle, num_levels);

    // end program //
    return 0;
}

/**
 * This function initializes the 2D-array to store Pascal's Triangle and fills in all ones
 * @param pascals_triangle: the 2D-array pointer to store the pointers which store the rows of the Pascal's Triangle
 * @param num_levels: the number of levels of the Pascal's Triangle that the user wants
 * @return: nothing, pass-by-pointer utilized
*/
void construct_triangle(int** *pascals_triangle, int num_levels)
{
    // initialize the pointer to the pointers
    (*pascals_triangle) = (int**) calloc(num_levels, sizeof(int*));

    // initialize each row
    for (int i = 0, num_elements = 1; i < num_levels; i++, num_elements++)
    {
        // initialize row pointers
        (*pascals_triangle)[i] = (int*) calloc(num_elements, sizeof(int));

        // fill in ones
        (*pascals_triangle)[i][0] = 1;
        (*pascals_triangle)[i][num_elements - 1] = 1;
    }

    // end function
    return;
}

/**
 * This function fills in the rows of the Pascal's triangle for the user-specified number of rows
 * @param pascals_triangle: the 2D-array pointer to store the pointers which store the rows of the Pascal's Triangle
 * @param num_levels: the number of levels of the Pascal's Triangle that the user wants
 * @return: nothing, pass-by-pointer utilized
*/
void calculate_triangle(int** pascals_triangle, int num_levels)
{
    for (int i = 2, num_elements = 3; i < num_levels; i++, num_elements++)
    {
        for (int j = 1; j < num_elements - 1; j++)
        {
            pascals_triangle[i][j] = pascals_triangle[i - 1][j - 1] + pascals_triangle[i - 1][j];
        }
    }

    // end function
    return;
}

/**
 * This function prints out the 2D-Array that stores Pascal's Triangle, assumes length of each pointer
 * @param pascals_triangle: the 2D-array pointer to store the pointers which store the rows of the Pascal's Triangle
 * @return: none, only prints output doesn't adjust values
*/
void print_pascals(int** pascals_triangle, const int num_levels)
{
    for (int i = 0; i < num_levels; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (j == i)
            {
                printf("%i\n", pascals_triangle[i][j]);
            }
            else
            {
                printf("%i ", pascals_triangle[i][j]);
            }
        }
    }

    // end function
    return;
}