AM_CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations   \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long    \
            -Wstrict-prototypes -Werror -fprofile-arcs -ftest-coverage    \
	    -fprofile-generate -g -I../src/ -I/usr/local/include -p -pg   \
	    -O0
AM_LDFLAGS = -fprofile-arcs -ftest-coverage -L/usr/local/lib -lcunit -lgcov
pontifex_test_CFLAGS = -DPONTIFEX_TEST_VECTORS=\"@abs_builddir@/vectors\" \
		       $(AM_CFLAGS)
include_HEADERS = *.h
check_PROGRAMS = deck_test card_test pontifex_test
card_test_SOURCES = ../src/card.c card_test.c
deck_test_SOURCES = ../src/deck.c ../src/card.c ../src/util.c deck_test.c
pontifex_test_SOURCES = ../src/card.c ../src/deck.c ../src/pontifex.c \
			../src/util.c pontifex_test.c
dist_noinst_DATA = vectors/*
