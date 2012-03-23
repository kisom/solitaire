/****************************************************************************
 * file: card_test.c                                                        *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Unit tests for the card implementation.                                  *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include <CUnit/CUnit.h>
#include "CUnit/Basic.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "card_test.h"
#include "card.h"

/*
 * suite set up functions
 * as of now, the card doesn't require any fancy set up
 */
int initialise_card_test() 
{ 
    return 0; 
}

int 
cleanup_card_test() 
{ 
    return 0; 
}

/*
 * the actual unit tests
 */

void
test_card_read(void)
{
    struct card_s card;
    struct card_s refcardJH, refcardOS;
    char JH[3] = { 'J', 'H', 0x00 };
    char OS[3] = { 'O', 'S', 0x00 };

    refcardJH.suite = HEART;
    refcardJH.face = JACK;

    refcardOS.suite = SPADE;
    refcardOS.face = JOKER;
    
    card = card_read(JH);
    CU_ASSERT(refcardJH.suite == card.suite);
    CU_ASSERT(refcardJH.face == card.face);

    card = card_read(OS);
    CU_ASSERT(refcardOS.suite == card.suite);
    CU_ASSERT(refcardOS.face == card.face);
}

void
test_card_str(void)
{
    struct card_s refcardJH, refcardOS;
    char refJH[3] = { 'J', 'H', 0x00 };
    char refOS[3] = { 'O', 'S', 0x00 };
    char card[3];

    refcardJH.suite = HEART;
    refcardJH.face = JACK;

    refcardOS.suite = SPADE;
    refcardOS.face = JOKER;

    card_str(refcardJH, card);
    CU_ASSERT(0 == strncmp(card, refJH, 0x2));

    card_str(refcardOS, card);
    CU_ASSERT(0 == strncmp(card, refOS, 0x2));
}

void destroy_test_registry()
{
    CU_cleanup_registry();
    exit(CU_get_error());
}

int
main(void)
{
    CU_pSuite card_suite = NULL;

    printf("starting tests for card...\n");

    if (! CUE_SUCCESS == CU_initialize_registry()) {
        fprintf(stderr, "error initialising CUnit test registry!\n");
        return EXIT_FAILURE;
    }

    /* set up the suite */
    card_suite = CU_add_suite("card_tests", initialise_card_test,
                                            cleanup_card_test);
    if (NULL == card_suite)
        destroy_test_registry();

    /* add tests */
    if (NULL == CU_add_test(card_suite, "test of card_read", test_card_read))
        destroy_test_registry();
    if (NULL == CU_add_test(card_suite, "test of card_str", test_card_str))
        destroy_test_registry();



    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    destroy_test_registry();

    /* should never get here! */
    return EXIT_FAILURE;
}

