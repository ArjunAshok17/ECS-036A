/**
 * PROGRAM DESCRIPTION
 * This program will convert between different units of temperature and distance,
 * making sure to account for user input errors
 * 
 * This program will convert all inputs to a standard unit, then convert to the desired
 * unit in order to be more concise and efficient
*/

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// conversion functions //
double dist_feet(double dist, char units);
double convert_feet(double dist_ft, char units);
double temp_celsius(double temp, char units);
double convert_celsius(double temp_c, char units);

// input validation //
bool is_valid_format(const int num_args_req, const int num_args_read, bool expected_last_val);
char get_valid_char(const bool is_last_element);
double get_valid_double(const bool is_last_element);

bool dist_units(char units);
bool temp_units(char units);

int main(void)
{
    // variable declaration //
    double value_init, value_mid, value_final;
    char conversion_type, units_orig, units_conv;

    // user input //
    printf("Pick the type of conversion that you would like to do.\n");
    printf("T or t for temperature\n");
    printf("D or d for distance\n");

    printf("Enter your choice: ");
    conversion_type = get_valid_char(true);
    conversion_type = toupper(conversion_type);

    // calculations //
    if (conversion_type == 'T')
    {
        printf("Enter the temperature followed by its suffix (F, C, or K): ");
        value_init = get_valid_double(false);
        units_orig = get_valid_char(true);
        units_orig = toupper(units_orig);

        // ERROR: INVALID UNIT //
        if (!temp_units(units_orig))
        {
            printf("%c is not a valid temperature type. Ending program.\n", units_orig);
            exit(0);
        }

        printf("Enter the new unit type (F, C, or K): ");
        units_conv = get_valid_char(true);
        units_conv = toupper(units_conv);

        // ERROR: INVALID UNIT //
        if (!temp_units(units_conv))
        {
            printf("%c is not a valid temperature type. Ending program.\n", units_conv);
            exit(0);
        }

        value_mid = temp_celsius(value_init, units_orig);
        value_final = convert_celsius(value_mid, units_conv);
    }
    else if (conversion_type == 'D')
    {
        printf("Enter the distance followed by its suffix (I,F,Y,M): ");
        value_init = get_valid_double(false);
        units_orig = get_valid_char(true);
        units_orig = toupper(units_orig);

        // ERROR: INVALID UNIT //
        if (!dist_units(units_orig))
        {
            printf("%c is not a valid distance type. Ending program.\n", units_orig);
            exit(0);
        }

        printf("Enter the new unit type (I,F,Y,M): ");
        units_conv = get_valid_char(true);
        units_conv = toupper(units_conv);
        
        // ERROR: INVALID UNIT //
        if (!dist_units(units_conv))
        {
            printf("%c is not a valid distance type. Ending program.\n", units_conv);
            exit(0);
        }

        value_mid = dist_feet(value_init, units_orig);
        value_final = convert_feet(value_mid, units_conv);
    }
    // ERROR: UKNOWN CONVERSION TYPE //
    else
    {
        printf("Unknown conversion type %c chosen. Ending program.\n", conversion_type);
        exit(0);
    }

    // output //
    printf("%.2lf%c is %.2lf%c\n", value_init, units_orig, value_final, units_conv);

    // end program //
    return 0;
}

/**
 * This function converts the specified unit
 * into feet
 * 
 * @param dist: distance value
 * @param units: distance units
 * @return the distance in feet
 */
double dist_feet(double dist, char units)
{
    // INCHES to feet //
    if (units == 'I')
    {
        dist /= 12; // 12 in in 1 ft
    }
    // YARDS to feet //
    else if (units == 'Y')
    {
        dist *= 3; // 3 ft to 1 yd
    }
    // MILES to feet //
    else if (units == 'M')
    {
        dist *= 5280; // 5280 ft to 1 mi
    }
    // FEET to feet //
    // do nothing

    return dist;
}

/**
 * This function converts the distance in feet into the specified unit
 * 
 * @param dist_ft: distance in feet
 * @param units: units to convert to
 * @return the distance in units specified
 */
double convert_feet(double dist_ft, char units)
{
    // feet to INCHES //
    if (units == 'I')
    {
        dist_ft *= 12; // 12 in in 1 ft
    }
    // feet to YARDS //
    else if (units == 'Y')
    {
        dist_ft /= 3; // 3 ft to 1 yd
    }
    // feet to MILES //
    else if (units == 'M')
    {
        dist_ft /= 5280; // 5280 ft to 1 mi
    }
    // feet to FEET //
    // do nothing

    return dist_ft;
}

/**
 * This function converts the specified unit into celsius
 * 
 * @param temp: temperature value
 * @param units: temperature unit
 * @return the temperature in celsius
 */
double temp_celsius(double temp, char units)
{
    // FAHRENHEIT to celsius //
    if (units == 'F')
    {
        temp = (temp - 32) * (5.0 / 9);
    }
    // KELVIN to celsius //
    else if (units == 'K')
    {
        temp -= 273.15;
    }
    // CELSIUS to celsius //
    // do nothing

    return temp;
}

/**
 * This function converts degrees celsius into the specified unit
 * 
 * @param temp_c: temperature in celsius
 * @param units: units to convert to
 * @return the temperture in units specified
 */
double convert_celsius(double temp_c, char units)
{
    // celsius to FAHRENHEIT //
    if (units == 'F')
    {
        temp_c = (temp_c * 9.0 / 5.0) + 32;
    }
    // celsius to KELVIN //
    else if (units == 'K')
    {
        temp_c += 273.15;
    }
    // celsius to CELSIUS //
    // do nothing

    return temp_c;
}

/**
 *
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
 * Get a character  from the user but close the program if one is not entered
 * 
 * @param is_last_element: true if this is the last value that should be on this line of input
 * @return a valid character
 */
char get_valid_char(const bool is_last_element)
{
    const int num_args_req = 1;
    int num_args_read;
    char cur_char;

    num_args_read = scanf(" %c", &cur_char);
    if (is_valid_format(num_args_req, num_args_read, is_last_element))
    {
        return cur_char;
    }

    // ERROR: INVALID FORMATTING //
    printf("Invalid formatting. Ending program.\n");
    exit(0);
}

/**
 * Get a double from the user but close the program if one is not entered
 * 
 * @param is_last_element : true if this is the last value that should be on this line of input
 * @return a valid double
 */
double get_valid_double(const bool is_last_element)
{
    const int num_args_req = 1;
    int num_args_read;
    double num;

    num_args_read = scanf(" %lf", &num);
    if (is_valid_format(num_args_req, num_args_read, is_last_element))
    {
        return num;
    }

    // ERROR: INVALID FORMATTING //
    printf("Invalid formatting. Ending program.\n");
    exit(0);
}

/**
 * Checks if the distance units given is valid or not
 * 
 * @param units : units received from the user
 * @return true if the units are valid, false otherwise
 */
bool dist_units(char units)
{
    return units == 'I' || units == 'F' || units == 'Y' || units == 'M';
}

/**
 * Checks if the temperature units given is valid or not
 * 
 * @param units : units received from the user
 * @return true if the units are valid, false otherwise
 */
bool temp_units(char units)
{
    return units == 'F' || units == 'C' || units == 'K';
}