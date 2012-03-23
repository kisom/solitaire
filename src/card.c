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
        case ONE:
            card_out[0] = '1';
            break;
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
        default:
            /* critical alert:
             * this shouldn't ever happen!
             * assert false, debug!
             */
            card_out[1] = 0x0;
            break;
            assert(0);
    }
    return;
}

struct card_s 
card_read(char *strcard)
{
    struct card_s card;
    assert(strcard[2] == 0x00);

    switch (strcard[0]) {
        case '1':
            card.face = ONE;
            break;
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
        default:
            /* should never happen */
            card.suite = INVALID_SUITE;
            break;
    }

    return card;
}

