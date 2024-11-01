#ifndef INCLUDE_SIMPLESUB_H_
#define INCLUDE_SIMPLESUB_H_


/* This cipher involves creating a 1 to 1 mapping from each symbol in the
 * plaintext alphabet to a symbol in the ciphertext alphabet. The 'key' here is
 * just a reordered alphabet, where symbols in the plaintext alphabet are
 * converted to symbols in ciphertext alphabet by finding the symbol in the
 * ciphertext alphabet with the same index as the target in plaintext alphabet.
 *
 * For example:
 * plaintext alphabet -  abcdefghijklmnopqrstuvwxyz
 * ciphertext alphabet - LONGABCDEFHIJKMPQRSTUVWXYZ
 * plaintext - "hello there"
 * ciphertext - "DAIIM TDARA"
 *
 * In our case, each symbol takes up one byte or 'char'.
 * The user only provides the ciphertext alphabet.
 * When encoding, each given char in the plaintext is used as the index for the
 * corresponding ciphertext symbol in the ciphertext alphabet.
 * This means it is up to the user to map their output to the desired encoding.
 *
 * May add arbitrarily sized symbols in future.
 */


/* plaintext - string containing the sequence of symbols to be encrypted.
 * ciphertext - Buffer to receive encrypted text. Should be at least
 * strlen(plaintext) bytes long.
 * n_bytes - Number of bytes to encrypt.
 * key - An array of bytes representing the mapping from plain alphabet to
 * cipher alphabet. Must be of length n_symbols. Not null terminated.
 * It's important that the largest value appearing in plaintext is smaller than
 * n_symbols.
 * n_symbols - The number of unique symbols supported by the key or cipher
 * alphabet. This is also the length of the key.
 */
int simplesub_encode(
        const char *plaintext,
        char *ciphertext,
        const int n_bytes,
        const char *key,
        const int n_symbols);

/* ciphertext - string containing the sequence of symbols to be decrypted.
 * plaintext - Buffer to receive encrypted text. Should be at least
 * strlen(cipehrtext) bytes long.
 * n_bytes - Number of bytes to encrypt.
 * key - An array of bytes representing the mapping from plain alphabet to
 * cipher alphabet. Must be of length n_smbols. Not null terminated. Must be
 * identical to the key used to encrypt the plaintext.
 * n_symbols - The number of unique symbols supported by the key or cipher
 * alphabet. This is also the length of the key.
 */
int simplesub_decode(
        const char *ciphertext,
        char *plaintext,
        const int n_bytes,
        const char *key,
        const int n_symbols);


#endif  // INCLUDE_SIMPLESUB_H_
