/****************************************************************************
 * file: pontifex_test.c                                                    *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Unit tests for the cipher implementation.                                *
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
#include "pontifex.h"
#include "pontifex_test.h"
#include "config.h"

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
    deck1 =load_deck_from_file(test_deck1);
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
    struct card_s card10 = card_read("0S");
    struct card_s card16 = card_read("3D");
    struct card_s card05 = card_read("0S");
    struct card_s card02 = card_read("2C");
    struct card_s card14 = card_read("AD");
    struct card_s card20 = card_read("7H");
    struct card_s card00 = card_read("OA");
    struct card_s card19 = card_read("6D");
    struct card_s cardNO = card_read("FF");

    CU_ASSERT(10 == card_value(&card10));
    CU_ASSERT(16 == card_value(&card16));
    CU_ASSERT( 5 == card_value(&card05));
    CU_ASSERT( 2 == card_value(&card02));
    CU_ASSERT(14 == card_value(&card14));
    CU_ASSERT(20 == card_value(&card20));
    CU_ASSERT( 0 == card_value(&card00));
    CU_ASSERT(19 == card_value(&card19));
    CU_ASSERT(-1 == card_value(&cardNO));
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

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    fails = CU_get_number_of_tests_failed();

    CU_cleanup_registry();

    /* should never get here! */
    return fails;
}

