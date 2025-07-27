//
// Created by Alison on 27/07/2025.
//

#ifndef RAILFENCECYPHER_H
#define RAILFENCECYPHER_H

#include <string>

class RailFenceCipher {
private:
    int numRails;

public:
    RailFenceCipher(int rails);  // Construtor

    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);
};

#endif // RAILFENCECIPHER_H

