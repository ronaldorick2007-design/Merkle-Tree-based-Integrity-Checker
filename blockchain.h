
#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "common.h"

void init_chain(Chain *c);
void clear_chain(Chain *c);

int append_block(Chain *c,
                 const char tx[][TX_SIZE],
                 size_t n);

Block *find_block(const Chain *c, size_t idx);

void show_block(const Block *b);
void show_chain(const Chain *c);

#endif
