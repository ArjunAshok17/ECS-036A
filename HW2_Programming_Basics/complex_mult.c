#include <stdio.h>

int main(void)
{
    // declare vars //
    int a1, b1;
    int a2, b2;
    int a, b;

    // user input //
    printf("Enter the first complex number in the form ai + b: ");
    scanf(" %i i + %i", &a1, &b1);
    
    printf("Enter the second complex number in the form ai + b: ");
    scanf(" %i i + %i", &a2, &b2);

    // calculations //
    a = a1 * b2 + a2 * b1;
    b = b1 * b2 - a1 * a2;

    // output //
    printf("(%ii + %i) * (%ii + %i) = %ii + %i\n", a1, b1, a2, b2, a, b);

    // end program //
    return 0;
}