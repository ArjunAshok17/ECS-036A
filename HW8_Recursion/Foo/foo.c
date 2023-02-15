/**
 * Program Description
 * This program recursively implements the function/sequence "foo" defined by Mr. Butner
*/

#include <stdio.h>

int foo_calc(int n, int foo4, int foo3, int foo2, int foo1);
int foo(int n);

int main(void)
{
    // variable declaration //
    int foo_result = -1;
    int n;

    // user input //
    printf("Enter a value for n: ");
    scanf(" %i", &n);

    // calculations //
    foo_result = foo(n);

    // user output //
    printf("Foo(%i) = %i\n", n, foo_result);

    // end program //
    return 0;
}

/**
 * This function calculates foo(n) using dynamic programming
 * @param n: the term of the foo sequence to calculate
 * @param foo3: 3rd term of the foo sequence
 * @param foo2: 2nd term of the foo sequence
 * @param foo1: 1st term of the foo sequence
 * @param foo0: 0th term of the foo sequence
 * @modifies: nothing
 * @returns foo(n)
*/
int foo_calc(int n, int foo3, int foo2, int foo1, int foo0)
{
    // base cases //
    if (n == 0)
    {
        return foo0;
    }

    if(n == 1)
    {
        return foo1;
    }

    if (n == 2)
    {
        return foo2;
    }

    if (n == 3)
    {
        return foo3;
    }

    // general case //
    return foo_calc(n - 1, foo3 + foo2 + foo1 - foo0 + 1, foo3, foo2, foo1);
}

/**
 * A foo helper function to make calculations easier
 * @param n: the term of the foo sequence to calculate
 * @modifies: nothing
 * @returns foo(n)
*/
int foo(int n)
{
    return foo_calc(n, 7, 2, 6, 3);
}