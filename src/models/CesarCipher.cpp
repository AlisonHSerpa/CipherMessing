#include "../../include/CesarCipher.h"
#include <string>
#include <algorithm>
#include <unordered_map>
#include <locale>
#include <cctype>

using namespace std;

// Função para normalizar o texto (utilizando um mapa de caracteres) e converter para maiúsculas
std::string normalizarTexto(const std::string &input) {
    static const std::unordered_map<char, char> mapa = {
        // Minúsculas
        { 'á', 'A' }, { 'à', 'A' }, { 'â', 'A' }, { 'ã', 'A' }, { 'ä', 'A' }, { 'å', 'A' },
        { 'é', 'E' }, { 'è', 'E' }, { 'ê', 'E' }, { 'ë', 'E' },
        { 'í', 'I' }, { 'ì', 'I' }, { 'î', 'I' }, { 'ï', 'I' },
        { 'ó', 'O' }, { 'ò', 'O' }, { 'ô', 'O' }, { 'õ', 'O' }, { 'ö', 'O' }, { 'ø', 'O' },
        { 'ú', 'U' }, { 'ù', 'U' }, { 'û', 'U' }, { 'ü', 'U' },
        { 'ñ', 'N' }, { 'ç', 'C' }, { 'ý', 'Y' }, { 'ÿ', 'Y' },
        { 'š', 'S' }, { 'ž', 'Z' }, { 'đ', 'D' }, { 'ß', 'S' },

        // Maiúsculas (já estão corretas, mas incluídas para completude)
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
            output += toupper(c);
        }
    }
    return output;
}

// Função para mover circularmente os caracteres (agora só precisa lidar com maiúsculas)
int circulareMove(int key, int asciiChar) {
    int newKey = key % 26;
    asciiChar = newKey + asciiChar;

    // Garantir que permaneça no intervalo de A-Z (65-90)
    if (asciiChar > 90) {
        asciiChar -= 26;
    } else if (asciiChar < 65) {
        asciiChar += 26;
    }

    return asciiChar;
}

string CesarCipher::encrypt(const string& text, int key) {
    string plainText = normalizarTexto(text);
    string buffer;

    for (char c : plainText) {
        int asciiChar = static_cast<int>(c);

        // Apenas processar caracteres maiúsculos (65-90)
        if (asciiChar >= 65 && asciiChar <= 90) {
            asciiChar = circulareMove(key, asciiChar);
        }

        buffer += static_cast<char>(asciiChar);
    }

    return buffer;
}

string CesarCipher::decrypt(const string& text, int key) {
    int inverseKey = key * -1;
    string plainText = normalizarTexto(text);
    string buffer = encrypt(plainText, inverseKey);

    return buffer;
}