//
// Created by Alison on 11/06/2025.
//

#include "../../include/VigenereCipher.h"
#include <stdexcept>
#include <cctype>
#include <unordered_map>

using namespace std;

string VigenereCipher::prepareKey(const string& key) {
    string prepared;
    for (char c : key) {
        char upperC = toupper(c);
        if (upperC >= 'A' && upperC <= 'Z') {
            prepared += upperC;
        }
    }
    return prepared;
}

std::string VigenereCipher::normalizarTexto(const std::string &input) {
    static const std::unordered_map<char, char> mapa = {
        // Min�sculas
        { '�', 'A' }, { '�', 'A' }, { '�', 'A' }, { '�', 'A' }, { '�', 'A' }, { '�', 'A' },
        { '�', 'E' }, { '�', 'E' }, { '�', 'E' }, { '�', 'E' },
        { '�', 'I' }, { '�', 'I' }, { '�', 'I' }, { '�', 'I' },
        { '�', 'O' }, { '�', 'O' }, { '�', 'O' }, { '�', 'O' }, { '�', 'O' }, { '�', 'O' },
        { '�', 'U' }, { '�', 'U' }, { '�', 'U' }, { '�', 'U' },
        { '�', 'N' }, { '�', 'C' }, { '�', 'Y' }, { '�', 'Y' },
        { '?', 'S' }, { '?', 'Z' }, { '?', 'D' }, { '�', 'S' },

        // Mai�sculas (j� est�o corretas, mas inclu�das para completude)
        { '�', 'A' }, { '�', 'A' }, { '�', 'A' }, { '�', 'A' }, { '�', 'A' }, { '�', 'A' },
        { '�', 'E' }, { '�', 'E' }, { '�', 'E' }, { '�', 'E' },
        { '�', 'I' }, { '�', 'I' }, { '�', 'I' }, { '�', 'I' },
        { '�', 'O' }, { '�', 'O' }, { '�', 'O' }, { '�', 'O' }, { '�', 'O' }, { '�', 'O' },
        { '�', 'U' }, { '�', 'U' }, { '�', 'U' }, { '�', 'U' },
        { '�', 'N' }, { '�', 'C' }, { '�', 'Y' },
        { '?', 'S' }, { '?', 'Z' }, { '�', 'D' }
    };

    std::string output;
    for (char c : input) {
        auto it = mapa.find(c);
        if (it != mapa.end()) {
            output += it->second;
        } else if (static_cast<unsigned char>(c) < 128) {
            output += toupper(c);
        }
    }
    return output;
}

string VigenereCipher::encrypt(const string& plaintext, const string& key) {
    string preparedKey = prepareKey(key);
    if (preparedKey.empty()) {
        throw invalid_argument("Chave inv�lida: deve conter pelo menos uma letra");
    }

    string normalizedText = normalizarTexto(plaintext);
    string ciphertext;
    ciphertext.reserve(normalizedText.size());

    size_t keyIndex = 0;
    for (char c : normalizedText) {
        if (c >= 'A' && c <= 'Z') {
            char encrypted = 'A' + (c - 'A' + preparedKey[keyIndex] - 'A') % 26;
            ciphertext += encrypted;
            keyIndex = (keyIndex + 1) % preparedKey.size();
        } else {
            ciphertext += c; // Mant�m caracteres n�o-alfab�ticos
        }
    }

    return ciphertext;
}

string VigenereCipher::decrypt(const string& ciphertext, const string& key) {
    string preparedKey = prepareKey(key);
    if (preparedKey.empty()) {
        throw invalid_argument("Chave inv�lida: deve conter pelo menos uma letra");
    }

    string normalizedText = normalizarTexto(ciphertext);
    string plaintext;
    plaintext.reserve(normalizedText.size());

    size_t keyIndex = 0;
    for (char c : normalizedText) {
        if (c >= 'A' && c <= 'Z') {
            char decrypted = 'A' + (c - 'A' - (preparedKey[keyIndex] - 'A') + 26) % 26;
            plaintext += decrypted;
            keyIndex = (keyIndex + 1) % preparedKey.size();
        } else {
            plaintext += c; // Mant�m caracteres n�o-alfab�ticos
        }
    }

    return plaintext;
}