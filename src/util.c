/****************************************************************************
 * file: card.c                                                             *
 * author: kyle isom <coder@kyleisom.net>                                   *
 *                                                                          *
 * Definition and utility functions for a card in the solitaire cipher.     *
 *                                                                          *
 * it is released under an ISC / public domain dual-license; see any of the *
 * header files or the file "LICENSE" (or COPYING) under the project root.  *
 ****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "util.h"

int
get_random(int bytes, char *buffer)
{

    int bytes_remain = bytes;
    int position = 0;
    int tmp_read;
   

    while (bytes_remain > 0) {
        if (bytes_remain >= RANDOM_BLOCK_SZ) {
            tmp_read = random_block(buffer + position);
            if (tmp_read > 0) {
                position += tmp_read;
                bytes_remain -= tmp_read;
                tmp_read = 0;
            }
        } else {
            char byte = random_byte();
            buffer[position++] = byte;
            bytes_remain--;
        }
    }

    return bytes - bytes_remain;

}
int random_block(char *buffer) {
    FILE *devrandom = NULL;
    char block[RANDOM_BLOCK_SZ];
    int read = 0;
    int wrote = 0;

    devrandom = fopen(DEV_RANDOM, "r");
    if (NULL == devrandom)
        return -1;

    read = (int)fread(block, sizeof(char), RANDOM_BLOCK_SZ, devrandom);
    strncpy(buffer, block, read);

    if (! 0 == fclose(devrandom))
        fprintf(stderr, "Error closing %s!\n", DEV_RANDOM);

    return read;
 }

char random_byte() {
    FILE *devrandom = NULL;
    char byte = 0x0;
    int read = 0;

    devrandom = fopen(DEV_RANDOM, "r");
    if (NULL == devrandom)
        return -1;

    read = fread(&byte, sizeof(byte), 1, devrandom);
    if (read != 1)
        fprintf(stderr, "*** WARNING: invalid read size from %s\n",
                DEV_RANDOM);

    if (! 0 == fclose(devrandom))
        fprintf(stderr, "Error closing %s!\n", DEV_RANDOM);
    return byte;
}

