/**
 * PROGRAM DESCRIPTION
 * This program will determine whether you should invest your money or
 * put it towards paying of your loans
*/

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// calculations //
double potential_minpay_return(double loan_amt, double invest_pay, double min_pay, double interest_rate, double invest_rate, int num_months);
double potential_fullpay_return(double loan_amt, double invest_pay, double interest_rate, double invest_rate, int num_months);
void output_optimal_strat(double min_return, double full_return, double invest_pay);

// input validation //
bool is_valid_format(const int num_args_req, const int num_args_read, bool expected_last_val);
double get_valid_double(const bool is_last_element, const char* prompt, double lower_bound);
int get_valid_int(const bool is_last_element, const char* prompt, int lower_bound);

int main(void)
{
    // variable declaration //
    double loan_amt, min_pay, invest_pay;
    double yearly_interest_rate, interest_rate;
    double yearly_invest_rate, invest_rate;
    int cur_age, retire_age;

    double min_return, full_return;
    int num_months;

    // user input //
    loan_amt = get_valid_double(true, "Enter how much you owe in loans: ", 0);
    yearly_interest_rate = get_valid_double(true, "Enter the annual interest rate of the loans: ", 0);
    min_pay = get_valid_double(true, "Enter your minimum monthly loan payment: ", 0);
    invest_pay = get_valid_double(true, "Enter how much money you will be putting towards loans/retirement each month: ", min_pay);
    cur_age = get_valid_int(true, "Enter your current age: ", 0);
    retire_age = get_valid_int(true, "Enter the age you plan to retire at: ", cur_age);
    yearly_invest_rate = get_valid_double(true, "Enter your predicted annual rate of return: ", 0);

    // calculations //
    interest_rate = yearly_interest_rate / 12; // convert to monthly
    invest_rate = yearly_invest_rate / 12; // convert to monthly
    num_months = (retire_age - cur_age) * 12; // find number of months before retirement

    min_return = potential_minpay_return(loan_amt, invest_pay, min_pay, interest_rate, invest_rate, num_months);
    full_return = potential_fullpay_return(loan_amt, invest_pay, interest_rate, invest_rate, num_months);

    // output //
    output_optimal_strat(min_return, full_return, invest_pay);

    // end program
    return 0;
}

/**
 * Determines whether or not the inpit is formatted correctly
 * @param num_args_req: the number of format placeholders that needed to have been read in the last scanf
 * @param num_args_read: the actual number of placeholders that were read from scanf, ie its return value
 * @param expected_last_val: true if this is the last value that should be on this line of input
 * @return: true if the input is correctly formatted and false otherwise
 */
bool is_valid_format(const int num_args_req, const int num_args_read, bool expected_last_val)
{
    bool correct_format = num_args_read == num_args_req;

    if (expected_last_val)
    {
        char should_be_newline = '?';
        scanf("%c", &should_be_newline);
        correct_format = correct_format && should_be_newline == '\n';
    }

    return correct_format;
}

/**
 * Gets a double from the user using a specified prompt until a valid input (>= lower_bound) is received
 * @param is_last_element: true if this is the last value that should be on this line of input
 * @param prompt: a string prompting the user to enter input
 * @param lower_bound: the lower bound of the accepted range of values
 * @return a valid double
 */
double get_valid_double(const bool is_last_element, const char* prompt, double lower_bound)
{
    const int num_args_req = 1;
    int num_args_read;
    double num;

    do
    {
        // prompt user //
        printf("%s", prompt);

        // read input & check //
        num_args_read = scanf(" %lf", &num);
        if (is_valid_format(num_args_req, num_args_read, is_last_element) && num >= lower_bound)
        {
            return num;
        }
    } while (true);
}

/**
 * Gets an int from the user using a specified prompt until a valid input (>= lower_bound) is received
 * @param is_last_element: true if this is the last value that should be on this line of input
 * @param prompt: a string prompting the user to enter input 
 * @param lower_bound: the lower bound of the accepted range of values
 * @return a valid double
 */
int get_valid_int(const bool is_last_element, const char* prompt, int lower_bound)
{
    const int num_args_req = 1;
    int num_args_read;
    int num;

    do
    {
        // prompt user //
        printf("%s", prompt);

        // read input & check //
        num_args_read = scanf(" %i", &num);
        if (is_valid_format(num_args_req, num_args_read, is_last_element) && num >= lower_bound)
        {
            return num;
        }
    } while (true);
}

/**
 * Simulates the returns achieved if the user only pays the minimum monthly amount
 * @param loan_amt: the amount the loan taken out is for
 * @param invest_pay: the monthly income you can designate to invest or payoff loans
 * @param min_pay: the minimimum monthly payments
 * @param interest_rate: the interest rate the loan has
 * @param invest_rate: the investment return rate
 * @param num_months: number of months to simulate over (until retirement)
*/
double potential_minpay_return(double loan_amt, double invest_pay, double min_pay, double interest_rate, double invest_rate, int num_months)
{
    // variable declaration //
    double loan_bal = loan_amt; // stores the loan_amt balance
    double invest_bal = 0;
    const double INVEST_AMT = invest_pay - min_pay; // stores the amount you can invest each month

    // until retirement or the loan is paid back by next month, whichever comes first
    while (num_months > 0 && (loan_bal * (1 + interest_rate)) - min_pay >= 0)
    {
        // calculations
        loan_bal = (loan_bal) * (1 + interest_rate) - min_pay;
        invest_bal = (invest_bal * (1 + invest_rate)) + INVEST_AMT;

        // update vars
        num_months--;
    }

    // next step to make the final payment for the loan OR no step if months is run out
    if (num_months > 0)
    {
        // calculate leftover money to invest
        double unpaid = min_pay - (loan_bal * (1 + interest_rate));

        // invest
        invest_bal = (invest_bal * (1 + invest_rate)) + INVEST_AMT + unpaid;

        // update vars
        loan_bal = 0;
        num_months--;
    }

    // remaining steps where all income is going to be invested
    while (num_months > 0)
    {
        // invest
        invest_bal = (invest_bal * (1 + invest_rate)) + invest_pay;

        // update vars
        num_months--;
    }

    return invest_bal - loan_bal; // total balance after all months
}

/**
 * Simulates the returns achieved if the user only pays the minimum monthly amount
 * @param loan_amt: the amount the loan taken out is for
 * @param invest_pay: the monthly income you can designate to invest or payoff loans
 * @param interest_rate: the interest rate the loan has
 * @param invest_rate: the investment return rate
 * @param num_months: number of months to simulate over (until retirement)
*/
double potential_fullpay_return(double loan_amt, double invest_pay, double interest_rate, double invest_rate, int num_months)
{
    // variable declaration //
    double loan_bal = loan_amt; // stores the loan_amt balance
    double invest_bal = 0;
    const double MONTHLY_PAY = invest_pay; // monthly payment is the full possible amount

    // until retirement or the loan is paid back by next month, whichever comes first
    while (num_months > 0 && (loan_bal * (1 + interest_rate)) - MONTHLY_PAY >= 0)
    {
        // calculations
        loan_bal = (loan_bal) * (1 + interest_rate) - MONTHLY_PAY;

        // update vars
        num_months--;
    }

    // next step to make the final payment for the loan OR no step if months is run out
    if (num_months > 0)
    {
        // calculate leftover money to invest
        double unpaid = MONTHLY_PAY - (loan_bal * (1 + interest_rate));

        // invest
        invest_bal = (invest_bal * (1 + invest_rate)) + unpaid;

        // update vars
        loan_bal = 0;
        num_months--;
    }

    // remaining steps where all income is going to be invested
    while (num_months > 0)
    {
        // invest
        invest_bal = (invest_bal * (1 + invest_rate)) + invest_pay;

        // update vars
        num_months--;
    }

    return invest_bal - loan_bal; // total balance after all months
}

/**
 * Prints to console the dialogue for indicating the optimal strategy for the user
 * @param min_return: total investment returns with the minimum payment strategy
 * @param full_return: total investment returns with the full payment strategy
 * @param invest_pay: the monthly income you get to decide to invest vs payoff loans
 * @return: void
*/
void output_optimal_strat(double min_return, double full_return, double invest_pay)
{
    if (min_return >= full_return)
    {
        printf("You should only make the minimum payments on your loan and apply the rest towards retirement.\n");
        printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you paid off your loan before investing.\n",
                min_return, full_return);
        
        // end function //
        return;
    }
    
    printf("You should apply all $%.2lf towards your loan before making any investments.\n", invest_pay);
    printf("If you do you will have $%.2lf when you retire as opposed to $%.2lf if you only made minimum payments.\n",
            full_return, min_return);

    // end function //
    return;
}