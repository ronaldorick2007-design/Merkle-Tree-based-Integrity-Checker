#include <stdio.h>
#include <string.h>

#include "integrity.h"
#include "blockchain.h"
#include "merkle.h"
#include "input.h"


static int check_integrity(const Chain *c) {
    if(!c->head) { puts("Build a chain first."); return 0; }
    puts("\nRe-enter all candidate transactions in original block/order.");
    puts("The stored chain will not be modified.");
    size_t nb;
    if(!number("Number of candidate blocks: ",1,MAX_BLOCKS,&nb)) return 0;
    int ok=(nb==c->count);
    if(nb!=c->count) printf("Block count mismatch: stored %zu, entered %zu\n",c->count,nb);
    unsigned char candidate_prev[HS]={0};
    size_t common=nb<c->count?nb:c->count;
    for(size_t i=0;i<nb;i++) {
        char tx[MAX_TX][TX_SIZE]={{0}}; size_t nt;
        printf("\n--- Candidate block %zu ---\n",i);
        if(!input_txs(tx,&nt)) { puts("Invalid input; check stopped."); return 0; }
        if(i>=common) { printf("Block %zu is extra.\n",i); ok=0; continue; }
        Block *stored=find_block(c,i);
        unsigned char root[HS], bh[HS];
        if(!stored || !merkle_root(tx,nt,root,NULL)) { ok=0; continue; }
        block_hash(i,candidate_prev,root,bh);
        int count_ok=(nt==stored->tx_count);
        int root_ok=count_ok && memcmp(root,stored->root,HS)==0;
        int prev_ok=memcmp(stored->prev_hash,candidate_prev,HS)==0;
        int hash_ok=memcmp(bh,stored->hash,HS)==0;
        printf("Transaction count: %s\n",count_ok?"MATCH":"MISMATCH");
        printf("Merkle root:       %s\n",root_ok?"MATCH":"MISMATCH");
        printf("Previous link:     %s\n",prev_ok?"MATCH":"MISMATCH");
        printf("Block hash:        %s\n",hash_ok?"MATCH":"MISMATCH");
        if(count_ok && root_ok && prev_ok && hash_ok) printf("Block %zu: VALID\n",i);
        else { printf("Block %zu: MISMATCH / POSSIBLE TAMPERING\n",i); ok=0; }
        memcpy(candidate_prev,bh,HS);
    }
    if(ok && nb==c->count) puts("\nFINAL: INTEGRITY VERIFIED — all data matches.");
    else puts("\nFINAL: INTEGRITY CHECK FAILED — data/order/count differs from stored chain.");
    return ok && nb==c->count;
}