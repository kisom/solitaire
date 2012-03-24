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

static char new_deck[54][3] = {
    "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "0S", "JS", "QS", "KS",
    "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "0C", "JC", "QC", "KC",
    "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "0H", "JH", "QH", "KH",
    "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "0D", "JD", "QD", "KD",
    "AS", "AC", "AH", "AD", "OA", "OB"
};

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
    int i, j;
    int swap_position;

    for (j = 0; j < 3; ++j) {
        for (i = 0; i < DECK_SIZE; ++i) {
            swap_position = ((int)random_byte() % DECK_SIZE);
            temporary_card = deck->cards[i];
            deck->cards[i] = deck->cards[swap_position];
            deck->cards[swap_position] = temporary_card;
        }
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

struct card_s 
deck_pop(struct std_deck *deck)
{
    struct card_s top_card;
    int i;

    top_card = deck->cards[0];
    for (i = 0; i < (DECK_SIZE - 1); ++i)
        deck->cards[i] = deck->cards[i + 1];
    
    deck->cards[DECK_SIZE] = top_card;

    return top_card;
}

