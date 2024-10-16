#include "railfence.h"

void railfence_encode(
    const char *plaintext,
    const int plaintext_length,
    const int n_partitions,
    char *ciphertext
) {
    ciphertext[plaintext_length] = '\0';

    int p_index = 0;
    int next_start = 0;
    for (int i = 0; i < plaintext_length; i++) {
        ciphertext[i] = plaintext[p_index];
        p_index += n_partitions;
        if (p_index >= plaintext_length) {
            next_start++;
            p_index = next_start;
        }
    }
}
