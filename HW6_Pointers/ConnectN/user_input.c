/**
 * Program Description
 * This program defines functions prototyped in the header file "user_input.h". These functions
 * are built to prompt andreceive user input, specifically in reference to the Connect-N game
*/

#include "user_input.h"

/**
 * Checks if the command line inputs are valid for Connect-N & outputs specific error message
 * @param argc: number of command line arguments read in
 * @param argv: the vector of arguments read in
 * @param rows: number of rows
 * @param columns: number of columns
 * @param win_condition: number of connections needed to win
 * @modifies: nothing
 * @returns true if the input is valid, false otherwise
*/
bool cl_input_valid(int argc, char** argv, int *rows, int *columns, int *win_condition)
{
    char should_be_empty;
    int num_args_read;

    // num args check //
    if (argc < 4)
    {
        printf("Not enough arguments entered\n");
        return false;
    }
    else if (argc > 4)
    {
        printf("Too many arguments entered\n");
        return false;
    }
    else
    {
        // get inputs //
        num_args_read = sscanf(argv[1], " %i %c", rows, &should_be_empty);
        if (num_args_read != 1)
        {
            return false;
        }

        num_args_read = sscanf(argv[2], " %i %c", columns, &should_be_empty);
        if (num_args_read != 1)
        {
            return false;
        }

        num_args_read = sscanf(argv[3], " %i %c", win_condition, &should_be_empty);
        if (num_args_read != 1)
        {
            return false;
        }

        // value checking //
        if (rows <= 0 || columns <= 0 || win_condition <= 0)
        {
            return false;
        }
    }

    return true;
}

/**
 * Gets a pair of integers from the user using a specified prompt until valid inputs [0, board edges] is received
 * @param is_last_element: true if this is the last value that should be on this line of input
 * @param columns: number of columns, the upper bound of the accepted range of values for column
 * @modifies: nothing
 * @returns a valid integer
 */
int get_valid_int(const bool is_last_element, int columns)
{
    const int num_args_req = 2;
    char newline_check;
    int num_args_read;
    int num;

    do
    {
        // prompt user //
        printf("Enter a column between %i and %i to play in: ", 0, columns - 1);

        // read input & check //
        num_args_read = scanf(" %i%c", &num, &newline_check);
        if (newline_check == '\n' && num_args_req == num_args_read)
        {
            return num;
        }
        else
        {
            // clear input buffer
            while(getchar() != '\n');
        }
    } while (true);

    // error checking & end function //
    return -1;
}