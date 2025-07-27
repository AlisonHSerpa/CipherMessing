//
// Created by Alison on 27/07/2025.
//

#include "../../include/DoubleTranspositionCipher.h"

#include <vector>
#include <algorithm>
#include <cmath>

DoubleTranspositionCipher::DoubleTranspositionCipher(const std::string& key1, const std::string& key2)
    : key1(key1), key2(key2) {}

std::string DoubleTranspositionCipher::applyTransposition(const std::string& text, const std::string& key, bool encrypting) {
    int cols = key.size();
    int rows = std::ceil((double)text.length() / cols);

    // Preenche a matriz com 'X' como padding
    std::vector<std::vector<char>> matrix(rows, std::vector<char>(cols, 'X'));
    int idx = 0;
    for (int r = 0; r < rows && idx < (int)text.length(); ++r) {
        for (int c = 0; c < cols && idx < (int)text.length(); ++c) {
            matrix[r][c] = text[idx++];
        }
    }

    // Obter a ordem das colunas com base na chave ordenada
    std::string sortedKey = key;
    std::sort(sortedKey.begin(), sortedKey.end());

    std::vector<int> colOrder(cols);
    std::string keyCopy = key;
    for (int i = 0; i < cols; ++i) {
        int pos = keyCopy.find(sortedKey[i]);
        colOrder[i] = pos;
        keyCopy[pos] = '*';  // Evita duplicatas
    }

    std::string result;
    if (encrypting) {
        for (int i = 0; i < cols; ++i) {
            int col = colOrder[i];
            for (int r = 0; r < rows; ++r) {
                result += matrix[r][col];
            }
        }
    } else {
        // Desencriptar: construir matriz em ordem de colunas e depois ler linha por linha
        std::vector<std::vector<char>> decryptedMatrix(rows, std::vector<char>(cols, ' '));
        int charIndex = 0;

        for (int i = 0; i < cols; ++i) {
            int col = colOrder[i];
            for (int r = 0; r < rows && charIndex < (int)text.length(); ++r) {
                decryptedMatrix[r][col] = text[charIndex++];
            }
        }

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                result += decryptedMatrix[r][c];
            }
        }
    }

    return result;
}

std::string DoubleTranspositionCipher::encrypt(const std::string& plaintext) {
    std::string first = applyTransposition(plaintext, key1, true);
    return applyTransposition(first, key2, true);
}

std::string DoubleTranspositionCipher::decrypt(const std::string& ciphertext) {
    std::string first = applyTransposition(ciphertext, key2, false);
    return applyTransposition(first, key1, false);
}