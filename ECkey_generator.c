#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/ec.h>
#include <openssl/obj_mac.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/ecdsa.h>
#include <openssl/rand.h>

#define MESSAGE "Hello, world!"

int main() {
    // Create a new EC key pair
    EC_KEY *ec_key = EC_KEY_new_by_curve_name(NID_secp256k1);
    EC_KEY_generate_key(ec_key);

    // Get the group and order of the curve
    const EC_GROUP *group = EC_KEY_get0_group(ec_key);
    const BIGNUM *order = EC_GROUP_get0_order(group);

    // Generate a random nonce
    BIGNUM *nonce = BN_new();
    BN_rand_range(nonce, order);

    // Hash the message
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char *)MESSAGE, strlen(MESSAGE), hash);

    // Create an ECDSA signature
    ECDSA_SIG *sig = ECDSA_do_sign(hash, SHA256_DIGEST_LENGTH, ec_key);

    // Verify the signature
    int verified = ECDSA_do_verify(hash, SHA256_DIGEST_LENGTH, sig, ec_key);

    // Print the results
    printf("Message: %s\n", MESSAGE);
    printf("Public key: ");
    EC_KEY_print_fp(stdout, ec_key, 0);
    printf("\n");
    printf("Signature: ");
    BN_print_fp(stdout, sig->r);
    printf(", ");
    BN_print_fp(stdout, sig->s);
    printf("\n");
    printf("Verified: %d\n", verified);

    // Clean up
    ECDSA_SIG_free(sig);
    BN_free(nonce);
    EC_KEY_free(ec_key);

    return 0;
}
