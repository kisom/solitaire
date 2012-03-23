AM_CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations   \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long    \
            -Wstrict-prototypes -g -I../src/ -O0
AM_LDFLAGS = -L/usr/local/lib -lcunit
check_PROGRAMS = deck_test card_test pontifex_test
card_test_SOURCES = ../src/card.c card_test.c
deck_test_SOURCES = ../src/deck.c ../src/card.c deck_test.c
pontifex_test_SOURCES = ../src/card.c ../src/deck.c ../src/pontifex.c \
			pontifex_test.c


