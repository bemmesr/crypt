#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "railfence.h"

int TEST_NUMBER = 0;

void test_railfence_encode_decode(
    const char *plaintext,
    const char *ciphertext,
    const int n_partitions
);

int main() {
    test_railfence_encode_decode("Hello World", "HlWleoodl r", 3);
    test_railfence_encode_decode("Hello World", "HloWrdel ol", 2);
    test_railfence_encode_decode("Hello World", "Hello World", 11);
    test_railfence_encode_decode("Hello World", "Hello World", 1);
    test_railfence_encode_decode(
        "abcdefghijklmnopqrstuvwxyz",
        "afkpuzbglqvchmrwdinsxejoty",
        5
    );

    return 0;
}

void test_railfence_encode_decode(
    const char *plaintext,
    const char *ciphertext,
    const int n_partitions
) {
    TEST_NUMBER++;
    const int text_length = strlen(plaintext);
    char result_buffer[text_length + 1];

    railfence_encode(plaintext, text_length, n_partitions, result_buffer);

    if (strcmp(result_buffer, ciphertext)) {
        printf(
            "%d: railfence_encode failed: expected '%s' but got '%s'\n",
            TEST_NUMBER,
            ciphertext,
            result_buffer
        );
    } else {
        printf("%d: railfence_encode passed.\n", TEST_NUMBER);
    }

    railfence_decode(ciphertext, text_length, n_partitions, result_buffer);

    if (strcmp(result_buffer, plaintext)) {
        printf(
            "%d: railfence_decode failed: expected '%s' but got '%s'\n",
            TEST_NUMBER,
            plaintext,
            result_buffer
        );
    } else{
        printf("%d: railfence_decode passed.\n", TEST_NUMBER);
    }
}

