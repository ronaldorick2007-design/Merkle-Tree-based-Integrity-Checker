
#ifndef MERKLE_H
#define MERKLE_H

#include "common.h"

void sha(const unsigned char *p, size_t n,
         unsigned char out[HS]);

void hex(const unsigned char *h);

void parent_hash(const unsigned char *a,
                 const unsigned char *b,
                 unsigned char out[HS]);

void block_hash(size_t idx,
                const unsigned char *prev,
                const unsigned char *root,
                unsigned char out[HS]);

int merkle_root(const char tx[][TX_SIZE],
                size_t n,
                unsigned char root[HS],
                unsigned char (**leaves)[HS]);

void show_tree(const Block *b);

#endif
