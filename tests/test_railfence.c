#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "railfence.h"

int main() {
    char plaintext[] = "Test string.";
    int plaintext_length = strlen(plaintext);
    int partitions = 3;
    char ciphertext[plaintext_length + 1];
    ciphertext[plaintext_length] = '\0';
    char expected_ciphertext[] = "Tttne rgssi.";

    railfence_encode(plaintext, plaintext_length, partitions, ciphertext);

    assert(!strcmp(ciphertext, expected_ciphertext));

    return 0;
}
