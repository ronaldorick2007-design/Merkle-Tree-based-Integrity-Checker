#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include "merkle.h"

void sha(const unsigned char *p, size_t n, unsigned char out[HS]) {
    SHA256(p, n, out);
}

static void leaf_hash(const char *s, unsigned char out[HS]) {
    size_t n = strlen(s);
    unsigned char *p = malloc(n + 1);
    if (!p) { perror("malloc"); exit(1); }
    p[0] = 0; memcpy(p + 1, s, n); sha(p, n + 1, out); free(p);
}

void parent_hash(const unsigned char *a, const unsigned char *b,
                        unsigned char out[HS]) {
    unsigned char p[1 + 2 * HS]; p[0] = 1;
    memcpy(p + 1, a, HS); memcpy(p + 1 + HS, b, HS);
    sha(p, sizeof p, out);
}
void hex(const unsigned char *h) {
    for (int i=0;i<HS;i++) printf("%02x", h[i]);
}

void block_hash(size_t idx, const unsigned char *prev,
                       const unsigned char *root, unsigned char out[HS]) {
    unsigned char p[8 + 2 * HS];
    uint64_t x = (uint64_t)idx;
    for (int i=0;i<8;i++) p[i]=(unsigned char)(x >> (56 - 8*i));
    memcpy(p+8, prev, HS); memcpy(p+8+HS, root, HS);
    sha(p, sizeof p, out);
}
int merkle_root(const char tx[][TX_SIZE], size_t n,
                       unsigned char root[HS], unsigned char (**leaves)[HS]) {
    if (!n || n > MAX_TX) return 0;
    unsigned char (*lv)[HS] = malloc(n * HS);
    if (!lv) return 0;
    for (size_t i=0;i<n;i++) leaf_hash(tx[i], lv[i]);
    size_t count=n;
    unsigned char (*cur)[HS] = malloc(count * HS);
    if (!cur) { free(lv); return 0; }
    memcpy(cur, lv, count * HS);
    while (count > 1) {
        size_t nn=(count+1)/2;
        unsigned char (*next)[HS] = malloc(nn * HS);
        if (!next) { free(cur); free(lv); return 0; }
        for (size_t i=0;i<nn;i++) {
            size_t l=2*i, r=l+1; if (r>=count) r=l;
            parent_hash(cur[l],cur[r],next[i]);
        }
        free(cur); cur=next; count=nn;
    }
    memcpy(root,cur[0],HS); free(cur);
    if (leaves) *leaves=lv; else free(lv);
    return 1;
}

void show_tree(const Block *b) {
    if(!b) return;
    size_t count=b->tx_count;
    unsigned char (*cur)[HS]=malloc(count*HS);
    if(!cur) { puts("Memory allocation failed."); return; }
    memcpy(cur,b->leaf_hashes,count*HS);
    size_t level=0;
    printf("\nMerkle tree for block #%zu\n",b->index);
    for(;;) {
        printf("Level %zu (%zu node%s)\n",level,count,count==1?"":"s");
        for(size_t i=0;i<count;i++) { printf("  "); hex(cur[i]); putchar('\n'); }
        if(count==1) break;
        size_t nn=(count+1)/2;
        unsigned char (*next)[HS]=malloc(nn*HS);
        if(!next) { free(cur); puts("Memory allocation failed."); return; }
        for(size_t i=0;i<nn;i++) {
            size_t l=2*i,r=l+1; if(r>=count) r=l;
            parent_hash(cur[l],cur[r],next[i]);
        }
        free(cur); cur=next; count=nn; level++;
    }
    free(cur);
}