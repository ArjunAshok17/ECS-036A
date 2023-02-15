#include <stdio.h>

int main(void)
{
    // declare vars //
    char letter_grade;
    double percent_needed, percent_curr, final_weight;
    double test_grade;

    // user input //
    printf("Enter the grade you want in the class: ");
    scanf(" %c", &letter_grade);
    
    printf("Enter the percent you need to get that grade: ");
    scanf(" %lf", &percent_needed);
    
    printf("Enter your current percent in the class: ");
    scanf(" %lf", &percent_curr);
    
    printf("Enter the weight of the final: ");
    scanf(" %lf", &final_weight);
    final_weight /= 100;

    // calculations //
    test_grade = (percent_needed - (percent_curr * (1 - final_weight))) / (final_weight);

    // output //
    printf("You need to get at least %.2lf%% on the final to get a %c in the class.\n", test_grade, letter_grade);

    // end program //
    return 0;
}