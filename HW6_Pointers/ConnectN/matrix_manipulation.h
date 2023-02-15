#ifndef MATRIX_MANIPULATION_H
    #define MATRIX_MANIPULATION_H

    #include <math.h>
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include "user_input.h"
    
    // board setup //
    void initialize_board(char** *board, int rows, int columns);
    void fill_board(char** board, int rows, int columns);

    // updating board //
    bool update_board(char** board, char player, int rows, int column, int *r, int *c);
    void make_move(char** board, char player, int rows, int columns, int *r, int *c);
    
    // print board //
    void print_board(char** board, int rows, int columns);

    // board checking //
    int num_connections(char** board, char player, int rows, int columns, int r, int c, int dir_mod_r, int dir_mod_c);
    bool game_won(char** board, int win_condition, char player, int rows, int columns, int r, int c);
    bool board_full(char** board, int columns);

    // memory //
    void free_board(char** *board, int rows);

#endif