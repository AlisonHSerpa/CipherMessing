//
// Created by Alison on 27/07/2025.
//

#include "../../include/TPCCipher.h"

#include <vector>
#include <algorithm>
#include <cmath>

ColumnarTranspositionCipher::ColumnarTranspositionCipher(const std::string& key) : key(key) {}

std::string ColumnarTranspositionCipher::createSortedKeyIndices() const {
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());
    return sortedKey;
}

std::string ColumnarTranspositionCipher::encrypt(const std::string& plaintext) {
    int cols = key.length();
    int rows = std::ceil((double)plaintext.length() / cols);

    std::vector<std::string> matrix(rows, std::string(cols, 'X'));
    int idx = 0;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (idx < plaintext.length()) matrix[r][c] = plaintext[idx++];
        }
    }

    std::string sortedKey = createSortedKeyIndices();
    std::string ciphertext;
    std::string tempKey = key;  // Temporary copy to avoid modifying 'key'

    for (char sk : sortedKey) {
        int col = tempKey.find(sk);
        for (int r = 0; r < rows; ++r) {
            ciphertext += matrix[r][col];
        }
        tempKey[col] = '*';  // Mark used (doesn't affect original key)
    }

    return ciphertext;
}

std::string ColumnarTranspositionCipher::decrypt(const std::string& ciphertext) {
    int cols = key.length();
    int rows = ciphertext.length() / cols;  // No padding needed if divisible

    std::vector<std::string> matrix(rows, std::string(cols, ' '));
    std::string sortedKey = createSortedKeyIndices();  // Must return "ABERSZ" for "ZEBRAS"

    // Split ciphertext into column chunks (each of size 'rows')
    for (int i = 0; i < sortedKey.length(); ++i) {
        char sk = sortedKey[i];
        int col = key.find(sk);  // Original column position

        // Fill this column with the next 'rows' characters
        for (int r = 0; r < rows; ++r) {
            matrix[r][col] = ciphertext[i * rows + r];
        }
    }

    // Read row-wise to reconstruct plaintext
    std::string plaintext;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            plaintext += matrix[r][c];
        }
    }

    return plaintext;  // No padding removal needed (exact fit)
}
