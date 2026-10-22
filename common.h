
#ifndef COMMON_H
#define COMMON_H

#include <stddef.h>

#define MAX_BLOCKS 100
#define MAX_TX 50
#define TX_SIZE 256
#define HS 32

typedef struct Block {
    size_t index, tx_count;

    char tx[MAX_TX][TX_SIZE];

    unsigned char (*leaf_hashes)[HS];
    unsigned char root[HS];
    unsigned char prev_hash[HS];
    unsigned char hash[HS];

    struct Block *prev, *next;
} Block;

typedef struct {
    Block *head, *tail;
    size_t count;
} Chain;

#endif
