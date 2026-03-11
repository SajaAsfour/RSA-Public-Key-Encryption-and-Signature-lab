#include <stdio.h>
#include <string.h>
#include <openssl/bn.h>

void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

BIGNUM* sign_message(char *plaintext, BIGNUM *d, BIGNUM *n, BN_CTX *ctx) {
    BIGNUM *message = BN_new();
    BIGNUM *signature = BN_new();
    
    // Convert string to hex
    char hex_message[512] = "";
    for(int i = 0; i < strlen(plaintext); i++) {
        sprintf(hex_message + strlen(hex_message), "%02X", (unsigned char)plaintext[i]);
    }
    
    BN_hex2bn(&message, hex_message);
    
    printf("Message: %s\n", plaintext);
    printf("Message (hex): %s\n", hex_message);
    printBN("Message (M) =", message);
    
    // Sign: signature = message^d mod n
    BN_mod_exp(signature, message, d, n, ctx);
    printBN("Signature (S) = M^d mod n =", signature);
    
    BN_free(message);
    return signature;
}

int main() {
    BN_CTX *ctx = BN_CTX_new();
    
    BIGNUM *n = BN_new();
    BIGNUM *d = BN_new();
    
    // Private key
    BN_hex2bn(&n, "E103ABD94892E3E74AFD724BF28E78366D9676BCCC70118BD0AA1968DBB143D1");
    BN_hex2bn(&d, "3587A24598E5F2A21DB007D89D18CC50ABA5075BA19A33890FE7C28A9B496AEB");
    
    printf("Private Key:\n");
    printBN("n =", n);
    printBN("d =", d);
    printf("\n");
    
    // Sign first message
    printf("=== Signing Message 1 ===\n");
    char *msg1 = "I owe you $2000";
    BIGNUM *sig1 = sign_message(msg1, d, n, ctx);
    printf("\n");
    
    // Sign modified message
    printf("=== Signing Message 2 (Modified) ===\n");
    char *msg2 = "I owe you $3000";
    BIGNUM *sig2 = sign_message(msg2, d, n, ctx);
    printf("\n");
    
    // Compare signatures
    printf("=== Comparison ===\n");
    printf("Message 1: %s\n", msg1);
    printBN("Signature 1:", sig1);
    printf("\nMessage 2: %s\n", msg2);
    printBN("Signature 2:", sig2);
    
    
    // Cleanup
    BN_free(n);
    BN_free(d);
    BN_free(sig1);
    BN_free(sig2);
    BN_CTX_free(ctx);
    
    return 0;
}
