/**
 * Program Description
 * This program will simulate a game of Connect-N (like Connect-4, but the users can specify
 * how many have to be connected in order to win) between two users
*/

/** Import Libraries **/
#include <stdio.h>
#include <stdlib.h>
#include "matrix_manipulation.h"
#include "user_input.h"

/** Run Connect-N Game **/
int main(int argc, char** argv)
{
    // variable declaration //
    int rows = -1, columns = -1; // board dimensions
    int win_condition = -1; // connections necessary to win
    char** board = NULL; // board
    int r = -1, c = -1; // stores last move

    char player[2] = {'X', 'O'}; // determines whose turn it is
    bool first_turn = true; // tracks an edge case for conducting the game
    int turn_num = 1; // counts number of turns played (for player determination)

    // command line input //
    if (!cl_input_valid(argc, argv, &rows, &columns, &win_condition))
    {
        printf("Usage connectn.out num_rows num_columns number_of_pieces_in_a_row_needed_to_win\n");
        exit(0);
    }

    // conduct game //
    // board setup //
    initialize_board(&board, rows, columns);
    fill_board(board, rows, columns);

    // play game //
    do
    {
        // edge case
        if (first_turn)
        {
            turn_num--;
            first_turn = false;
        }

        // make a move
        print_board(board, rows, columns);
        make_move(board, player[turn_num % 2], rows, columns, &r, &c);

        // update turn
        turn_num++;
    }
    while (!game_won(board, win_condition, player[(turn_num - 1) % 2], rows, columns, r, c)
           && !board_full(board, columns));
    print_board(board, rows, columns);

    // print output //
    if (board_full(board, columns) && !game_won(board, win_condition, player[(turn_num - 1) % 2], rows, columns, r, c))
    {
        printf("Tie game!\n");
    }
    else
    {
        printf("Player %i Won!\n", player[(turn_num - 1) % 2] == 'X' ? 1 : 2);
    }

    // end program //
    free_board(&board, rows);
    return 0;
}