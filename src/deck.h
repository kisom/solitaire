/****************************************************************************
 * file: deck.c                                                             *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Definition and utility functions for a deck of cards in the solitaire    *
 * cipher.                                                                  *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

/****************************************************************************
 * the ISC license:                                                         *
 * Copyright (c) 2011 Kyle Isom <coder@kyleisom.net>                        * 
 *                                                                          *
 * Permission to use, copy, modify, and distribute this software for any    *
 * purpose with or without fee is hereby granted, provided that the above   *
 * copyright notice and this permission notice appear in all copies.        *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES *
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF         *
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR  *
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES   *
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN    *
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF  *
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.           *
 ****************************************************************************
 * you may choose to follow this license or public domain. my intent with   *
 * dual-licensing this code is to afford you, the end user, maximum freedom *
 * with the software. if public domain affords you more freedom, use it.    *
 ****************************************************************************/

#include "card.h"

#ifndef __SOLITAIRE_DECK_H
#define __SOLITAIRE_DECK_H

#define     DECK_SIZE       54

/*
 * data type declarations
 */

/* 54 card deck: 13x4 suites, plus 2x joker */
struct std_deck {
    struct card_s cards[54];
};

/* 
 * function prototypes 
 */
struct std_deck build_new_deck(void);
struct std_deck *load_deck_from_file(char *);
int store_deck_to_file(struct std_deck *, char *);

int deck_seek(struct std_deck *, struct card_s *);

void shuffle_round(struct std_deck*);
void shuffle(struct std_deck*, int); 
struct card_s deck_pop(struct std_deck *);
void deck_shift_down(struct std_deck *, int, int);

int deck_is_valid(struct std_deck *);
void dump_deck(struct std_deck *);

#endif
