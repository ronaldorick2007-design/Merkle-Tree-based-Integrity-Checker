#ifndef MERKLE_H
#define MERKLE_H

#include "common.h"

// Purpose: Calculates the SHA-256 hash of input data.
// Time Complexity: O(n), where n is the input size.
void sha(const unsigned char *p, size_t n,
         unsigned char out[HS]);

// Purpose: Prints a hash in hexadecimal format.
// Time Complexity: O(1), because HS is fixed.
void hex(const unsigned char *h);

// Purpose: Calculates the parent hash from two child hashes.
// Time Complexity: O(1), because hash sizes are fixed.
void parent_hash(const unsigned char *a,
                 const unsigned char *b,
                 unsigned char out[HS]);

// Purpose: Calculates a block hash using its index, previous hash, and Merkle root.
// Time Complexity: O(1), because input size is fixed.
void block_hash(size_t idx,
                const unsigned char *prev,
                const unsigned char *root,
                unsigned char out[HS]);

// Purpose: Calculates the Merkle root from transaction hashes.
// Time Complexity: O(n), where n is the number of transactions.
int merkle_root(const char tx[][TX_SIZE],
                size_t n,
                unsigned char root[HS],
                unsigned char (**leaves)[HS]);

// Purpose: Displays all levels of a block's Merkle tree.
// Time Complexity: O(n), where n is the number of leaf nodes.
void show_tree(const Block *b);

#endif
