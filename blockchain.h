#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include "common.h"

// Purpose: Initializes an empty blockchain.
// Time Complexity: O(1).
void init_chain(Chain *c);

// Purpose: Frees the memory allocated for the blockchain.
// Time Complexity: O(n), where n is the number of blocks.
void clear_chain(Chain *c);

// Purpose: Creates and appends a new block containing transactions.
// Time Complexity: O(n), where n is the number of transactions.
int append_block(Chain *c,
                 const char tx[][TX_SIZE],
                 size_t n);

// Purpose: Finds a block using its index.
// Time Complexity: O(n), where n is the number of blocks.
Block *find_block(const Chain *c, size_t idx);

// Purpose: Displays the details of a single block.
// Time Complexity: O(n), where n is the number of transactions in the block.
void show_block(const Block *b);

// Purpose: Displays all blocks in the blockchain.
// Time Complexity: O(n), where n is the number of blocks.
void show_chain(const Chain *c);

#endif
