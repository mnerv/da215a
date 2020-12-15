/*
 * guess_nr.h
 *
 * This is a simple game called "Guess the number".
 *
 * Author:  Mathias Beckius
 *
 * Date:    2014-11-28
 */

#include "guess_nr.h"
#include "hmi/hmi.h"
#include <stdio.h>

static uint16_t get_nr(void);
static uint8_t playing_game(uint16_t, uint16_t*);
static void show_result(uint16_t);

/**
 * Let the user make a guess by entering a number.
 * The function never exists before the user has entered a number
 * between 1-100.
 *
 * @return the number that were entered by the user.
 */
static uint16_t get_nr(void) {
    uint16_t input_length;
    uint16_t guessed_nr;
    while (1) {
        input_length = 0;  // UPPGIFT: ändra koden så att 'input_int()' anropas,
                           // returvärdet ska lagras i 'input_length',
                           // 'guessed_nr' ska modifieras av 'input_int()'.
        // if the user entered a number, and if it was between 1 and 100...
        if (input_length > 0 && guessed_nr >= 1 && guessed_nr <= 100) {
            // ...return that number!
            return guessed_nr;
        } else {
            // show error/info message!
            output_msg("Enter a number", "between 1-100!", 1);
        }
    }
}

/**
 * Playing game, until the correct number is guessed!
 *
 * @param rnd_nr: random number (to be guessed)
 * @param p_nr_of_guesses: pointer to variable with the current number of
 * guesses
 *
 * @return Returns 1 if the game should continue, 0 if the game is over.
 */
static uint8_t playing_game(uint16_t rnd_nr, uint16_t* p_nr_of_guesses) {
    uint16_t guessed_nr;

    // let the user guess a number
    guessed_nr = get_nr();
    // keep track of number of guesses
    // UPPGIFT: öka innehållet i variabeln som 'p_nr_of_guesses' pekar på.

    // if the guessed number was the correct number...
    if (guessed_nr == rnd_nr) {
        output_msg("Correct number!", "", 1);
        return 0;                      // return 0 for "game over!"
    } else if (guessed_nr < rnd_nr) {  // number too low?
        output_msg("Too low!", "", 1);
    } else {  // number too high?
        output_msg("Too high!", "", 1);
    }
    return 1;  // return 1 for "keep on playing!"
}

/**
 * Show result (when the game has ended!)
 *
 * @param nr_of_guesses: the number of guesses that was required
 *                  to guess the correct number.
 */
static void show_result(uint16_t nr_of_guesses) {
    char result[17];
    // show result
    sprintf(result, "Guesses: %u", nr_of_guesses);
    output_msg(result, "", 3);
    if (nr_of_guesses <= 7) {
        output_msg("Good job!", "", 3);
    } else {
        output_msg("Better luck", "next time...", 3);
    }
}

/**
 * Play a round of "Guess the number".
 *
 * @param rnd_nr: random number (to be guessed)
 */
void play_guess_nr(uint16_t rnd_nr) {
    uint16_t nr_of_guesses = 0;
    // show initial message, before game starts.
    output_msg("Can you guess", "the number?", 3);
    // play game until the correct number is guessed!
    while (playing_game(rnd_nr, &nr_of_guesses)) {}
    // show result!
    show_result(nr_of_guesses);
}