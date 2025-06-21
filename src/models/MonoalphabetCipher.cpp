//
// Created by Alison on 21/05/2025.
//
#include <iostream>
#include "../../include/MonoalphabetCipher.h"
#include <algorithm>
#include <random>
#include <chrono>
#include <unordered_map>
#include <cctype>

std::string MonoalphabetCipher::normalizarTexto(const std::string &input) {
    static const std::unordered_map<char, char> mapa = {
        // Minúsculas
        { 'á', 'A' }, { 'à', 'A' }, { 'â', 'A' }, { 'ã', 'A' }, { 'ä', 'A' }, { 'å', 'A' },
        { 'é', 'E' }, { 'è', 'E' }, { 'ê', 'E' }, { 'ë', 'E' },
        { 'í', 'I' }, { 'ì', 'I' }, { 'î', 'I' }, { 'ï', 'I' },
        { 'ó', 'O' }, { 'ò', 'O' }, { 'ô', 'O' }, { 'õ', 'O' }, { 'ö', 'O' }, { 'ø', 'O' },
        { 'ú', 'U' }, { 'ù', 'U' }, { 'û', 'U' }, { 'ü', 'U' },
        { 'ñ', 'N' }, { 'ç', 'C' }, { 'ý', 'Y' }, { 'ÿ', 'Y' },
        { 'š', 'S' }, { 'ž', 'Z' }, { 'đ', 'D' }, { 'ß', 'S' },

        // Maiúsculas (mantidas como maiúsculas)
        { 'Á', 'A' }, { 'À', 'A' }, { 'Â', 'A' }, { 'Ã', 'A' }, { 'Ä', 'A' }, { 'Å', 'A' },
        { 'É', 'E' }, { 'È', 'E' }, { 'Ê', 'E' }, { 'Ë', 'E' },
        { 'Í', 'I' }, { 'Ì', 'I' }, { 'Î', 'I' }, { 'Ï', 'I' },
        { 'Ó', 'O' }, { 'Ò', 'O' }, { 'Ô', 'O' }, { 'Õ', 'O' }, { 'Ö', 'O' }, { 'Ø', 'O' },
        { 'Ú', 'U' }, { 'Ù', 'U' }, { 'Û', 'U' }, { 'Ü', 'U' },
        { 'Ñ', 'N' }, { 'Ç', 'C' }, { 'Ý', 'Y' },
        { 'Š', 'S' }, { 'Ž', 'Z' }, { 'Ð', 'D' }
    };

    std::string output;
    for (char c : input) {
        auto it = mapa.find(c);
        if (it != mapa.end()) {
            output += it->second;
        } else if (static_cast<unsigned char>(c) < 128) {
            // Converte para maiúscula
            output += static_cast<char>(toupper(c));
        }
    }
    return output;
}

void MonoalphabetCipher::createKey(std::array<int, 26> &keyArray) {
    // Preenche com valores de 0 a 25
    for (int i = 0; i < 26; ++i) {
        keyArray[i] = i;
    }

    // Embaralha o array
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(keyArray.begin(), keyArray.end(), std::default_random_engine(seed));
}

std::string MonoalphabetCipher::encrypt(const std::string &plainText, const std::array<int, 26> &key) {
    std::string normalizedText = normalizarTexto(plainText);

    std::string cipherText;

    for (char c : normalizedText) {
        if (isalpha(c)) {
            int originalPos = toupper(c) - 'A';
            int encryptedPos = key[originalPos];
            char encryptedChar = 'A' + encryptedPos;
            cipherText += encryptedChar;
        }
    }

    return cipherText;
}

std::string MonoalphabetCipher::decrypt(const std::string &cipherText, const std::array<int, 26> &key) {
    std::string plainText;

    for (char c : cipherText) {
        if (isalpha(c)) {
            int encryptedPos = toupper(c) - 'A';  // Posição do caractere cifrado (0-25)

            // Procura em qual posição da chave está este valor
            for (int originalPos = 0; originalPos < 26; originalPos++) {
                if (key[originalPos] == encryptedPos) {
                    plainText += 'A' + originalPos;
                    break;
                }
            }
        }
    }

    return plainText;
}