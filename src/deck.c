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

#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include "deck.h"
#include "util.h"

static char new_deck[54][3] = {
    "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "0S", "JS", "QS", "KS",
    "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "0C", "JC", "QC", "KC",
    "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "0H", "JH", "QH", "KH",
    "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "0D", "JD", "QD", "KD",
    "AS", "AC", "AH", "AD", "OA", "OB"
};
static void destroy_ptr(void *);

void
destroy_ptr(void *ptr)
{
    free(ptr);
    ptr = NULL;
}


struct std_deck 
build_new_deck() {
    int i = 0;
    struct std_deck deck;

    for (i = 0; i < DECK_SIZE; ++i)
        deck.cards[i] = card_read(new_deck[i]);

    return deck;
}


struct std_deck *
load_deck_from_file(char *filename)
{
    FILE *stream = NULL;
    struct std_deck *deck;
    char *buffer, *buf_head;
    int i;
    size_t read_size;

    deck = calloc(1, sizeof(struct std_deck));
    buffer = calloc((DECK_SIZE * 3) + 1, sizeof(char));
    if ((NULL == calloc) || (NULL == buffer)) {
        perror("calloc");
        err(EX_OSERR, "fatal memory allocation error!\n");
    }   

    stream = fopen(filename, "r");
    if (NULL == stream) {
        destroy_ptr(deck);
        destroy_ptr(buffer);
        perror("fopen");
        err(EX_NOINPUT, "could not open %s\n", filename);
    }

    read_size = fread(buffer, sizeof(char), DECK_SIZE * 3, stream);
    if (read_size < (DECK_SIZE * 3)) {
        destroy_ptr(deck);
        destroy_ptr(buffer);       
        err(EX_DATAERR, "short read: %u instead of %u!\n",
                (unsigned int)read_size,
                (unsigned int)DECK_SIZE * 3);
    }

    for (i = 0; i < (DECK_SIZE * 3); ++i)
        if (buffer[i] == 0x0a)
            buffer[i] = 0x00;
    buf_head = buffer;

    for (i = 0; i < DECK_SIZE; ++i) {
        deck->cards[i] = card_read(buf_head);
        buf_head += 3;
    }
    
    free(buffer);
    buffer = NULL;
    buf_head = NULL;

    if (!deck_is_valid(deck)) {
        warnx("invalid deck!");
        free(deck);
        deck = NULL;
    }

    return deck;
}


int
store_deck_to_file(struct std_deck *deck, char *filename)
{
    char card[3];
    int i;
    int status = EXIT_FAILURE;
    FILE *fstream;

    fstream = fopen(filename, "w");
    if (NULL == fstream) {
        perror("fopen");
        return status;
    }

    for (i = 0; i < DECK_SIZE; ++i) {
        card[0] = 0x0;
        card[1] = 0x0;
        card_str(deck->cards[i], card);
        fprintf(fstream, "%s\n", card);
    }

    if (-1 == fclose(fstream))
        perror("fclose");
    else
        status = EXIT_SUCCESS;

    return status;
}


int 
deck_seek(struct std_deck *deck, struct card_s *card)
{
    int position = 0;
    
    while (! cards_eq(&deck->cards[position], card))
        position = (position + 1) % DECK_SIZE;

    return position;
}

void shuffle_round(struct std_deck *deck) {
    struct card_s temporary_card;
    int i, j;
    int swap_position;

    for (j = 0; j < 3; ++j) {
        for (i = 0; i < DECK_SIZE; ++i) {
            swap_position = abs((int)random_byte() % DECK_SIZE);
            temporary_card = deck->cards[i];
            if (cards_eq(&temporary_card, &deck->cards[swap_position]))
                continue;
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

    if (NULL == deck)
        return 0;

    for (i = 0; i < DECK_SIZE; i++) {
        if (!card_is_valid(&deck->cards[i])) {
            warnx("invalid card!");
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
    
    deck->cards[DECK_SIZE - 1] = top_card;

    return top_card;
}

void
deck_shift_down(struct std_deck *deck, int position, int places)
{
    struct card_s card;
    int i, shift_position;
    card = deck->cards[position];

    for (i = 0; i < places; ++i) {
        shift_position = (position + 1) % DECK_SIZE;
        deck->cards[position] = deck->cards[shift_position];
        position = shift_position;
        deck->cards[position] = card;
    }
}

void
dump_deck(struct std_deck *deck)
{
    int i;
    char card[3];

    printf(" 0: ");
    for (i = 1; i <= DECK_SIZE; ++i) {
        card_str(deck->cards[i - 1], card);
        printf("%s, ", card);
        if (0 == (i % 10))
            printf("\n%d: ", i);
    }
    printf("\n");
}
    

