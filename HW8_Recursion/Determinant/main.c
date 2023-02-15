/**
 * Program Description
 * This program uses recursion to calculate the determinant of a matrix
*/

#include "matrix.h"

int main(int argc, char** argv)
{
    // variable declaration //
    char* file_name = argv[1];
    Matrix* m = (Matrix*) calloc(1, sizeof(Matrix));
    FILE* reader = NULL;
    double det = -1;

    // calculations //
    find_file(file_name, &reader);
    read_matrix(m, reader);
    det = determinant(m);

    // user output //
    printf("The determinant is %.2lf.\n", det);

    // end program //
    return 0;
}