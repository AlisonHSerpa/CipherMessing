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
        // Minúsculas
        { 'á', 'A' }, { 'à', 'A' }, { 'â', 'A' }, { 'ã', 'A' }, { 'ä', 'A' }, { 'å', 'A' },
        { 'é', 'E' }, { 'è', 'E' }, { 'ê', 'E' }, { 'ë', 'E' },
        { 'í', 'I' }, { 'ì', 'I' }, { 'î', 'I' }, { 'ï', 'I' },
        { 'ó', 'O' }, { 'ò', 'O' }, { 'ô', 'O' }, { 'õ', 'O' }, { 'ö', 'O' }, { 'ø', 'O' },
        { 'ú', 'U' }, { 'ù', 'U' }, { 'û', 'U' }, { 'ü', 'U' },
        { 'ñ', 'N' }, { 'ç', 'C' }, { 'ý', 'Y' }, { 'ÿ', 'Y' },
        { '?', 'S' }, { '?', 'Z' }, { '?', 'D' }, { 'ß', 'S' },

        // Maiúsculas (já estão corretas, mas incluídas para completude)
        { 'Á', 'A' }, { 'À', 'A' }, { 'Â', 'A' }, { 'Ã', 'A' }, { 'Ä', 'A' }, { 'Å', 'A' },
        { 'É', 'E' }, { 'È', 'E' }, { 'Ê', 'E' }, { 'Ë', 'E' },
        { 'Í', 'I' }, { 'Ì', 'I' }, { 'Î', 'I' }, { 'Ï', 'I' },
        { 'Ó', 'O' }, { 'Ò', 'O' }, { 'Ô', 'O' }, { 'Õ', 'O' }, { 'Ö', 'O' }, { 'Ø', 'O' },
        { 'Ú', 'U' }, { 'Ù', 'U' }, { 'Û', 'U' }, { 'Ü', 'U' },
        { 'Ñ', 'N' }, { 'Ç', 'C' }, { 'Ý', 'Y' },
        { '?', 'S' }, { '?', 'Z' }, { 'Ð', 'D' }
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
        throw invalid_argument("Chave inválida: deve conter pelo menos uma letra");
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
            ciphertext += c; // Mantém caracteres não-alfabéticos
        }
    }

    return ciphertext;
}

string VigenereCipher::decrypt(const string& ciphertext, const string& key) {
    string preparedKey = prepareKey(key);
    if (preparedKey.empty()) {
        throw invalid_argument("Chave inválida: deve conter pelo menos uma letra");
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
            plaintext += c; // Mantém caracteres não-alfabéticos
        }
    }

    return plaintext;
}