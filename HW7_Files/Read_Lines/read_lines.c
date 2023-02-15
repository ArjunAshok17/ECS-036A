/**
 * Program Description
 * This program defines functions necessary for reading in all lines from a file into a 2D-Array
*/

#include "read_lines.h"

/**
 * Reads all of the lines in file into lines and sets num_lines to be the total number of lines in the file
 * @param reader: a file pointer opened in read mode
 * @param lines: a pointer indicating where the lines should be placed. If there are no lines in a file,
 *               lines will be set to NULL
 * @param num_lines: a pointer to the number of lines, set to the number of lines contained within lines
 * @modifies: lines, num_lines
 * @returns nothing
*/
void read_lines(FILE* reader, char** *lines, int *num_lines)
{
    // variable declaration //
    char* line = NULL;
    int num_chars = 0;

    // reset values //
    (*lines) = NULL;
    *num_lines = 0;

    // attempt to get line, for every line //
    (*lines) = (char**) calloc(1, sizeof(char*));
    while (get_line(reader, &line, &num_chars))
    {
        // update array //
        add_char_arr(lines, num_lines, line, num_chars);

        // free memory //
        free_memory(&line);
    }

    // remove extra space //
    // (*lines) = (char**) realloc((*lines), (*num_lines - 1) * sizeof(char*));

    // end function //
    return;
}

/**
 * Reads in one line from the file and sets line equal to the line if valid, returns false otherwise
 * @param reader: a file pointer opened in read mode
 * @param line: a pointer to store the line
 * @param num_chars: pointer to the number of characters in the line
 * @modifies: line, num_chars
 * @returns true if line is read in, false if no lines left
*/
bool get_line(FILE* reader, char* *line, int *num_chars)
{
    // variable declaration //
    *num_chars = 0;
    char cur_char;

    // edge case //
    cur_char = fgetc(reader);
    if (cur_char == EOF)
    {
        return false;
    }

    // loop through characters in a line //
    while(cur_char != '\n' && cur_char != EOF)
    {
        // reallocate space //
        add_char(line, num_chars, cur_char);

        // update //
        cur_char = fgetc(reader);
    }

    // add newline & null char //
    if (cur_char != EOF)
    {
        add_char(line, num_chars, cur_char);
    }
    
    add_char(line, num_chars, '\0');

    return true;
}

/**
 * Reallocates memory for a char pointer to accept another character
 * @param arr: the pointer to the char pointer to be expanded
 * @param arr_len: current length of the array
 * @param augment: char pointer to augment the original array with
 * @modifies: arr, arr_len
 * @returns nothing
*/
void add_char(char* *arr, int *arr_len, char augment)
{
    // reallocate space //
    (*arr_len)++;
    if ((*arr_len) == 1)
    {
        (*arr) = (char*) calloc(1, sizeof(char));
    }
    else
    {
        (*arr) = (char*) realloc((*arr), (*arr_len) * sizeof(char));
    }

    // update chars //
    (*arr)[(*arr_len) - 1] = augment;

    // end function //
    return;
}

/**
 * Reallocates memory for a pointer to char pointers to accept another char pointer
 * @param arr: the pointer to the char pointer to be expanded
 * @param arr_len: current length of the array
 * @param augment: array to augment the 2D-Array with
 * @param aug_len: length of the array to augment
 * @modifies: arr, arr_len
 * @returns nothing
*/
void add_char_arr(char** *arr, int *arr_len, char* augment, int aug_len)
{
    // reallocate space //
    (*arr_len)++;
    if ((*arr_len) == 1)
    {
        (*arr) = (char**) calloc(1, sizeof(char*));
    }
    else
    {
        (*arr) = (char**) realloc((*arr), (*arr_len) * sizeof(char*));
    }
    
    // copy array //
    (*arr)[*arr_len - 1] = (char*) calloc(aug_len, sizeof(char));

    for (int i = 0; i < aug_len; i++)
    {
        (*arr)[*arr_len - 1][i] = augment[i];
    }

    // end function //
    return;
}

/**
 * Frees memory allocated for storing a single line
 * @param arr: pointer to the char pointer that stores a single line
 * @modifies: arr
 * @returns nothing
*/
void free_memory(char* *arr)
{
    // free //
    free((*arr));
    (*arr) = NULL;

    // end function //
    return;
}