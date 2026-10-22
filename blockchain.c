#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "blockchain.h"
#include "merkle.h"

//O(1)
void init_chain(Chain *c) {
    c->head = c->tail = NULL; 
    c->count = 0; 
}

//O(N) 
//Initialises an empty chain
void clear_chain(Chain *c) {
    Block *b = c->head;
    while (b) { 
        Block *n = b->next; 
        free(b->leaf_hashes); 
        free(b); 
        b = n; 
    }
    init_chain(c);
}

//O(1)  Standard Block creation time
//Creates a block and Returns it
static Block *make_block(size_t idx, const char tx[][TX_SIZE], size_t n, const unsigned char prev[HS]) {
    Block *b = calloc(1,sizeof *b); 
    if (!b) return NULL;
    b->index = idx; 
    b->tx_count = n;
    memcpy(b->tx,tx,n*TX_SIZE); 
    memcpy(b->prev_hash,prev,HS);
    if (!merkle_root(b->tx,n,b->root,&b->leaf_hashes)) { 
        free(b); 
        return NULL; 
    }
    block_hash(idx,b->prev_hash,b->root,b->hash); 
    return b;
}

//O(1)  Standard Block creation time along with append operation
// Invokes the previous "make_Block" function, gets a created block returned and appends it to the existing chain(inputted as argument)
int append_block(Chain *c, const char tx[][TX_SIZE], size_t n) {
    if (c->count >= MAX_BLOCKS) { 
        puts("Maximum block count reached."); 
        return 0; 
    }
    unsigned char zero[HS]={0};
    const unsigned char *prev = c->tail ? c->tail->hash : zero;
    Block *b = make_block(c->count, tx, n, prev);
    if (!b) { 
        puts("Could not allocate/build block."); 
        return 0; 
    }
    b->prev = c->tail;
    if (c->tail) c->tail->next = b;
    else c->head = b;
    c->tail = b; 
    c->count++; 
    return 1;
}

//O(N)
//Searches for a block with its ID in a chain
Block *find_block(const Chain *c,size_t idx) {
    for(Block *b = c->head; b; b = b->next) 
        if(b->index == idx) return b;
    return NULL;
}

//O(1)   Standard Time to print details of a block
// displays block's details
void show_block(const Block *b) {
    printf("\nBlock #%zu | %zu transaction(s)\n", b->index, b->tx_count);
    for(size_t i=0; i<b->tx_count; i++) printf("  Transaction %zu: %s\n", i+1, b->tx[i]);
    printf("  Previous hash: "); hex(b->prev_hash);
    printf("\n  Merkle root:   "); hex(b->root);
    printf("\n  Block hash:    "); hex(b->hash);
    putchar('\n');
}

//O(N)
//Displays details of every block in the chain. Invokes the previous "show_block" function.
void show_chain(const Chain *c) {
    if(!c->head) { 
        puts("No chain yet. Choose option 1."); 
        return; 
    }
    printf("\n=== CHAIN: %zu BLOCKS ===\n",c->count);
    for(Block *b = c->head; b; b = b->next) {
        show_block(b);
        if(b->next) puts("       <---- doubly linked ---->");
    }
}
