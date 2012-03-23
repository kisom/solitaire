/****************************************************************************
 * file: deck.c                                                             *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Definition and utility functions for a deck of cards in the solitaire    *
 * cipher.                                                                  *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include "deck.h"
#include "util.h"

struct std_deck 
build_new_deck() {
    int i = 0;
    struct std_deck deck;

    for (i = 0; i < DECK_SIZE; ++i)
        deck.cards[i] = card_read(new_deck[i]);

    return deck;
}

void shuffle_round(struct std_deck *deck) {
    struct card_s temporary_card;
    int i;
    int swap_position;

    for (i = 0; i < DECK_SIZE; ++i) {
        swap_position = ((int)random_byte() % DECK_SIZE - 1);
        temporary_card = deck->cards[i];
        deck->cards[i] = deck->cards[swap_position];
        deck->cards[swap_position] = temporary_card;
    }

}
void shuffle(struct std_deck *deck, int rounds) {
    int i = 0;

    while (i++ < rounds) {
        shuffle_round(deck);
    }

    return;
}

int
deck_is_valid(struct std_deck *deck)
{
    int valid = 1;
    int i, j, matches;

    for (i = 0; i < DECK_SIZE; i++) {
        if (!card_is_valid(&deck->cards[i])) {
            valid = 0;
            break;
        }

        matches = 0;

        for (j = 0; j < DECK_SIZE; j++) {
            if (cards_eq(&deck->cards[i], &deck->cards[j]))
                matches++;
        }
        if (matches > 1) {
            valid = 0;
            break;
        }
    }
    return valid;
}
