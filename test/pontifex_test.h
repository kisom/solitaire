/****************************************************************************
 * file: pontifex_test.h                                                        *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Unit tests for the card implementation.                                  *
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

#ifndef __SOLITAIRE_pontifex_test_H
#define __SOLITAIRE_pontifex_test_H

#include <CUnit/CUnit.h>

/* suite declarations */
int initialise_pontifex_test(void);
int cleanup_pontifex_test(void);


/* test declarations */
void test_load_deck(void);
void test_card_value(void);
void test_card_cut_value(void);
void test_letter_value(void);
void test_value_letter(void);
void test_round1(void);
void test_round2(void);
void test_round3_little_high(void);
void test_round3_big_high(void);
void test_round4(void);
void test_round5(void);
void test_round(void);

/* other functions */
void destroy_test_registry(void);

#endif
