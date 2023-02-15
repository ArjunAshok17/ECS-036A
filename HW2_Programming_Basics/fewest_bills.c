#include <math.h>
#include <stdio.h>

int num_bills(int amount_left, int bill);

int main(void)
{
    // declare variables //
    int withdraw_amount;
    int num_hundreds = 0,
        num_fifties = 0,
        num_twenties = 0,
        num_tens = 0,
        num_fives = 0,
        num_ones = 0;
    
    // user input //
    printf("Please enter the amount of money you wish to withdraw: ");
    scanf(" %i", &withdraw_amount);
    
    // calculations //

    // in order to minimize bills, you try to maximize the number of bills 
    // w/ the greatest possible value
    num_hundreds = num_bills(withdraw_amount, 100);
    withdraw_amount -= 100 * num_hundreds;
    
    num_fifties = num_bills(withdraw_amount, 50);
    withdraw_amount -= 50 * num_fifties;
    
    num_twenties = num_bills(withdraw_amount, 20);
    withdraw_amount -= 20 * num_twenties;
    
    num_tens = num_bills(withdraw_amount, 10);
    withdraw_amount -= 10 * num_tens;
    
    num_fives = num_bills(withdraw_amount, 5);
    withdraw_amount -= 5 * num_fives;
    
    num_ones = num_bills(withdraw_amount, 1);
    withdraw_amount -= num_ones;
    
    // console output //
    printf("You received %i hundred(s)\n", num_hundreds);
    printf("You received %i fifty(s)\n", num_fifties);
    printf("You received %i twenty(s)\n", num_twenties);
    printf("You received %i ten(s)\n", num_tens);
    printf("You received %i five(s)\n", num_fives);
    printf("You received %i one(s)\n", num_ones);

    // end program
    return 0;
}

int num_bills(int amount_left, int bill_type)
{
    // calculates the number of bills of the specified type you need
    return amount_left / bill_type; // use int division
}