#include <limits.h>
#include <stdio.h>

#include "include/simplesub.h"


int has_repetitions(const char *buffer, const int n_bytes);


int simplesub_encode(
        const char *plaintext,
        char *ciphertext,
        const int n_bytes,
        const char *key,
        const int n_symbols) {
    if (has_repetitions(key, n_symbols)) {
        fprintf(stderr, "Error: key in simplesub_encode has repetitions.\n");
        return 1;
    }

    for (int i = 0; i < n_bytes; i++) {
        ciphertext[i] = key[(int)plaintext[i]];
    }

    return 0;
}

int simplesub_decode(
        const char *ciphertext,
        char *plaintext,
        const int n_bytes,
        const char *key,
        const int n_symbols) {
    if (has_repetitions(key, n_symbols)) {
        fprintf(stderr, "Error: key in simplesub_decode has repetitions.\n");
        return 1;
    }

    // TODO(bemmesr): Design an O(n) algorithm to decode using the same key.

    return 0;
}


int has_repetitions(const char *buffer, const int n_bytes) {
    int seen_before[UCHAR_MAX];
    for (int i = 0; i < UCHAR_MAX; i++) {
        seen_before[i] = 0;
    }

    for (int i = 0; i < n_bytes; i++) {
        if (seen_before[(int)buffer[i]]) {
            return 1;
        }
        seen_before[(int)buffer[i]] = 1;
    }
    return 0;
}

