/****************************************************************************
 * file: pontifex.h                                                         *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * In the book Cryptonomicon by Neil Stephenson, the solitaire algorith is  *
 * referred to as 'Pontifex'; for the purposes of disambiguation, the       *
 * implementation of the cipher in this software package is named Pontifex  *
 * and the front end is named Solitaire.                                    *
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

#ifndef __SOLITAIRE_PONTIFEX_H
#define __SOLITAIRE_PONTIFEX_H

#include "card.h"
#include "deck.h"

/*
 * function declarations
 */

struct std_deck *load_deck_from_file(char *);
int card_value(struct card_s *);
int card_cut_value(struct card_s *);
void pontifex_round1(struct std_deck *);
void pontifex_round2(struct std_deck *);
void pontifex_round3(struct std_deck *);
void pontifex_round4(struct std_deck *);
struct card_s pontifex_round5(struct std_deck *);

#endif
