/**
 * Program Description
 * This program defines functions prototyped in the header file "board_manipulation.h". These functions
 * are built to manipulate 2D-Arrays (matrices), specifically in reference to the Connect-N game board
*/

#include "matrix_manipulation.h"

/**
 * Initializes a 2D-Array of specified size to represent the board of the game
 * @param board: a pointer to the memory address that stores the 2D-Array board
 * @param rows: number of rows
 * @param columns: number of columns
 * @modifies: board
 * @returns nothing
*/
void initialize_board(char** *board, int rows, int columns)
{
    // allocate memory //
    (*board) = (char**) calloc(rows, sizeof(char*));

    for (int i = 0; i < rows; i++)
    {
        (*board)[i] = (char*) calloc(columns, sizeof(char));
    }

    // end function //
    return;
}

/**
 * Fills in the board to prep for the start of the game
 * @param board: 2D-Array representing the board
 * @param rows: number of rows
 * @param columns: number of columns
 * @modifies: board
 * @returns nothing
*/
void fill_board(char** board, int rows, int columns)
{
    // fill w/ '*' //
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            board[i][j] = '*';
        }
    }

    // end function //
    return;
}

/**
 * Updates the board to reflect the move
 * @param board: 2D-Array representing the board
 * @param player: character that determines which player made the move
 * @param rows: number of rows
 * @param column: column number the move was made
 * @param r: pointer to last move made's row
 * @param c: pointer to last move made's column
 * @modifies: board, r, c
 * @returns true if successful update, false if invalid move
*/
bool update_board(char** board, char player, int rows, int column, int *r, int *c)
{
    // invalid move check //
    if (board[0][column] != '*')
    {
        return false;
    }

    // update column //
    *c = column;

    // next empty space //
    for (int i = 1; i < rows; i++)
    {
        // place move //
        if (board[i][column] != '*')
        {
            board[i - 1][column] = player;
            *r = i - 1;
            return true;
        }
    }

    // edge case //
    board[rows - 1][column] = player;
    *r = rows - 1;
    return true;
}

/**
 * Given which player, this function will prompt the user and make a valid move
 * @param board: 2D-Array representing the board
 * @param player: char of the current player
 * @param rows: number of rows
 * @param columns: number of columns
 * @param r: pointer to last move made's row
 * @param c: pointer to last move made's column
 * @modifies: board, r, c
 * @returns nothing
*/
void make_move(char** board, char player, int rows, int columns, int *r, int *c)
{
    // get valid column & make move //
    int column;

    do
    {
        column = get_valid_int(true, columns);
    } while (!update_board(board, player, rows, column, r, c));

    // end function //
    return;
}

/**
 * Prints the board along with the coordinates marking each axis
 * @param board: 2D-Array representing the board
 * @param rows: the number of rows
 * @param columns: the number of columns
 * @modifies: nothing
 * @returns nothing
*/
void print_board(char** board, int rows, int columns)
{
    // elements + row numbers //
    for (int i = 0; i < rows; i++)
    {
        // row numbers
        printf("%i ", rows - 1 - i);

        // elements
        for (int j = 0; j < columns; j++)
        {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }

    // column numbers //
    printf("  ");
    for (int i = 0; i < columns; i++)
    {
        printf("%i ", i);
    }
    printf("\n");

    // end function //
    return;
}

/**
 * Helper function to check the specified direction's number of connections
 * @param board: 2D-Array representing the board
 * @param player: char to determine which player might have won (player's pieces we check)
 * @param rows: number of rows
 * @param columns: number of columns
 * @param r: row position of the piece being considered
 * @param c: column position of the piece being considered
 * @param dir_mod_r: direction modifier for the rows, controls how we progress up and down for checking
 * @param dir_mod_c: direction modifier for the columns, controls how we progress right and left for checking
 * @modifies: nothing
 * @returns number of connections in a row in the specified direction, non-inclusive of starting node
*/
int num_connections(char** board, char player, int rows, int columns, int r, int c, int dir_mod_r, int dir_mod_c)
{
    // track connections //
    int counter = 0;

    // check until bounds reached //
    for (int i = 0; (r + i * dir_mod_r < rows && r + i * dir_mod_r >= 0) &&
                    (c + i * dir_mod_c < columns && c + i * dir_mod_c >= 0); i++)
    {
        // check if connection is broken //
        if (board[r + i * dir_mod_r][c + i * dir_mod_c] == player)
        {
            counter++;
        }
        else
        {
            return counter;
        }
    }

    return counter;
}

/**
 * Checks whether the board position is a win or not using recursion since we can assume
 * only the most recent move matters for determining who has won
 * @param board: 2D-Array representing the board
 * @param win_condition: number of connections in a row needed to win
 * @param player: char to signify which player might have won (player's pieces we check)
 * @param rows: number of rows
 * @param columns: number of columns
 * @param r: row position of the piece being considered
 * @param c: column position of the piece being considered
 * @modifies: nothing
 * @returns true if the player has won, false if there's no win yet
*/
bool game_won(char** board, int win_condition, char player, int rows, int columns, int r, int c)
{
    // first row: checks up and down
    // second row: checks right and left
    // third row: checks up-right and down-left diagonal
    // fourth row: check up-left and down-right diagonal
    // subtract one to avoid double-counting last move

        // inefficient but organized //
        /*
        bool vertical = (num_connections(board, player, rows, columns, r, c, 1, 0) + num_connections(board, player, rows, columns, r, c, -1, 0) - 1) == win_condition;
        bool horizontal = num_connections(board, player, rows, columns, r, c, 0, 1) + num_connections(board, player, rows, columns, r, c, 0, -1) - 1 == win_condition;
        bool r_diagonal = num_connections(board, player, rows, columns, r, c, 1, 1) + num_connections(board, player, rows, columns, r, c, -1, -1) - 1 == win_condition;
        bool l_diagonal = num_connections(board, player, rows, columns, r, c, 1, -1) + num_connections(board, player, rows, columns, r, c, -1, 1) - 1== win_condition;
        
        return vertical || horizontal || r_diagonal || l_diagonal;
        */

    // short-circuit version
    return (num_connections(board, player, rows, columns, r, c, 1, 0) + num_connections(board, player, rows, columns, r, c, -1, 0) - 1) >= win_condition ||
           (num_connections(board, player, rows, columns, r, c, 0, 1) + num_connections(board, player, rows, columns, r, c, 0, -1) - 1) >= win_condition ||
           (num_connections(board, player, rows, columns, r, c, 1, 1) + num_connections(board, player, rows, columns, r, c, -1, -1) - 1) >= win_condition ||
           (num_connections(board, player, rows, columns, r, c, 1, -1) + num_connections(board, player, rows, columns, r, c, -1, 1) - 1) >= win_condition;
}

/**
 * Checks whether or not the board is filled
 * @param board: 2D-Array representing the board
 * @param columns: number of columns
 * @modifies: nothing
 * @returns true if the board is filled, false if otherwise
*/
bool board_full(char** board, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        if (board[0][i] == '*')
        {
            return false;
        }
    }

    return true;
}

/**
 * Frees allocated memory
 * @param board: a pointer to the memory address that stores the 2D-Array board
 * @param rows: number of rows
 * @modifies: board
 * @returns nothing
*/
void free_board(char** *board, int rows)
{
    for (int i = 0; i < rows; i++)
    {
        free((*board)[i]);
        (*board)[i] = NULL;
    }
    free((*board));
    (*board) = NULL;
}