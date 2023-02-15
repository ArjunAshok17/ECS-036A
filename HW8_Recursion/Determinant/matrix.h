#ifndef MATRIX_H
    #define MATRIX_H

    // libraries //
    #include <stdbool.h>
    #include <stdio.h>
    #include <stdlib.h>

    // struct //
    typedef struct Matrix_struct {
        int rows;
        int cols;
        double** mat;
    } Matrix;

    // initialize matrix //
    void find_file(char* file_name, FILE* *reader);
    void allocate_matrix(Matrix *m);
    void read_matrix(Matrix *m, FILE* reader);
    
    // matrix helper functions //
    void print_matrix(Matrix* m);
    Matrix* sub_matrix(Matrix *m, int col);

    // determinant //
    double determinant(Matrix* m);

#endif