#include "cipher.h"
#include "base64.h"

using namespace std;

int main(int argc, char* argv[])
{
    Cipher test;

    RSA* rsapub = test.get_public_key();
    RSA* rsapri = test.get_private_key();

    const char* enc = test.encryptRSA(rsapub, std::string("kekwkekw"));
    std::string encoded = base64_encode(reinterpret_cast<const unsigned char*>(enc), 256);

    std::cout << "ENCRYPTED: " << encoded << std::endl;
    std::cout << "DECRYPTED: " << test.decryptRSA(rsapri, enc) << std::endl;

    return 0;
}
////
//
