AM_CFLAGS = -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations   \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long    \
            -Wstrict-prototypes -Werror -g -O0
include_HEADERS = *.h
bin_PROGRAMS = deckgen solitaire
deckgen_SOURCES = deck.c card.c deckgen.c util.c
solitaire_SOURCES = util.c pontifex.c card.c deck.c solitaire.c

