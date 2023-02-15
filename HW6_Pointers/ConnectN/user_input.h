#ifndef USER_INPUT_H
    #define USER_INPUT_H

    #include <ctype.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    bool cl_input_valid(int argc, char** argv, int *rows, int *columns, int *win_condition);
    int get_valid_int(const bool is_last_element, int columns);

#endif