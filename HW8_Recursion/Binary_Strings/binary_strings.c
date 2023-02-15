/**
 * Program Description
 * This program prints all possible combinations of a string of 1's and 0's where certain characters
 * (marked with an X in the string) can be changed into either a 1 OR a 0
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void process_string(char* bin_str, const int len);
bool contains_x(char* bin_str, int start, const int len);
void print_combos(char* bin_str, int start, const int len);

int main(int argc, char** argv)
{
    // variable declaration //
    char* bin_str = argv[1];
    const int len = strlen(bin_str);

    // calculations //
    process_string(bin_str, len);
    print_combos(bin_str, 0, len);

    // end program //
    return 0;
}

/**
 * Processes the input string to only contain 0's, 1's, and lowercase x's
 * @param bin_str: the string to be processed
 * @param len: bin_str's length
 * @modifies: bin_str
 * @returns nothing
*/
void process_string(char* bin_str, const int len)
{
    // iterate through string //
    for (int i = 0; i < len; i++)
    {
        if (bin_str[i] == 'X')
        {
            bin_str[i] = 'x';
        }
    }

    // end function //
    return;
}

/**
 * Checks if the string has any lowercase x's; helper function for print_combos
 * @param bin_str: string to check
 * @param start: index to start checking at
 * @param len: bin_str's length
 * @modifies: nothing
 * @returns true if there's at least 1 x, false if 0
*/
bool contains_x(char* bin_str, int start, const int len)
{
    // iterate through string //
    for (int i = start; i < len; i++)
    {
        // if any char is 'x' //
        if (bin_str[i] == 'x')
        {
            return true;
        }
    }

    // if no char is 'x' //
    return false;
}

/**
 * Recursively prints all the combinations of the binary string inputted
 * @param bin_str: the binary string
 * @param start: starting index of where to check from
 * @param len: bin_str's length
 * @modifies: nothing
 * @returns nothing
*/
void print_combos(char* bin_str, int start, const int len)
{
    // base cases //
    if (start == len || !contains_x(bin_str, start, len))
    {
        printf("%s\n", bin_str);
        return;
    }

    // general case //
    if (bin_str[start] == 'x')
    {
        // diverge path //
        bin_str[start] = '0';
        print_combos(bin_str, start + 1, len);

        bin_str[start] = '1';
        print_combos(bin_str, start + 1, len);

        // end recursion && reset //
        bin_str[start] = 'x';
        return;
    }
    
    // if not 'x' //
    print_combos(bin_str, start + 1, len);
    return;
}