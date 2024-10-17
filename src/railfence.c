#include "railfence.h"

void railfence_encode(
    const char *plaintext,
    const int text_length,
    const int n_partitions,
    char *ciphertext
) {
    ciphertext[text_length] = '\0';

    int p_index = 0;
    int next_start = 0;
    for (int i = 0; i < text_length; i++) {
        ciphertext[i] = plaintext[p_index];
        p_index += n_partitions;
        if (p_index >= text_length) {
            next_start++;
            p_index = next_start;
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

    int c_index = 0;
    int next_start = 0;
    const int leap_step_size = text_length / n_partitions;
    const int n_leap_steps = text_length % n_partitions;
    for (int i = 0; i < text_length; i++) {
        plaintext[i] = ciphertext[c_index];
        if (c_index - next_start < leap_step_size * n_leap_steps) {
            c_index += leap_step_size + 1;
        } else {
            c_index += leap_step_size;
        }
        if (c_index >= text_length) {
            next_start++;
            c_index = next_start;
        }
    }
}
