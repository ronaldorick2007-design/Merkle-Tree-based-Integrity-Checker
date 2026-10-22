#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "merkle.h"
#include "blockchain.h"
#include "integrity.h"
#include "input.h"


static int build_chain(Chain *c) {
    size_t nblocks;
    if (!number("How many blocks? ",1,MAX_BLOCKS,&nblocks)) return 0;
    clear_chain(c);
    for (size_t i=0;i<nblocks;i++) {
        char tx[MAX_TX][TX_SIZE]={{0}}; size_t n;
        printf("\n--- Block %zu ---\n",i);
        if (!input_txs(tx,&n) || !append_block(c,tx,n)) {
            puts("Build cancelled; partial chain discarded."); clear_chain(c); return 0;
        }
    }
    printf("Built %zu blocks successfully.\n",c->count); return 1;
}


static void recent_txs(const Chain *c) {
    if(!c->tail) { puts("Build a chain first."); return; }
    size_t wanted;
    if(!number("How many recent transactions (1-50)? ",1,50,&wanted)) return;
    size_t shown=0;
    puts("\n=== RECENT TRANSACTIONS ===");
    for(Block *b=c->tail;b && shown<wanted;b=b->prev)
        for(size_t i=b->tx_count;i>0 && shown<wanted;i--) {
            printf("Block #%zu | %s\n",b->index,b->tx[i-1]); shown++;
        }
    printf("Displayed %zu transaction(s).\n",shown);
}

int main(void) {
    Chain chain; init_chain(&chain);
    char input[40];
    for(;;) {
        puts("\n========================================");
        puts("     MERKLE CHAIN INTEGRITY CHECKER");
        puts("========================================");
        puts("1. Build chain and feed transactions");
        puts("2. Add a new block");
        puts("3. Display all blocks and hashes");
        puts("4. Display a block's Merkle tree");
        puts("5. Retrieve recent transactions");
        puts("6. Check integrity by re-entering data");
        puts("0. Exit");
        if(!line("Choose option: ",input,sizeof input)) break;
        char *end=NULL; long choice=strtol(input,&end,10);
        if(!input[0] || end==input || *end) { puts("Invalid menu option."); continue; }
        switch(choice) {
            case 1: build_chain(&chain); break;
            case 2: {
                if(!chain.head) { puts("Build a chain first."); break; }
                char tx[MAX_TX][TX_SIZE]={{0}}; size_t n;
                if(input_txs(tx,&n) && append_block(&chain,tx,n))
                    printf("Added block #%zu.\n",chain.tail->index);
                break;
            }
            case 3: show_chain(&chain); break;
            case 4: {
                if(!chain.head) { puts("Build a chain first."); break; }
                size_t idx;
                if(number("Block index: ",0,chain.count-1,&idx)) show_tree(find_block(&chain,idx));
                break;
            }
            case 5: recent_txs(&chain); break;
            case 6: check_integrity(&chain); break;
            case 0: clear_chain(&chain); puts("Goodbye."); return 0;
            default: puts("Choose a number from 0 to 7.");
        }
    }
    clear_chain(&chain); return 0;
}
