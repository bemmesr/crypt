#include "railfence.h"

void railfence_encode(
    const char *plaintext,
    const int text_length,
    const int n_partitions,
    char *ciphertext
) {
    ciphertext[text_length] = '\0';
    int write = 0;
    for (int i = 0; i < n_partitions; i++) {
        for (int j = i; j < text_length; j += n_partitions) {
            ciphertext[write++] = plaintext[j];
        }
    }
}

void railfence_decode(
    const char *ciphertext,
    const int text_length,
    const int n_partitions,
    char *plaintext
) {
    plaintext[text_length] = '\0';
    int read = 0;
    for (int i = 0; i < n_partitions; i++) {
        for (int j = i; j < text_length; j += n_partitions) {
            plaintext[j] = ciphertext[read++];
        }
    }
}
