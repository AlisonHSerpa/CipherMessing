#ifndef VIGENERE_CIPHER_H
#define VIGENERE_CIPHER_H

#include <string>

class VigenereCipher {
public:
    std::string encrypt(const std::string& plaintext, const std::string& key);
    std::string decrypt(const std::string& ciphertext, const std::string& key);
    
private:
    std::string prepareKey(const std::string& key);
    static std::string normalizarTexto(const std::string& input);
};

#endif // VIGENERE_CIPHER_H