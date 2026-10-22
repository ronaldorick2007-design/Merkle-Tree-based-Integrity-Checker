
#ifndef INPUT_H
#define INPUT_H

#include "common.h"

int line(const char *prompt, char *buf, size_t size);

int number(const char *prompt,
           size_t min,
           size_t max,
           size_t *out);

int input_txs(char tx[MAX_TX][TX_SIZE], size_t *n);

#endif
