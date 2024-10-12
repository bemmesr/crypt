#include "railfence.h"

#include <stdlib.h>
#include <string.h>

char *railfence_encode(const char *plaintext, const int n_partitions) {
    int plaintext_length = strlen(plaintext);

    // Allocate a buffer for the resulting ciphertext.
    char *ciphertext = malloc(sizeof(char) * (plaintext_length + 1));
    ciphertext[plaintext_length] = '\0';

    // Iterate through the plain text and assign each symbol to its partition.
    // TODO: Check that there is no index out-of-bound error here.
    int max_partition_size = plaintext_length / n_partitions;
    for (int i = 0; i < n_partitions; i++) {
        int current_partition = i % n_partitions;
        int partition_offset = max_partition_size * current_partition;
        int current_offset = i / n_partitions;
        int ciphertext_index = partition_offset + current_offset;
        ciphertext[ciphertext_index] = plaintext[i];
    }

    return ciphertext;
}
