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
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
/*#include <unistd.h>*/

#include "card.h"
#include "deck.h"

#include "config.h"

static int  store_deck(struct std_deck *, char *);
static void deckgen_usage(void);
static void deckgen_version(void);

extern char *__progname;

int
main(int argc, char **argv)
{
    int ch, retcode, rounds = 1;
    char *filename = NULL;
    struct std_deck deck;

    /* options descriptor */
    static struct option longopts[] = {
            { "help",      no_argument,        NULL,   'h' },
            { "version",   no_argument,        NULL,   'v' },
            { "numrounds", required_argument,  NULL,   'n' },
            { NULL,        0,                  NULL,   0 }
    };

    while ((ch = getopt_long(argc, argv, "hn:v", longopts, NULL)) != -1) {
        switch (ch) {
            case 'h':
                deckgen_usage();
                break;
            case 'n':
                rounds = atoi(optarg);
                break;
            case 'v':
                deckgen_version();
                break;
            default:
                /* should not be here */
                break;
        }
    }
    
    argc -= optind;
    argv += optind;

    filename = argv[0];
    
    if (NULL == filename) {
        deckgen_usage();
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

void
deckgen_usage()
{
    printf("usage: %s [options] filename\n", __progname);
    printf("\noptions:\n\t--help, -h\t\tprint this usage message\n");
    printf("\t--numrounds, -n <int>\tspecify number of rounds to ");
    printf("shuffle the deck\n");
    printf("\t--version, -v\t\tshow the version, author, and license\n");
    printf("\n\n\tfilename\t\tthe filename to store the deck to.\n");
    printf("\n\tReport bugs to: %s", PACKAGE_BUGREPORT);
    printf("\n\t%s's homepage: %s\n", PACKAGE_NAME, PACKAGE_URL);
    exit(EXIT_SUCCESS);
}

void 
deckgen_version()
{
    printf("%s\n", PACKAGE_STRING);
    printf("%s\n", PACKAGE_COPYRIGHT);
    printf("%s %s\n", PACKAGE_LICENSE, PACKAGE_LICENSE_URL);

    exit(EXIT_SUCCESS);
}
