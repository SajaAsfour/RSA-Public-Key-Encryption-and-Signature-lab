#include <stdio.h>
#include <openssl/bn.h>
#include <string.h>

void printBN(char *msg, BIGNUM *a) {
    char *number_str = BN_bn2hex(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    BN_CTX *ctx = BN_CTX_new();
    
    // Initialize BIGNUMs
    BIGNUM *n = BN_new();      // Modulus from issuer's certificate
    BIGNUM *e = BN_new();      // Public exponent from issuer's certificate
    BIGNUM *S = BN_new();      // Signature from server's certificate
    BIGNUM *decrypted = BN_new();  // Result of signature decryption
    

    // Step 1: Set the modulus (n) from c1.pem
    BN_hex2bn(&n, "A9FF9C7F451E70A8539FCAD9E50DDE4657577DBC8F9A5AAC46F1849ABB91DBC9FB2F01FB920900165EA01CF8C1ABF9782F4ACCD885A2D8593C0ED318FBB1F5240D26EEB65B64767C14C72F7ACEA84CB7F4D908FCDF87233520A8E269E28C4E3FB159FA60A21EB3C920531982CA36536D604DE90091FC768D5C080F0AC2DCF1736BC5136E0A4F7AC2F2021C2EB46383DA31F62D7530B2FBABC26EDBA9C00EB9F967D4C3255774EB05B4E98EB5DE28CDCC7A14E47103CB4D612E6157C519A90B98841AE87929D9B28D2FFF576A66E0CEAB95A82996637012671E3AE1DBB02171D77C9EFDAA176EFE2BFB381714D166A7AF9AB570CCC863813A8CC02AA97637CEE3");
    
    // Step 2: Set the public exponent (e) from c1.pem
    BN_hex2bn(&e, "010001");
    
    // Step 3: Set the signature (S) from c0.pem
    BN_hex2bn(&S, "01af1466049d4c54e334c8f1150be86aeafcb1939a993b99ee02d9f944229817ce7d7d5bd6f72a369f39ec702641c8f6c969232e398a2f717e806f7fb198b9de58bb8a1f8dad872abd311f4d4f956dd6a5f225cd2ca6c826f4c958ae0a745fb1446242d8d08c3cdb26cdb837419d5e17acf652f7622f6b46bd3b29c32c325b308cc5cbd53c7fcb46ab7dc8e0450b123e418c60c07d88c0e0a1081b1bfd5021dfbb9084bdfa34d54278f140b95ec635ca4820594074abb0a58f2b3a3f4301baa59a0101d17fa73e9bea8cfc6a9b3fd8c2c2a45184cf83a0369ef5aaa0a00f843632ca09b9d1fcf69b8cbfde9d3504bbed914e24f7d4cfc2fb4b49a64999ce2d3b"); 
    // Step 4: Decrypt the Message using the CA's public key
    // Formula: decrypted = S^e mod n
    BN_mod_exp(decrypted, S, e, n, ctx);
    
    // Step 5: Display the decrypted Message
    printf("\n=== Decrypted Message ===\n");
    printBN("Decrypted value:", decrypted);
    
    
    // Cleanup
    BN_free(n);
    BN_free(e);
    BN_free(S);
    BN_free(decrypted);
    BN_CTX_free(ctx);
    
    return 0;
}
