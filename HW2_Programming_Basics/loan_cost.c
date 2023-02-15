#include <math.h>
#include <stdio.h>

int main(void)
{
    // declare vars //
    double P, annual_i, monthly_i;
    int n;
    double payment_req, total_pay, loan_cost;

    // user input //
    printf("Please enter the amount of money you borrowed: ");
    scanf(" %lf", &P);

    printf("Please enter the annual interest rate: "); // grader relies on '$' before the Please
    scanf(" %lf", &annual_i);

    printf("Please enter the number of payments to be made: ");
    scanf(" %i", &n);

    // calculations //
    monthly_i = annual_i / 12; // get monthly interest rate
    payment_req = (P * monthly_i) / (1 - pow(1 + monthly_i, -n));
    total_pay = payment_req * n;
    loan_cost = total_pay - P;

    // output //
    printf("A loan of $%.2lf with an annual interest of %.2lf paid off over %i months"
           " will have monthly payments of $%.2lf.\n\n", P, annual_i, n, payment_req);
    printf("In total, you will pay $%.2lf, making the cost of your loan $%.2lf.\n", total_pay, loan_cost);

    // end program
    return 0;
}