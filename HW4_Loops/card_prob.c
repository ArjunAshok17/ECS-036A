/**
 * PROGRAM DESCRIPTION
 * This program will calculate the exact (as precise as floating point precision will allow, anyway)
 * probability of drawing a certain card from a specified deck of cards by a designated turn number
*/

#include <stdio.h>

double prob_draw_open(int num_deck_cards, int hand_size, int num_copies);
double prob_draw_mull(int num_deck_cards, int hand_size, int mull_size, int num_copies);
double prob_draw_turn(int num_deck_cards, int hand_size, int num_copies, int turn_limit);

int main(void)
{
    // variable declaration //
    int num_deck_cards, num_mull_cards, num_copies, hand_size, turn_limit;
    double prob;

    // user input //
    printf("Enter how many total cards there are in the deck: ");
    scanf(" %i", &num_deck_cards);

    printf("Enter how many copies of the card that you are looking for are in the deck: ");
    scanf(" %i", &num_copies);

    printf("Enter your initial hand size: ");
    scanf(" %i", &hand_size);

    printf("Enter how many cards you are mulliganing: ");
    scanf(" %i", &num_mull_cards);

    printf("Enter what turn you want to draw the card by: ");
    scanf(" %i", &turn_limit);

    // calculations //
    prob = 1 - (prob_draw_open(num_deck_cards, hand_size, num_copies) 
                * prob_draw_mull(num_deck_cards, hand_size, num_mull_cards, num_copies) 
                * prob_draw_turn(num_deck_cards, hand_size, num_copies, turn_limit));

    // output //
    printf("The probability of drawing at least one of the cards by turn %i given you mulliganed %i cards is %.2lf\n",
           turn_limit, num_mull_cards, prob);

    // end program
    return 0;
}

/**
 * Calculates the probability of drawing the card while creating your opening hand
 * @param num_deck_cards: total number of cards in the deck
 * @param hand_size: number of cards that are initially drawn
 * @param num_copies: number of copies of the card in the deck
 * @return: probability of drawing the card in the opening hand
*/
double prob_draw_open(int num_deck_cards, int hand_size, int num_copies)
{
    double probability = 1;

    for (int i = 0; i < hand_size; i++)
    {
        probability *= ((double) (num_deck_cards - num_copies)) / num_deck_cards;
        num_deck_cards--;
    }

    return probability;
}

/**
 * Calculates the probability of drawing the card in mulligan round
 * @param num_deck_cards: total number of cards in the deck
 * @param hand_size: number of cards that are in hand
 * @param mull_size: number of cards that can be exchanged in the mulligan
 * @param num_copies: number of copies of the card in the deck
 * @return: probability of drawing the card in mulligan round
*/
double prob_draw_mull(int num_deck_cards, int hand_size, int mull_size, int num_copies)
{
    double probability = 1;

    for (int i = 0; i < mull_size; i++)
    {
        probability *= ((double) num_deck_cards - hand_size - num_copies) / (num_deck_cards - hand_size);
        num_deck_cards--;
    }

    return probability;
}

/**
 * Calculates probability of drawing the card in the draw turns before the turn ends
 * @param num_deck_cards: total number of cards in the deck
 * @param hand_size: number of cards that are in hand
 * @param num_copies: number of copies of the card in the deck
 * @param turn_limit: the turn we have to draw the card by
 * @return: probability of drawing the card in the draw turns before the turn ends
*/
double prob_draw_turn(int num_deck_cards, int hand_size, int num_copies, int turn_limit)
{
    double probability = 1;

    for (int i = 0; i < turn_limit; i++)
    {
        probability *= ((double) num_deck_cards - hand_size - num_copies) / (num_deck_cards - hand_size);
        num_deck_cards--;
    }

    return probability;
}