/****************************************************************************
 * file: deck_test.c                                                        *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Unit tests for the deck implementation.                                  *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "deck.h"
#include "deck_test.h"

/*
 * the unit tests
 */
void 
test_create_deck()
{
    struct std_deck deck1;
    struct std_deck deck2;
    struct card_s card;
    int i;

    deck1 = build_new_deck();
    deck2 = build_new_deck();

    for (i = 0; i < DECK_SIZE; ++i) {
        card = card_read(new_deck[i]);
        CU_ASSERT(cards_eq(&deck1.cards[i], &deck2.cards[i]));
        CU_ASSERT(cards_eq(&deck1.cards[i], &card));
    }

    CU_ASSERT(deck_is_valid(&deck1));
    CU_ASSERT(deck_is_valid(&deck2));
}

void
test_shuffle_round()
{
    int i, runs;
    struct std_deck deck1, deck2;
    deck1 = build_new_deck();
    deck2 = build_new_deck();
    runs = 0;

    shuffle_round(&deck1);
    for (i = 0; i < DECK_SIZE; ++i) {
        if (cards_eq(&deck1.cards[i], &deck2.cards[i]))
            runs++;
    }
    
    /* no more than 1% of cards can be in the same position */
    CU_ASSERT(runs < (0.10 * (double)DECK_SIZE));
}

void
test_shuffle_rounds()
{
    int i, runs;
    struct std_deck deck1, deck2;
    deck1 = build_new_deck();
    deck2 = build_new_deck();
    runs = 0;

    shuffle(&deck1, 10);
    for (i = 0; i < DECK_SIZE; ++i) {
        if (cards_eq(&deck1.cards[i], &deck2.cards[i]))
            runs++;
    }
    
    /* no more than 1% of cards can be in the same position */
    CU_ASSERT(runs < (0.10 * (double)DECK_SIZE));
}


void
test_deck_pop()
{
    int i;
    struct card_s card;
    struct std_deck deck1, deck2;

    deck1 = build_new_deck();
    shuffle(&deck1, 3);

    for (i = 0; i < DECK_SIZE; ++i)
        deck2.cards[i] = deck1.cards[i];

    for (i = 0; i < (DECK_SIZE - 1); ++i) {
        card = deck_pop(&deck1);
        CU_ASSERT(cards_eq(&card, &deck2.cards[i]));
        CU_ASSERT(cards_eq(&deck1.cards[0], &deck2.cards[i + 1]));
    }
}

void 
test_shift_down()
{
    struct std_deck deck1;
    struct card_s card;

    deck1 = build_new_deck();
    card = card_read((char *)"2S");
    deck_shift_down(&deck1, 0, 1);

    CU_ASSERT(cards_eq(&card, &deck1.cards[1]));

    deck_shift_down(&deck1, 1, 2);
    CU_ASSERT(cards_eq(&card, &deck1.cards[3]));
}


/*
 * suite set up functions
 */
int initialise_deck_test() 
{ 
    return 0; 
}

int 
cleanup_deck_test() 
{ 
    return 0; 
}

void destroy_test_registry()
{
    CU_cleanup_registry();
    exit(CU_get_error());
}

int
main(void)
{
    CU_pSuite deck_suite = NULL;
    unsigned int fails = 0;

    printf("starting tests for deck...\n");

    if (! CUE_SUCCESS == CU_initialize_registry()) {
        fprintf(stderr, "error initialising CUnit test registry!\n");
        return EXIT_FAILURE;
    }

    /* set up the suite */
    deck_suite = CU_add_suite("deck_tests", initialise_deck_test,
                                            cleanup_deck_test);
    if (NULL == deck_suite)
        destroy_test_registry();

    /* add tests */
    if (NULL == CU_add_test(deck_suite, "test of build_new_deck", 
                            test_create_deck))
        destroy_test_registry();

    if (NULL == CU_add_test(deck_suite, "test of shuffle_round", 
                            test_shuffle_round))
        destroy_test_registry();

    if (NULL == CU_add_test(deck_suite, "test of deck_pop", 
                            test_deck_pop))
        destroy_test_registry();

    if (NULL == CU_add_test(deck_suite, "test of deck_shift_down",
                           test_shift_down))
        destroy_test_registry();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    fails = CU_get_number_of_tests_failed();

    CU_cleanup_registry();
    return fails;
}

