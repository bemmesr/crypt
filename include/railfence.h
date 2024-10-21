#ifndef INCLUDE_RAILFENCE_H_
#define INCLUDE_RAILFENCE_H_

/* This is a transposition cipher which divides the plain text into two
 * partitions by moving through the text in order and appending each symbol to
 * one of the two partitions, alternating between them.
 *
 * In this case, the cipher has been generalized to having 'N partitions',
 * where N is at most the number of symbols in the plain text.
 */


/* plaintext - buffer of text to be provided by user.
 * plaintext_length - length in bytes of the provided string. This does NOT
 * include the null terminating character.
 * n_partitions - number of partitions to use for cipher.
 * ciphertext - pointer to buffer to store output of railfence_encode. Must be
 * at least plaintext_length + 1 bytes long.
 */
void railfence_encode(
    const char *plaintext,
    const int text_length,
    const int n_partitions,
    char *ciphertext
);

void railfence_decode(
    const char *ciphertext,
    const int text_length,
    const int n_partitions,
    char *plaintext
);

#endif  // INCLUDE_RAILFENCE_H_
