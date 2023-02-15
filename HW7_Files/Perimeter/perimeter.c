/**
 * Program Description
 * This program takes in a binary file of vertices and calculates the perimeter of the shape they define
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/* Define Structs */
typedef struct Point_struct {
    int x;
    int y;
} Point;

typedef struct Polygon_struct {
    int num_points;
    Point* vertices;
} Polygon;

/* Helper Functions */
void gen_polygon(char* file_name, Polygon *shape);
double dist_formula(Point a, Point b);
double calc_perimeter(Polygon* shape);

int main(int argc, char** argv)
{
    // variable declaration //
    Polygon *shape = (Polygon*) calloc(1, sizeof(Polygon));
    shape->num_points = 0;
    shape->vertices = (Point*) calloc(1, sizeof(Point));

    double perimeter;

    // calculations //
    gen_polygon(argv[1], shape);
    perimeter = calc_perimeter(shape);

    // user output //
    printf("The perimeter is %.2lf\n", perimeter);

    // end program //
    return 0;
}

/**
 * Using a file name, this function opens & reads the file, converting the file data into a Polgyon
 * @param file_name: the name of the binary file to be opened and read
 * @param shape: a pointer to the polygon that will store all the information read
 * @modifies: shape
 * @returns nothing
*/
void gen_polygon(char* file_name, Polygon *shape)
{
    // variable declaration //
    int num_args; // file i/o checking
    int vertex_num = 0; // track index for shape's vertices

    int* cur_num = NULL; // storage for fread()
    cur_num = (int*) calloc(2, sizeof(int));

    // open file //
    FILE* reader = fopen(file_name, "rb");

    // iterate file //
    // get number of points //
    fread(&(shape->num_points), sizeof(int), 1, reader);

    // get vertices //
    do
    {
        // read in two points //
        num_args = fread(cur_num, sizeof(int), 2, reader);

        if (num_args == 2)
        {
            // reallocate memory //
            shape->vertices = (Point*) realloc(shape->vertices, (vertex_num + 1) * sizeof(Point));

            // add vertex //
            shape->vertices[vertex_num].x = cur_num[0];
            shape->vertices[vertex_num++].y = cur_num[1];
        }
    } while (num_args == 2);

    // end function //
    free(cur_num);
    fclose(reader);
    return;
}

/**
 * Given two points, this function calculates the distance between the two using the distance formula
 * @param a: first point
 * @param b: second point
 * @modifies: nothing
 * @returns distance between point a and point b
*/
double dist_formula(Point a, Point b)
{
    // return distance //
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

/**
 * Given a polygon, this function will calculate the distance between every consecutive point,
 * including edge between first and last
 * @param shape: the polygon whose edges' lengths need to be calculated
 * @modifies: nothing
 * @returns perimeter of shape
*/
double calc_perimeter(Polygon* shape)
{
    // variable declaration //
    double perimeter = 0;

    // every consecutive point //
    for (int i = 0; i < shape->num_points - 1; i++)
    {
        perimeter += dist_formula(shape->vertices[i], shape->vertices[i + 1]);
    }

    // include last edge //
    perimeter += dist_formula(shape->vertices[0], shape->vertices[shape->num_points - 1]);

    // return //
    return perimeter;
}