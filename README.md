# ECDSA_Algo
This code generates a new EC key pair using the secp256k1 curve, which is used by Bitcoin. It then generates a random nonce and hashes the message "Hello, world!" using the SHA256 algorithm. 
It creates an ECDSA signature using the private key of the key pair and the hash of the message, and then verifies the signature using the public key of the key pair and the same hash. Finally, it prints out the message, the public key, the signature, and whether the verification succeeded.

Note that this is just a simple example and is not suitable for production use.
