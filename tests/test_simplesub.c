#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "include/simplesub.h"


int TEST_NUMBER = 0;
int TEST_STATUS = 0;


struct test_buffers {
    char *result;
    char *plaintext_reduced;
    char *ciphertext_reduced;
    char *key_reduced;
    char *result_expanded;
};


void test_simplesub_encode_decode(
    const char *plaintext,
    const char *ciphertext,
    const char *key,
    const int n_symbols
);

void test_simplesub_encode_decode_key_repeats();

// Converts ascii values to a simpler alpha and space only system.
int prepare_test_buffers(
        struct test_buffers *buffer,
        const int n_bytes,
        const int n_symbols,
        const char *plaintext,
        const char *ciphertext,
        const char *key);
char *prepare_buffer(
        size_t n_bytes,
        const int reduce,
        const char *from,
        int *failed_reduce);
void free_test_buffers(struct test_buffers *buffer);
int reduce_to_alpha(const char *ascii, char *alpha, const int n_bytes);
int expand_to_ascii(const char *alpha, char *ascii, const int n_bytes);
void invalid_input_char(const char *func_name, const char bad_char);
void non_reducable(const char *bad_string);


int main() {
    test_simplesub_encode_decode(
            "hello world",
            "dyhhknukpha",
            "no waybcdefghijklmpqrstuvxz",
            27);

    test_simplesub_encode_decode_key_repeats();

    return TEST_STATUS;
}


void test_simplesub_encode_decode(
    const char *plaintext,
    const char *ciphertext,
    const char *key,
    const int n_symbols
) {
    TEST_NUMBER++;
    struct test_buffers buffer;
    const int text_length = strlen(plaintext);

    const int failed_reduce = prepare_test_buffers(
            &buffer,
            text_length,
            n_symbols,
            plaintext,
            ciphertext,
            key);

    if (failed_reduce) {
        free_test_buffers(&buffer);
        return;
    }

    (void)simplesub_encode(
            buffer.plaintext_reduced,
            buffer.result,
            text_length,
            buffer.key_reduced,
            n_symbols);

    expand_to_ascii(buffer.result, buffer.result_expanded, text_length);

    if (strcmp(buffer.result, buffer.ciphertext_reduced)) {
        printf(
            "%d: simplesub_encode failed: expected '%s' but got '%s'\n",
            TEST_NUMBER,
            ciphertext,
            buffer.result_expanded);
        TEST_STATUS = 1;
    } else {
        printf("%d: simplesub_encode passed.\n", TEST_NUMBER);
    }

    (void)simplesub_decode(
            ciphertext,
            buffer.result,
            text_length,
            key,
            n_symbols);

    expand_to_ascii(buffer.result, buffer.result_expanded, text_length);

    if (strcmp(buffer.result, plaintext)) {
        printf(
            "%d: simplesub_decode failed: expected '%s' but got '%s'\n",
            TEST_NUMBER,
            plaintext,
            buffer.result);
        TEST_STATUS = 1;
    } else {
        printf("%d: simplesub_decode passed.\n", TEST_NUMBER);
    }
}

void test_simplesub_encode_decode_key_repeats() {
    TEST_NUMBER++;
    char result_buffer[5];
    if (simplesub_encode("abcde", result_buffer, 5, "aabcd", 5)) {
        printf(
            "%d: simplesub_encode err on repetitive key passed.\n",
            TEST_NUMBER);
    } else {
        printf(
            "%d: simplesub_encode err on repetitive key failed.\n",
            TEST_NUMBER);
        TEST_STATUS = 1;
    }

    if (simplesub_decode("abcde", result_buffer, 5, "aabcd", 5)) {
        printf(
            "%d: simplesub_decode err on repetitive key passed.\n",
            TEST_NUMBER);
    } else {
        printf(
            "%d: simplesub_decode err on repetitive key failed.\n",
            TEST_NUMBER);
        TEST_STATUS = 1;
    }
}

int prepare_test_buffers(
        struct test_buffers *buffer,
        const int n_bytes,
        const int n_symbols,
        const char *plaintext,
        const char *ciphertext,
        const char *key) {
    int failed_reduce = 0;
    buffer->result = prepare_buffer(n_bytes, 0, NULL, NULL);
    buffer->plaintext_reduced = prepare_buffer(
            n_bytes,
            1,
            plaintext,
            &failed_reduce);
    buffer->ciphertext_reduced = prepare_buffer(
            n_bytes,
            1,
            ciphertext,
            &failed_reduce);
    buffer->key_reduced = prepare_buffer(n_symbols, 1, key, &failed_reduce);
    buffer->result_expanded = prepare_buffer(n_bytes, 0, NULL, NULL);
    return failed_reduce;
}

char *prepare_buffer(
        size_t n_bytes,
        const int reduce,
        const char *from,
        int *failed_reduce) {
    char *buffer = (char *)malloc(n_bytes + 1);
    buffer[n_bytes] = '\0';

    if (reduce && reduce_to_alpha(from, buffer, n_bytes)) {
        *failed_reduce = 1;
    }

    return buffer;
}

void free_test_buffers(struct test_buffers *buffer) {
    free(buffer->result);
    free(buffer->plaintext_reduced);
    free(buffer->ciphertext_reduced);
    free(buffer->key_reduced);
    free(buffer->result_expanded);
}

int reduce_to_alpha(const char *ascii, char *alpha, const int n_bytes) {
    for (int i = 0; i < n_bytes; i++) {
        if (ascii[i] == ' ') {
            alpha[i] = (char)0;
            continue;
        }

        if (ascii[i] >= 'A' && ascii[i] <= 'Z') {
            alpha[i] = (char)(1 + ascii[i] - 'A');
            continue;
        }

        if (ascii[i] >= 'a' && ascii[i] <= 'z') {
            alpha[i] = (char)(1 + ascii[i] - 'a');
            continue;
        }

        invalid_input_char("reduce_to_alpha", ascii[i]);
        return 1;
    }
    return 0;
}

int expand_to_ascii(const char *alpha, char *ascii, const int n_bytes) {
    for (int i = 0; i < n_bytes; i++) {
        if (alpha[i] == (char)0) {
            ascii[i] = ' ';
            continue;
        }

        if (alpha[i] >= (char)1 && alpha[i] <= (char)26) {
            ascii[i] = 'a' + alpha[i] - (char)1;
            continue;
        }

        invalid_input_char("expand_to_ascii", alpha[i]);
        return 1;
    }
    return 0;
}

void invalid_input_char(const char *func_name, const char bad_char) {
    fprintf(stderr,
            "Error: '%s' received invalid input char '%c'.\n",
            func_name,
            bad_char);
}

void non_reducable(const char *bad_string) {
    fprintf(stderr,
            "%d: Unable to execute test because '%s' was non-reducable",
            TEST_NUMBER,
            bad_string);
}

