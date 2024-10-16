#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "railfence.h"

int main() {
    char plaintext[] = "Hello World";
    int plaintext_length = strlen(plaintext);
    int partitions = 3;
    char ciphertext[plaintext_length + 1];
    char expected_ciphertext[] = "HlWleoodl r";

    railfence_encode(plaintext, plaintext_length, partitions, ciphertext);

    assert(!strcmp(ciphertext, expected_ciphertext));

    return 0;
}
