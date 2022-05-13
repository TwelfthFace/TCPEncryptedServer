#include "cipher.h"

using namespace std;

RSA* cipher::get_public_key(){
    //open public key file
    const unsigned char* public_key_str = cipher::open_pem("public.pem");
    //create BIO buffer
    BIO* bio = BIO_new_mem_buf((void *)public_key_str, -1);
    //set bio flags to expect BASE64 public key with no nulls;
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    //create RSA populate with BIO read of the former public key.
    RSA* rsa_pub_key = PEM_read_bio_RSA_PUBKEY(bio, NULL, NULL, NULL);
    //error check
    if(!rsa_pub_key){
        std::cout << "Could not load Public Key..." << std::endl << ERR_error_string(ERR_get_error(), NULL);
        BIO_free(bio);
        return nullptr;
    }
    //free bio because we're nice
    BIO_free(bio);
    //return the public key
    return rsa_pub_key;
}

RSA* cipher::get_private_key(){
    //identical to the above func, return private key
    const unsigned char* private_key_str = cipher::open_pem("private.pem");

    BIO* bio = BIO_new_mem_buf((void *)private_key_str, -1);
    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);

    RSA* rsa_pri_key = PEM_read_bio_RSAPrivateKey(bio, NULL, NULL, NULL);

    if(!rsa_pri_key){
        std::cout << "Could not load Private Key..." << std::endl << ERR_error_string(ERR_get_error(), NULL);
        BIO_free(bio);
        return nullptr;
    }

    BIO_free(bio);
    return rsa_pri_key;
}

const char* cipher::encryptRSA(RSA* key, const std::string& str){
    const unsigned char* str_data = (const unsigned char*) str.c_str();

    int rsa_length = RSA_size(key);
    unsigned char* ed = (unsigned char*) calloc(rsa_length, sizeof(u_char));
    int result_len = RSA_public_encrypt(str.size(), (const unsigned char*)str_data, ed, key, PADDING);

    if(result_len == -1){
        std::cout << "Could not encrypt: " << ERR_error_string(ERR_get_error(), NULL) << std::endl;
        return "";
    }

    char* buffer = reinterpret_cast<char*>(ed);

    return buffer;
}

std::string cipher::decryptRSA(RSA* key, const char* str){
    const unsigned char* str_data = (const unsigned char*) str;
    int rsa_length = RSA_size(key);

    unsigned char* ed = (unsigned char*) calloc(rsa_length, sizeof(u_char));
    int result_len = RSA_private_decrypt(rsa_length, str_data, ed, key, PADDING);

    if(result_len == -1){
        std::cout << "Could not decrypt: " << ERR_error_string(ERR_get_error() ,NULL) << std::endl;
        return "";
    }

    std::string buffer(reinterpret_cast<char*>(ed), result_len);

    return buffer;
}

unsigned char* cipher::open_pem(const char* file_path){
    FILE* file = fopen(file_path, "r+");

    if (file == NULL){
        std::cout << "Unable to open: " << file_path << std::endl;
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long int size = ftell(file);

    fclose(file);

    // Reading data to array of unsigned chars
    file = fopen(file_path, "r+");

    unsigned char* in = (unsigned char *) malloc(size);
    fread(in, sizeof(unsigned char), size, file);
    fclose(file);

    return in;
}
