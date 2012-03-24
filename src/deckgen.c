/****************************************************************************
 * file: deckgen.c                                                          *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Utility to generate a deck of cards for use with the solitaire cipher.   *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "deckgen.h"
#include "card.h"
#include "deck.h"

static int store_deck(struct std_deck *, char *);

int
main(int argc, char **argv)
{
    int ch, retcode, rounds = 1;
    char *filename = NULL;
    struct std_deck deck;

    while ((ch = getopt(argc, argv, "n:o:")) != -1) {
        switch (ch) {
            case 'n':
                rounds = atoi(optarg);
            case 'o':
                filename = optarg;
                break;
        }
    }
    
    if (NULL == filename) {
        fprintf(stderr, "need to specify a filename with -o!\n");
        exit(EXIT_FAILURE);
    }

    printf("getting a new deck and shuffing %d times...\n", rounds);
    deck = build_new_deck();
    shuffle(&deck, rounds);

    retcode = store_deck(&deck, filename);

    return retcode;
}

int
store_deck(struct std_deck *deck, char *filename)
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
        card_str(deck->cards[i], card);
        fprintf(fstream, "%s\n", card);
    }

    if (-1 == fclose(fstream))
        perror("fclose");
    else
        status = EXIT_SUCCESS;

    return status;
}
