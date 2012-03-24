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

void
round1(struct std_deck *deck)
{
    struct card_s joker;
    int position;
        
    joker = card_read((char *)"OA");
    position = deck_seek(deck, &joker);
    deck_shift_down(deck, position, 1);
}

void
round2(struct std_deck *deck)
{
    struct card_s joker;
    int position;
        
    joker = card_read((char *)"OB");
    position = deck_seek(deck, &joker);
    deck_shift_down(deck, position, 2);
}

