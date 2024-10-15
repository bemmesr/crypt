#include "railfence.h"

void railfence_encode(
    const char *plaintext,
    const int plaintext_length,
    const int n_partitions,
    char *ciphertext
) {
    ciphertext[plaintext_length] = '\0';

    for (int i = 0; i < plaintext_length; i++) {
        ciphertext[i] = plaintext[(i * n_partitions) % plaintext_length];
    }
}
