/**
 * PROGRAM DESCRIPTION
 * This program finds the real solutions (if they exist) of a user-specified
 * quadratic function 
 */

#include <stdio.h>
#include <math.h>

double find_discriminant(double a, double b, double c);
double find_num_sols(double a, double b, double c);

int main(void)
{
    // variable declaration //
    double a, b, c;
    int num_sols;
    double pos_root, neg_root;

    // user input //
    printf("Given a quadratic equation of the form a*x^2 + b * x + c\n");

    printf("Please enter a: ");
    scanf(" %lf", &a);

    printf("Please enter b: ");
    scanf(" %lf", &b);
    
    printf("Please enter c: ");
    scanf(" %lf", &c);

    // calculations //
    num_sols = find_num_sols(a, b, c);

    if (!num_sols) // since 0 is considered false in C
    {
        printf("There are no real solutions\n");
    }
    else
    {
        pos_root = (-b + find_discriminant(a, b, c)) / (2 * a);

        if (num_sols == 1)
        {
            printf("There is one real solution: %.2lf\n", pos_root);
        }
        else
        {
            printf("There are 2 real solutions\n");
            
            neg_root = (-b - find_discriminant(a, b, c)) / (2 * a);

            printf("Solution 1: %.2lf\n", pos_root);
            printf("Solution 2: %.2lf\n", neg_root);
        }
    }

    // end program //
    return 0;
}

/**
 * This function calculates the discriminant
 * 
 * @param a: a*x^2
 * @param b: b*x
 * @param c; c
 * @return the discriminant
 */
double find_discriminant(double a, double b, double c)
{
    return pow(b * b - 4 * a * c, 0.5);
}

/**
 * This function calculates the discriminant to find the number of
 * real solutions the quadratic has
 * 
 * @param a: a*x^2
 * @param b: b*x
 * @param c; c
 * @return number of real solutions
 */
double find_num_sols(double a, double b, double c)
{
    double discriminant = pow(b * b - 4 * a * c, 0.5);

    // two real solutions
    if (discriminant > 0)
    {
        return 2;
    }
    // 1 real solution
    else if (discriminant == 0)
    {
        return 1;
    }
    // 0 real solutions
    return 0;
}