# 🔐 RSA Public-Key Encryption and Digital Signatures

## 📌 Overview

This project demonstrates how **RSA cryptography** is used for **digital signatures** and **certificate verification**.
The lab focuses on two main cryptographic tasks:

1. **Signing messages using RSA digital signatures**
2. **Manually verifying an X.509 SSL/TLS certificate**

The goal is to understand how modern security systems ensure **data integrity, authentication, and trust** in secure communications. 

---

# 🎯 Learning Objectives

* Understand the **RSA digital signature process**
* Learn how **small message changes affect signatures**
* Extract information from **X.509 certificates**
* Verify a **certificate signature manually**
* Use **OpenSSL and C with BIGNUM** for cryptographic operations

---

# ⚙️ Technologies Used

* **C Programming**
* **OpenSSL Library**
* **RSA Cryptography**
* **X.509 Certificates**
* **SHA-256 Hashing**
* **Linux Terminal / OpenSSL commands**

---

# 🧪 Task 4 — Signing a Message

## Concept

RSA digital signatures allow a sender to prove:

✔ The message came from them (**authentication**)
✔ The message was not modified (**integrity**)
✔ The sender cannot deny sending it (**non-repudiation**)

The signature process uses the RSA formula:

```
Signature: S = M^d mod n
Verification: M = S^e mod n
```

Where:

* **M** = message
* **d** = private key exponent
* **n** = RSA modulus
* **e** = public exponent

---

## Implementation

The program signs two messages:

```
Message 1: I owe you $2000
Message 2: I owe you $3000
```

Both messages are converted to hexadecimal and then signed using the private key.

Example workflow:

```
Plaintext → Hex → BIGNUM → RSA signing
```

The signing operation is performed using:

```
BN_mod_exp(signature, message, d, n, ctx);
```

---

## Key Result

Although the messages differ by **only one character**, their signatures are **completely different**.

This demonstrates an important security property:

> Even a tiny change in a message produces a totally different digital signature. 

---

# 🔏 Task 6 — Verifying an X.509 Certificate

## Objective

Download a real **SSL/TLS certificate** from a web server and manually verify its authenticity using the issuer's public key.

The certificate used in this lab was downloaded from:

```
www.google.com
```

This server provides a valid HTTPS certificate chain. 

---

## X.509 Certificate Structure

A certificate contains several important fields:

* **Subject** → Owner of the certificate
* **Issuer** → Certificate Authority (CA)
* **Public Key** → Server's public key
* **Validity Period** → Certificate lifetime
* **Signature** → CA’s digital signature

---

## Verification Process

The certificate verification follows these steps:

### 1️⃣ Download the Certificate

```
openssl s_client -connect www.google.com:443 -showcerts
```

Save the certificates as:

```
c0.pem  → Server certificate
c1.pem  → Intermediate CA certificate
```

---

### 2️⃣ Extract the Public Key

From the issuer certificate:

```
Modulus (n)
Public Exponent (e)
```

Example exponent:

```
e = 65537
```

---

### 3️⃣ Extract the Signature

The signature from the server certificate is copied and cleaned into:

```
signature.txt
```

Spaces and colons are removed to create a continuous hexadecimal string.

---

### 4️⃣ Extract Certificate Body

The certificate body (without signature) is extracted using:

```
openssl asn1parse
```

This produces:

```
c0_body.bin
```

---

### 5️⃣ Compute the Hash

The certificate body hash is calculated using:

```
sha256sum c0_body.bin
```

---

### 6️⃣ Verify the Signature

The certificate signature is decrypted using the CA's public key:

```
Decrypted = S^e mod n
```

If:

```
Decrypted Hash == Computed Hash
```

then the certificate is **valid and authentic**. 

---

# 📊 Final Result

The decrypted signature hash matched the computed certificate hash.

This confirms that:

✔ The certificate was issued by a trusted CA
✔ The certificate content has not been modified
✔ The server identity is authentic

This verification process is a **core mechanism behind HTTPS security**.

---

# 📂 Project Structure

```
RSA-Signature-and-Certificate-Verification
│
├── task4_sign.c          # RSA message signing program
├── task6_verify.c        # Certificate signature verification
├── c0.pem                # Server certificate
├── c1.pem                # Intermediate CA certificate
├── c0_body.bin           # Extracted certificate body
├── signature.txt         # Extracted certificate signature
└── README.md
```

---

# 🔐 Security Concepts Demonstrated

* Public-Key Cryptography
* RSA Digital Signatures
* Certificate Authority Trust Model
* X.509 Certificate Structure
* SSL/TLS Authentication
* Cryptographic Hash Verification

---

# 👩‍💻 Author

**Saja Asfour**

---

# 📚 References

* OpenSSL Documentation
* RSA Cryptography Standards
* X.509 Certificate Specification
* SEED Security Labs
