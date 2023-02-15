/**
 * PROGRAM DESCRIPTION
 * This program will count the number of words in a file
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

FILE* open_file(char* file_name);
int count_words(FILE* reader);
void close_file(FILE* reader);

int main(int argc, char** argv)
{
    // variable declaration //
    FILE* reader = open_file(argv[1]);
    int num_words;

    // calculations //
    num_words = count_words(reader);

    // output //
    printf("There are %i word(s).\n", num_words);

    // end program //
    close_file(reader);
    return 0;
}

/**
 * This function will return the FILE pointer for reading
 * @param file_name: name of the file being opened
 * @modifies: nothing
 * @returns FILE pointer to the specified file
*/
FILE* open_file(char* file_name)
{
    return fopen(file_name, "r");
}

/**
 * This function will count the number of words in a file
 * @param reader: pointer to the file specified
 * @modifies: nothing
 * @returns number of words
*/
int count_words(FILE* reader)
{
    // variable declaration //
    int num_words = 0;
    char cur_char;

    // loop through each character //
    cur_char = fgetc(reader);
    while (cur_char != EOF)
    {
        // next word //
        while (cur_char != EOF && !isspace(cur_char))
        {
            // next char
            cur_char = fgetc(reader);
        }

        // increment counter //
        num_words++; // guaranteed to have passed one word

        // remove whitespace //
        while (cur_char != EOF && isspace(cur_char))
        {
            // next char
            cur_char = fgetc(reader);
        }
    }

    return num_words;
}

/**
 * This function will return the FILE pointer for reading
 * @param reader: file pointer to close
 * @modifies: reader
 * @returns nothing
*/
void close_file(FILE* reader)
{
    // close file //
    fclose(reader);

    // end function //
    return;
}