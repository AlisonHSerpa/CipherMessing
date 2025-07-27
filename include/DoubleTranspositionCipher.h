//
// Created by Alison on 27/07/2025.
//

#ifndef DOUBLETRANSPOSITIONCIPHER_H
#define DOUBLETRANSPOSITIONCIPHER_H

#include <string>

class DoubleTranspositionCipher {
public:
    DoubleTranspositionCipher(const std::string& key1, const std::string& key2);

    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);

private:
    std::string key1;
    std::string key2;

    std::string applyTransposition(const std::string& text, const std::string& key, bool encrypting);
};

#endif // DOUBLETRANSPOSITIONCIPHER_H

