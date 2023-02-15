/**
 * PROGRAM DESCRIPTION
 * This program will check whether or not two words are anagrams of one another
 * NOTE: Does not take case into account
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// input //
bool is_valid_format(const int num_args_req, const int num_args_read, bool expected_last_val);
void get_valid_string(const bool is_last_element, const char* prompt, char* user_input);

// calculations //
void get_letter_count(char* word, int* letter_count);
bool arr_cmp(int* arr1, int* arr2, const int arr_len);

int main(void)
{
    // variable declaration //
    char* word_one = (char*) calloc(21, sizeof(char));
    char* word_two = (char*) calloc(21, sizeof(char));
    word_one[21] = '\0';
    word_two[21] = '\0';

    int* letter_count_one = (int*) calloc(26, sizeof(int));
    int* letter_count_two = (int*) calloc(26, sizeof(int));

    // user input //
    get_valid_string(true, "Please enter the first word: ", word_one);
    get_valid_string(true, "Please enter the second word: ", word_two);

    // calculations //
    get_letter_count(word_one, letter_count_one);
    get_letter_count(word_two, letter_count_two);

    // output //
    if (arr_cmp(letter_count_one, letter_count_two, 26))
    {
        printf("%s is an anagram of %s\n", word_one, word_two);
    }
    else
    {
        printf("%s is NOT an anagram of %s\n", word_one, word_two);
    }

    // end program //
    free(word_one);
    free(word_two);
    free(letter_count_one);
    free(letter_count_two);

    return 0;
}

/**
 * Determines whether or not the inpit is formatted correctly
 * @param num_args_req: the number of format placeholders that needed to have been read in the last scanf
 * @param num_args_read: the actual number of placeholders that were read from scanf, ie its return value
 * @param expected_last_val: true if this is the last value that should be on this line of input
 * @return: true if the input is correctly formatted and false otherwise
 */
bool is_valid_format(const int num_args_req, const int num_args_read, bool expected_last_val)
{
    bool correct_format = num_args_read == num_args_req;

    if (expected_last_val)
    {
        char should_be_newline = '?';
        scanf("%c", &should_be_newline);
        correct_format = correct_format && should_be_newline == '\n';
    }

    return correct_format;
}

/**
 * Gets a string from the user using a specified prompt and checks it's a valid word
 * @param is_last_element: true if this is the last value that should be on this line of input
 * @param prompt: a string prompting the user to enter input
 * @param user_input: pointer to memory address where the input will be stored
 * @return: no return, pass-by-pointers
 */
void get_valid_string(const bool is_last_element, const char* prompt, char* user_input)
{
    const int num_args_req = 1;
    int num_args_read;

    // prompt user
    printf("%s", prompt);

    // read input
    num_args_read = scanf(" %s", user_input);

    // check format
    if (!is_valid_format(num_args_req, num_args_read, is_last_element))
    {
        exit(0);
    }

    // check string for valid chars
    for (int i = 0, l = strlen(user_input); i < l; i++)
    {
        if (!isalpha(user_input[i]))
        {
            printf("ERROR: INVALID INPUT\n");
            exit(0);
        }
    }

    // end function
    return;
}

/**
 * Calculates the letter counts for a given string
 * @param word: the string traversed over to count the distribution of letters
 * @param letter_count: the integer array to store the distribution of letters
 * @return: no return, pass-by-pointer
*/
void get_letter_count(char* word, int* letter_count)
{
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        letter_count[toupper(word[i]) - 'A'] += 1;
    }

    // end function
    return;
}

/**
 * Compares two integer arrays and determines if they are equal or not
 * @param arr1: the first integer array to compare
 * @param arr2: the second integer array to compare
 * @param arr_len: the length of both arrays, if not equal then function is anyways not required
 * @return: true if the arrays are equal in value, false if otherwise
*/
bool arr_cmp(int* arr1, int* arr2, const int arr_len)
{
    for (int i = 0; i < arr_len; i++)
    {
        if (arr1[i] != arr2[i])
        {
            return false;
        }
    }

    return true;
}