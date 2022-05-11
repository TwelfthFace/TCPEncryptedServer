#ifndef CIPHER_H
#define CIPHER_H
#include <fstream>
#include <iostream>
#include <string>
#include <openssl/rsa.h>
#include <openssl/engine.h>
#include <openssl/pem.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>

#define PADDING RSA_PKCS1_PADDING
#define KEYSIZE 32
#define IVSIZE 32
#define BLOCKSIZE 256
#define SALT 8



class Cipher
{
    public:
        Cipher();
        virtual ~Cipher();
    public:
        RSA* get_public_key();
        RSA* get_private_key();
        const char* encryptRSA(RSA* pubkey, const std::string& str);
        std::string decryptRSA(RSA* prikey, const char* str);
    private:
        unsigned char* open_pem(const char* file_path);
};

#endif // CIPHER_H
