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

/*
 * Convert the card to a number. As before, use the bridge suits to order
 * them: From lowest to highest, we have clubs, diamonds, hearts, and spades.
 * Hence, A(clubs) through K(clubs) is 1 through 13, A(diamonds) through
 * K(diamonds) is 14 through 26, A(hearts) through K(hearts) is 1 through 13,
 * and A(spades) through K(spades) is 14 through 26.
 */
int 
card_value(struct card_s *card)
{
    int val = 0;
    if (!card_is_valid(card))
        val = -1;
    if (card->face == JOKER)
        val = 0;
    else if ((card->suite == HEART) || (card->suite == SPADE))
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

int 
pontifex_letter_value(char letter)
{
    int value;

    if (letter > 'z')
        value = 0;
    else if (letter >= 'a')
        value = letter - 0x60;
    else if (letter > 'Z')
        value = 0;
    else if (letter >= 'A')
        value = letter - 0x40;
    else
        value = 0;

    return value;
}

char
pontifex_value_letter(int value)
{
    char letter = 0x00;

    if ((value > 0) && (value < 27))
        letter = value + 0x40;

    return letter;
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
    struct std_deck cut_deck;
    int cut_value, i, deck_position;

    cut_value = card_cut_value(&deck->cards[DECK_SIZE - 1]);
    deck_position = 0;

    for (i = cut_value; i < (DECK_SIZE - 1); ++i)
        cut_deck.cards[deck_position++] = deck->cards[i];

    for (i = 0; i < cut_value; ++i)
        cut_deck.cards[deck_position++] = deck->cards[i];

    for (i = 0; i < (DECK_SIZE - 1); ++i)
        deck->cards[i] = cut_deck.cards[i];

}

/*
 * Find the output card. Look at the top card. Convert it into a number from 1
 * through 53, in the same manner as above. Count down that many cards. (Count
 * the top card as number one.) Write the card after the one you counted to on
 * a piece of paper. (If you hit a joker, don't write anything down and start
 * over again with step 1.) This is the first output card. Note that this step
 * does not modify the state of the deck.
 */
struct card_s
pontifex_round5(struct std_deck *deck)
{
    struct card_s output_card;
    int output_card_val;

    output_card_val = card_cut_value(&deck->cards[0]);
    output_card = deck->cards[output_card_val];

    if (output_card.face == JOKER) {
        output_card.face  = INVALID_FACE;
        output_card.suite = INVALID_SUITE;
    }

    return output_card;
}

/*
 * carry out steps 1-6
 */
int
pontifex_round(struct std_deck *deck)
{
    struct card_s output_card;
    int value;

    pontifex_round1(deck);
    pontifex_round2(deck);
    pontifex_round3(deck);
    pontifex_round4(deck);

    output_card = pontifex_round5(deck);
    value = card_value(&output_card);
    return value;
}
