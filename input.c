#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"


static int line(const char *prompt,char *buf,size_t size) {
    printf("%s",prompt);
    if (!fgets(buf,(int)size,stdin)) return 0;
    size_t n=strlen(buf);
    if (n && buf[n-1]=='\n') buf[n-1]='\0';
    else { int ch; while ((ch=getchar())!='\n' && ch!=EOF) {} }
    return 1;
}

static int number(const char *prompt,size_t min,size_t max,size_t *out) {
    char s[80]; if (!line(prompt,s,sizeof s)) return 0;
    char *end=NULL; unsigned long v=strtoul(s,&end,10);
    if (!s[0] || end==s || *end || v<min || v>max) {
        printf("Enter a whole number from %zu to %zu.\n",min,max); return 0;
    }
    *out=(size_t)v; return 1;
}

static int input_txs(char tx[MAX_TX][TX_SIZE],size_t *n) {
    if (!number("Number of transactions in this block: ",1,MAX_TX,n)) return 0;
    for (size_t i=0;i<*n;i++) {
        char prompt[64]; snprintf(prompt,sizeof prompt,"Transaction %zu: ",i+1);
        if (!line(prompt,tx[i],TX_SIZE) || !tx[i][0]) {
            puts("Transaction cannot be empty."); return 0;
        }
    }
    return 1;
}