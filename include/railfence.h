#ifndef CRYPT_RAILFENCE
#define CRYPT_RAILFENCE

/* This is a transposition cipher which divides the plain text into two
 * partitions by moving through the text in order and appending each symbol to
 * one of the two partitions, alternating between them.
 *
 * In this case, the cipher has been generalized to having 'N partitions',
 * where N is at most the number of symbols in the plain text.
 */


/* plaintext - buffer of text to be provided by user.
 * plaintext_length - length in bytes of the provided string.
 * n_partitions - number of partitions to use for cipher.
 * ciphertext - pointer to buffer to store output of railfence_encode.
 */
void railfence_encode(
    const char *plaintext,
    const int plaintext_length,
    const int n_partitions,
    char *ciphertext
);

#endif
