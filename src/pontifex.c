/****************************************************************************
 * file: pontifex.c                                                         *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * In the book Cryptonomicon by Neil Stephenson, the solitaire algorithm is *
 * referred to as 'Pontifex'; for the purposes of disambiguation, the       *
 * implementation of the cipher in this software package is named Pontifex  *
 * and the front end is named Solitaire.                                    *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>

#include "card.h"
#include "deck.h"
#include "pontifex.h"

static void destroy_ptr(void *);

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

void
destroy_ptr(void *ptr)
{
    free(ptr);
    ptr = NULL;
}

int 
card_value(struct card_s *card)
{
    int val = 0;
    if (!card_is_valid(card))
        val = -1;
    if (card->face == JOKER)
        val = 0;
    else if ((card->suite == HEART) || (card->suite == DIAMOND))
        val = card->face + 13;
    else
        val = card->face;

    return val;
}

int
card_cut_value(struct card_s *card)
{
    int value = 0;

    if (card->face == JOKER)
        value = 53;
    else
        value = card->face;

    switch (card->suite) {
        case DIAMOND:
            value += 13;
            break;
        case HEART:
            value += 26;
            break;
        case SPADE:
            value += 39;
            break;
        default:
            /* jokers and clubs shouldn't be changed */
            break;
    }

    return value;
}

/*
 * Find the A joker. Move it one card down. (That is, swap it with the card 
 * beneath it.)
 */
void
pontifex_round1(struct std_deck *deck)
{
    struct card_s joker;
    int position, shift_by;
        
    joker = card_read((char *)"OA");
    position = deck_seek(deck, &joker);
    if ((DECK_SIZE - 1) == position)
        shift_by = 2;
    else
        shift_by = 1;
    deck_shift_down(deck, position, shift_by);
}

/*
 * Find the B joker. Move it two cards down. If the joker is the bottom card 
 * of the deck, move it just below the second card. If the joker is one up 
 * from the bottom card, move it just below the top card.
 */
void
pontifex_round2(struct std_deck *deck)
{
    struct card_s joker;
    int position;
        
    joker = card_read((char *)"OB");
    position = deck_seek(deck, &joker);
    deck_shift_down(deck, position, 2);
}

/*
 * Perform a triple cut. That is, swap the cards above the first joker with 
 * the cards below the second joker.
 */
void
pontifex_round3(struct std_deck *deck)
{
    struct std_deck cut_deck;
    struct card_s card, joker1, joker2;
    int i, joker1pos, joker2pos, deck_position;
    int above, below;

    joker1 = card_read((char *)"OA");
    joker2 = card_read((char *)"OB");
    joker1pos = deck_seek(deck, &joker1);
    joker2pos = deck_seek(deck, &joker2);

    /* if little joker is below big joker need to shift some things around */
    if (joker1pos > joker2pos) {
        above = joker2pos;
        below = joker1pos;
        card  = joker1;
        joker1 = joker2;
        joker2 = card;
        deck_position = joker1pos;
        joker1pos = joker2pos;
        joker2pos = deck_position;
    } else {
        above = joker1pos;
        below = joker2pos;
    }

    deck_position = 0;
    for (i = below + 1; i < DECK_SIZE; ++i)
        cut_deck.cards[deck_position++] = deck->cards[i];

    cut_deck.cards[deck_position++] = deck->cards[above];
    for (i = above + 1; i < below; ++i)
        cut_deck.cards[deck_position++] = deck->cards[i];

    cut_deck.cards[deck_position++] = deck->cards[below];
    for (i = 0; i < above; ++i)
        cut_deck.cards[deck_position++] = deck->cards[i];

    for (i = 0; i < DECK_SIZE; ++i)
        deck->cards[i] = cut_deck.cards[i];
}

/*
 * Perform a count cut. Look at the bottom card. Convert it into a number from
 * 1 through 53. (Use the bridge order of suits: clubs, diamonds, hearts, and
 * spades. If the card is a (club), it is the value shown. If the card is a
 * (diamond), it is the value plus 13. If it is a (heart), it is the value
 * plus 26. If it is a (spade), it is the value plus 39. Either joker is a 53.)
 * Count down from the top card that number. (I generally count 1 through 13
 * again and again if I have to; it's easier than counting to high numbers
 * sequentially.) Cut after the card that you counted down to, leaving the
 * bottom card on the bottom.
 */
void
pontifex_round4(struct std_deck *deck)
{
    deck_is_valid(deck);
}
