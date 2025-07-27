//
// Created by Alison on 27/07/2025.
//

#include "../../include/RailFenceCipher.h"

#include <vector>

RailFenceCipher::RailFenceCipher(int rails) : numRails(rails) {}

std::string RailFenceCipher::encrypt(const std::string& plaintext) {
    if (numRails <= 1 || plaintext.empty()) return plaintext;

    std::vector<std::string> railStrings(numRails);
    int rail = 0;
    int dir = 1; // 1 = descendo, -1 = subindo

    for (char c : plaintext) {
        railStrings[rail] += c;
        rail += dir;

        if (rail == 0 || rail == numRails - 1)
            dir *= -1;
    }

    std::string result;
    for (const auto& row : railStrings) {
        result += row;
    }

    return result;
}

std::string RailFenceCipher::decrypt(const std::string& ciphertext) {
    if (numRails <= 1 || ciphertext.empty()) return ciphertext;

    std::vector<std::vector<bool>> pattern(numRails, std::vector<bool>(ciphertext.length(), false));

    // Marcar onde os caracteres irão
    int rail = 0;
    int dir = 1;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        pattern[rail][i] = true;
        rail += dir;

        if (rail == 0 || rail == numRails - 1)
            dir *= -1;
    }

    // Preencher com os caracteres do ciphertext
    std::vector<std::vector<char>> rails(numRails, std::vector<char>(ciphertext.length()));
    size_t idx = 0;
    for (int r = 0; r < numRails; ++r) {
        for (size_t c = 0; c < ciphertext.length(); ++c) {
            if (pattern[r][c] && idx < ciphertext.length()) {
                rails[r][c] = ciphertext[idx++];
            }
        }
    }

    // Ler o texto na ordem original
    std::string result;
    rail = 0;
    dir = 1;
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        result += rails[rail][i];
        rail += dir;

        if (rail == 0 || rail == numRails - 1)
            dir *= -1;
    }

    return result;
}
