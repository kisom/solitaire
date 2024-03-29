/****************************************************************************
 * file: card.c                                                             *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Definition and utility functions for a card in the solitaire cipher.     *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include <assert.h>
#include <string.h>

#include "card.h"

void 
card_str(struct card_s card, char *card_out)
{
    card_out[0] = 0x00;
    card_out[1] = 0x00;
    card_out[2] = 0x00;

    switch (card.face) {
        case TWO:
            card_out[0] = '2';
            break;
        case THREE:
            card_out[0] = '3';
            break;
        case FOUR:
            card_out[0] = '4';
            break;
        case FIVE:
            card_out[0] = '5';
            break;
        case SIX:
            card_out[0] = '6';
            break;
        case SEVEN:
            card_out[0] = '7';
            break;
        case EIGHT:
            card_out[0] = '8';
            break;
        case NINE:
            card_out[0] = '9';
            break;
        case TEN:
            card_out[0] = '0';
            break;
        case JACK:
            card_out[0] = 'J';
            break;
        case QUEEN:
            card_out[0] = 'Q';
            break;
        case KING:
            card_out[0] = 'K';
            break;
        case ACE:
            card_out[0] = 'A';
            break;
        case JOKER:
            card_out[0] = 'O';
            break;
        default:
            /* the impossible
             * has happened. call washington,
             * terrorists at work!
             */
            card_out[0] = 0x0;
            break;
    }

    switch (card.suite) {
        case SPADE:
            card_out[1] = 'S';
            break;
        case CLUB:
            card_out[1] = 'C';
            break;
        case HEART:
            card_out[1] = 'H';
            break;
        case DIAMOND:
            card_out[1] = 'D';
            break;
        case FIRST:
            card_out[1] = 'A';
            break;
        case SECOND:
            card_out[1] = 'B';
            break;
        default:
            /* critical alert:
             * this shouldn't ever happen!
             * assert false, debug!
             */
            card_out[1] = 0x0;
            break;
            assert(0);
    }

    /* make sure the Jokers are treated properly */
    if (card.face == JOKER && !((card.suite == FIRST) ||
                                (card.suite == SECOND)))
        card_out[0] = 0x0;

    if (((card.suite == FIRST) || (card.suite == SECOND)) &&
        (!card.face == JOKER))
        card_out[0] = 0x0;
    return;
}

struct card_s 
card_read(char *strcard)
{
    struct card_s card;
    assert(strcard[2] == 0x00);

    switch (strcard[0]) {
        case '2':
            card.face = TWO;
            break;
         case '3':
            card.face = THREE;
            break;
         case '4':
            card.face = FOUR;
            break;
         case '5':
            card.face = FIVE;
            break;
         case '6':
            card.face = SIX;
            break;
         case '7':
            card.face = SEVEN;
            break;
         case '8':
            card.face = EIGHT;
            break;
         case '9':
            card.face = NINE;
            break;
         case '0':
            card.face = TEN;
            break;
         case 'J':
            card.face = JACK;
            break;
         case 'Q':
            card.face = QUEEN;
            break;
         case 'K':
            card.face = KING;
            break;
         case 'A':
            card.face = ACE;
            break;
        case 'O':
            card.face = JOKER;
            break;
         default:
            /* should never happen */
            card.face = INVALID_FACE;
            break;
    }

    switch (strcard[1]) {
        case 'S':
            card.suite = SPADE;
            break;
        case 'C':
            card.suite = CLUB;
            break;
        case 'H':
            card.suite = HEART;
            break;
        case 'D':
            card.suite = DIAMOND;
            break;
        case 'A':
            card.suite = FIRST;
            break;
        case 'B':
            card.suite = SECOND;
            break;
        default:
            /* should never happen */
            card.suite = INVALID_SUITE;
            break;
    }

    /* make sure the Jokers are treated properly */
    if (card.face == JOKER && !((card.suite == FIRST) ||
                                (card.suite == SECOND))) {
        card.face = INVALID_FACE;
        card.suite = INVALID_SUITE;
    }

    if (((card.suite == FIRST) || (card.suite == SECOND)) &&
        (!card.face == JOKER)) {
        card.face = INVALID_FACE;
        card.suite = INVALID_SUITE;
    }



    return card;
}

int 
card_is_valid(struct card_s *card)
{
    int valid = 1;
    if ((card->face == 0) && (card->face == 0))
        valid = 0;
    else if ((card->face == INVALID_FACE) || (card->suite == INVALID_SUITE))
        valid = 0;
    else if ((card->face == JOKER) && !((card->suite == FIRST) ||
                                        (card->suite == SECOND)))
        valid = 0;
    else if (((card->suite == FIRST) || (card->suite == SECOND)) &&
             (card->face != JOKER))
        valid = 0;
    else if (!((card->face == TWO)           ||
               (card->face == THREE)         ||
               (card->face == FOUR)          ||
               (card->face == FIVE)          ||
               (card->face == SIX)           ||
               (card->face == SEVEN)         ||
               (card->face == EIGHT)         ||
               (card->face == NINE)          ||
               (card->face == TEN)           ||
               (card->face == JACK)          ||
               (card->face == QUEEN)         ||
               (card->face == KING)          ||
               (card->face == ACE)           ||
               (card->face == JOKER)))
        valid = 0;
    else if (!((card->suite == SPADE)        ||
               (card->suite == CLUB)         ||
               (card->suite == HEART)        ||
               (card->suite == DIAMOND)      ||
               (card->suite == FIRST)        ||
               (card->suite == SECOND)))
        valid = 0;
    else
        valid = 1;

    return valid;
}

int
card_cmp(struct card_s *card1, struct card_s *card2)
{
    int match = 0;
    if (card1->face > card2->face)
        match = 1;
    else if (card1->face < card2->face)
        match = -1;
    return match;
}

int
cards_eq(struct card_s *card1, struct card_s *card2)
{
    int match = 1;
    if (card1->face != card2->face)
        match = 0;
    else if (card1->suite != card2->suite)
        match = 0;

    return match;
}
