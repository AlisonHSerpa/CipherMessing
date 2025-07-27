//
// Created by Alison on 27/07/2025.
//

#ifndef TPCCIPHER_H
#define TPCCIPHER_H


#include <string>

class ColumnarTranspositionCipher {
public:
    ColumnarTranspositionCipher(const std::string& key);

    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);

private:
    std::string key;
    std::string createSortedKeyIndices() const;
};

#endif // COLUMNARTRANSPOSITIONCIPHER_H
