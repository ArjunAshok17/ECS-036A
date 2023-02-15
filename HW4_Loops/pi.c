/**
 * PROGRAM DESCRIPTION
 * This program will use Monte Carlo simulations to approximate PI
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rand_double(double low, double high);
double gen_coord();
int check_circle(double x, double y);
double sim_PI(int num_iters);

int main(void)
{
    // variable declaration //
    int seed, num_iters;
    double approx_PI;

    // user input //
    printf("Enter the seed for the random number generator: ");
    scanf(" %i", &seed);

    printf("Enter the number of iterations to run: ");
    scanf(" %i", &num_iters);

    // initialize random num gen //
    srand(seed);

    // calculations //
    approx_PI = sim_PI(num_iters);

    // output //
    printf("The value of pi is %.2lf.\n", approx_PI);

    // end program
    return 0;
}

/**
 * Generate a random double between low and high inclusive
 * @param low: the lowest possible double that can be generated
 * @param high: the highest possible double that can be generated
 * @return: a random number between low and high
 */
double rand_double(double low, double high)
{
  return low + ((double) rand()) / (((double) RAND_MAX / (high - low)));
}

/**
 * Generates a coordinate using random numbers
 * @return: a random number between -1 to 1
*/
double gen_coord()
{
    return rand_double(-1, 1);
}

/**
 * Checks whether or not a coordinate is within the circle
 * @param x: x coordinate
 * @param y: y coordinate
 * @return: returns 1 if inside the circle, returns 0 if otherwise
*/
int check_circle(double x, double y)
{
    if (pow(x, 2) + pow(y, 2) <= 1)
    {
        return 1;
    }

    return 0;
}

/**
 * Runs a Monte Carlo simulation to determine the approximate value of PI
 * @param num_iters: number of user specified iterations to run the simulation
 * @return: the approximation for PI as obtained from the simulation
*/
double sim_PI(int num_iters)
{
    // track coordinates within the circle
    int circle_count = 0;

    // coordinate variables
    double x, y;

    for (int i = 0; i < num_iters; i++)
    {
        x = gen_coord();
        y = gen_coord();

        circle_count += check_circle(x, y);
    }

    // calculate probability of landing inside the circle * 4 to get PI
    return 4 * ((double) circle_count) / num_iters;
}