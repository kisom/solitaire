/****************************************************************************
 * file: pontifex_test.c                                                    *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Unit tests for the cipher implementation.                                *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

/* need to define _GNU_SOURCE in Linux before loading stdlib */
#include "config.h"

#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>

#include "card.h"
#include "deck.h"
#include "pontifex.h"
#include "pontifex_test.h"

/*
 * the unit tests
 */
void 
test_load_deck()
{
    struct std_deck *deck1;
    char *test_deck1 = NULL;
    int ret;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test1.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    free(deck1);
    free(test_deck1);
    deck1 = NULL;
    test_deck1 = NULL;
    return;
}

void
test_card_value()
{
    struct card_s card23 = card_read((char *)"0S");
    struct card_s card03 = card_read((char *)"3D");
    struct card_s card18 = card_read((char *)"5S");
    struct card_s card02 = card_read((char *)"2C");
    struct card_s card01 = card_read((char *)"AD");
    struct card_s card20 = card_read((char *)"7H");
    struct card_s card00 = card_read((char *)"OA");
    struct card_s card06 = card_read((char *)"6D");
    struct card_s cardNO = card_read((char *)"FF");

    CU_ASSERT(23 == card_value(&card23));
    CU_ASSERT( 3 == card_value(&card03));
    CU_ASSERT(18 == card_value(&card18));
    CU_ASSERT( 2 == card_value(&card02));
    CU_ASSERT( 1 == card_value(&card01));
    CU_ASSERT(20 == card_value(&card20));
    CU_ASSERT( 0 == card_value(&card00));
    CU_ASSERT( 6 == card_value(&card06));
    CU_ASSERT(-1 == card_value(&cardNO));
}

void
test_card_cut_value()
{
    struct card_s card49 = card_read((char *)"0S");
    struct card_s card16 = card_read((char *)"3D");
    struct card_s card44 = card_read((char *)"5S");
    struct card_s card02 = card_read((char *)"2C");
    struct card_s card14 = card_read((char *)"AD");
    struct card_s card33 = card_read((char *)"7H");
    struct card_s card53 = card_read((char *)"OA");
    struct card_s card19 = card_read((char *)"6D");
    struct card_s cardNO = card_read((char *)"FF");

    CU_ASSERT(49 == card_cut_value(&card49));
    CU_ASSERT(16 == card_cut_value(&card16));
    CU_ASSERT(44 == card_cut_value(&card44));
    CU_ASSERT( 2 == card_cut_value(&card02));
    CU_ASSERT(14 == card_cut_value(&card14));
    CU_ASSERT(33 == card_cut_value(&card33));
    CU_ASSERT(53 == card_cut_value(&card53));
    CU_ASSERT(19 == card_cut_value(&card19));
    CU_ASSERT(-1 == card_cut_value(&cardNO));
}


void 
test_round1()
{
    struct std_deck *deck1;
    struct card_s joker;
    char *test_deck1 = NULL;
    int ret, jokerpos;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test2.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    joker = card_read((char *)"OA");
    jokerpos = deck_seek(deck1, &joker);
    CU_ASSERT(50 == jokerpos);

    pontifex_round1(deck1);
    jokerpos = deck_seek(deck1, &joker);
    CU_ASSERT(51 == jokerpos);

    CU_ASSERT(deck_is_valid(deck1));

    free(deck1);
    free(test_deck1);
    deck1 = NULL;
    test_deck1 = NULL;
    return;
}

void 
test_round2()
{
    struct std_deck *deck1;
    struct card_s joker;
    char *test_deck1 = NULL;
    int ret, jokerpos;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test2.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    joker = card_read((char *)"OB");
    jokerpos = deck_seek(deck1, &joker);
    CU_ASSERT(7 == jokerpos);

    pontifex_round2(deck1);
    jokerpos = deck_seek(deck1, &joker);
    CU_ASSERT(9 == jokerpos);

    CU_ASSERT(deck_is_valid(deck1));

    free(deck1);
    free(test_deck1);
    deck1 = NULL;
    test_deck1 = NULL;
    return;
}

void 
test_round3_little_high()
{
    struct std_deck *deck1, *deck2;
    struct card_s little_joker, big_joker;
    char *test_deck1 = NULL;
    char *test_deck2 = NULL;
    int i, ret, joker1pos, joker2pos;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test3.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    ret = asprintf(&test_deck2, "%s/%s", PONTIFEX_TEST_VECTORS, "test3b.deck");
    deck2 = load_deck_from_file(test_deck2);
    CU_ASSERT(deck_is_valid(deck2));

    little_joker = card_read((char *)"OA");
    big_joker = card_read((char *)"OB");

    pontifex_round3(deck1);
    joker1pos = deck_seek(deck1, &little_joker);
    joker2pos = deck_seek(deck2, &little_joker);
    CU_ASSERT(joker1pos == joker2pos);

    joker1pos = deck_seek(deck1, &big_joker);
    joker2pos = deck_seek(deck2, &big_joker);
    CU_ASSERT(joker1pos == joker2pos);

    CU_ASSERT(deck_is_valid(deck1));
    for (i = 0; i < DECK_SIZE; ++i)
        CU_ASSERT(cards_eq(&deck1->cards[i], &deck2->cards[i]));

    free(deck1);
    free(deck2);
    free(test_deck1);
    free(test_deck2);
    deck1 = NULL;
    deck2 = NULL;
    test_deck1 = NULL;
    test_deck2 = NULL;
    return;
}




void 
test_round3_big_high()
{
    struct std_deck *deck1, *deck2;
    struct card_s little_joker, big_joker;
    char *test_deck1 = NULL;
    char *test_deck2 = NULL;
    int i, ret, joker1pos, joker2pos;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test2.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    ret = asprintf(&test_deck2, "%s/%s", PONTIFEX_TEST_VECTORS, "test2b.deck");
    deck2 = load_deck_from_file(test_deck2);
    CU_ASSERT(deck_is_valid(deck2));

    little_joker = card_read((char *)"OA");
    big_joker = card_read((char *)"OB");

    pontifex_round3(deck1);
    joker1pos = deck_seek(deck1, &little_joker);
    joker2pos = deck_seek(deck2, &little_joker);
    CU_ASSERT(joker1pos == joker2pos);

    joker1pos = deck_seek(deck1, &big_joker);
    joker2pos = deck_seek(deck2, &big_joker);
    CU_ASSERT(joker1pos == joker2pos);

    CU_ASSERT(deck_is_valid(deck1));
    for (i = 0; i < DECK_SIZE; ++i)
        CU_ASSERT(cards_eq(&deck1->cards[i], &deck2->cards[i]));

    free(deck1);
    free(deck2);
    free(test_deck1);
    free(test_deck2);
    deck1 = NULL;
    deck2 = NULL;
    test_deck1 = NULL;
    test_deck2 = NULL;
    return;
}

void 
test_round4()
{
    struct std_deck *deck1, *deck2;
    char *test_deck1 = NULL;
    char *test_deck2 = NULL;
    int i, ret;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test4.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    ret = asprintf(&test_deck2, "%s/%s", PONTIFEX_TEST_VECTORS, "test4b.deck");
    deck2 = load_deck_from_file(test_deck2);
    CU_ASSERT(deck_is_valid(deck2));

    pontifex_round4(deck1);

    CU_ASSERT(deck_is_valid(deck1));
    for (i = 0; i < DECK_SIZE; ++i)
        CU_ASSERT(cards_eq(&deck1->cards[i], &deck2->cards[i]));

    free(deck1);
    free(deck2);
    free(test_deck1);
    free(test_deck2);
    deck1 = NULL;
    deck2 = NULL;
    test_deck1 = NULL;
    test_deck2 = NULL;
    return;
}

void 
test_round5()
{
    struct std_deck *deck1;
    struct card_s output_card, expected_output_card;
    char *test_deck1 = NULL;
    int ret;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test4.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    expected_output_card = card_read((char *)"QC");
    output_card = pontifex_round5(deck1);

    CU_ASSERT(deck_is_valid(deck1));
    CU_ASSERT(cards_eq(&output_card, &expected_output_card));

    free(deck1);
    free(test_deck1);
    deck1 = NULL;
    test_deck1 = NULL;
    return;
}

void 
test_round()
{
    struct std_deck *deck1;
    struct card_s output_card, expected_output_card;
    char *test_deck1 = NULL;
    int ret;

    ret = asprintf(&test_deck1, "%s/%s", PONTIFEX_TEST_VECTORS, "test4.deck");
    deck1 = load_deck_from_file(test_deck1);
    CU_ASSERT(deck_is_valid(deck1));

    expected_output_card = card_read((char *)"3D");
    output_card = pontifex_round(deck1);

    CU_ASSERT(deck_is_valid(deck1));
    CU_ASSERT(cards_eq(&output_card, &expected_output_card));

    free(deck1);
    free(test_deck1);
    deck1 = NULL;
    test_deck1 = NULL;
    return;
}


/*
 * suite set up functions
 */
int initialise_pontifex_test() 
{ 
    return 0; 
}

int 
cleanup_pontifex_test() 
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
    CU_pSuite pontifex_suite = NULL;
    unsigned int fails = 0;

    printf("starting tests for pontifex...\n");

    if (! CUE_SUCCESS == CU_initialize_registry()) {
        fprintf(stderr, "error initialising CUnit test registry!\n");
        return EXIT_FAILURE;
    }

    /* set up the suite */
    pontifex_suite = CU_add_suite("pontifex_tests", initialise_pontifex_test,
                                  cleanup_pontifex_test);
    if (NULL == pontifex_suite)
        destroy_test_registry();

    /* add tests */
    if (NULL == CU_add_test(pontifex_suite, "test of load_deck_from_file",
                            test_load_deck))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test of card value", 
                            test_card_value))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test of card cut value", 
                            test_card_cut_value))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test round1", test_round1))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test round2", test_round2))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test round3 / little high", 
                            test_round3_little_high))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test round3 / big high", 
                            test_round3_big_high))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test round4", test_round4))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test round5", test_round5))
        destroy_test_registry();

    if (NULL == CU_add_test(pontifex_suite, "test full round", test_round))
        destroy_test_registry();

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    fails = CU_get_number_of_tests_failed();

    CU_cleanup_registry();

    /* should never get here! */
    return fails;
}

