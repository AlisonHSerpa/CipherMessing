#include "../../include/PlayfairCipher.h"
#include <cctype>
#include <iostream>
#include <stdexcept>

using namespace std;

PlayfairCipher::PlayfairCipher(const std::string& key) {
    buildKeyMatrix(key);
}

// Prepara o texto convertendo para maiúsculas e tratando 'J'
string PlayfairCipher::prepareText(const string& text) const {
    string prepared;
    for (char c : text) {
        if (isalpha(c)) {
            char upper = toupper(c);
            // Substitui 'J' por 'I' consistentemente
            if (upper == 'J') upper = 'I';
            prepared.push_back(upper);
        }
    }
    return prepared;
}

// Processa pares de caracteres para adicionar 'X' se necessário
std::string PlayfairCipher::processPairs(const std::string& text) const {
    if (text.empty()) return "";

    std::string processed;
    for (size_t i = 0; i < text.size(); ) {
        if (i + 1 >= text.size()) {
            // Último caractere sozinho, adiciona 'X'
            processed.push_back(text[i]);
            processed.push_back('X');
            break;
        }
        else if (text[i] == text[i + 1]) {
            // Caracteres iguais, insere 'X' entre eles
            processed.push_back(text[i]);
            processed.push_back('X');
            i++; // Avança apenas um caractere
        }
        else {
            processed.push_back(text[i]);
            processed.push_back(text[i + 1]);
            i += 2;
        }
    }
    return processed;
}

// Encontra a posição de um caractere na matriz de chave
pair<int, int> PlayfairCipher::findPosition(char c) const {
    // Garante que o caractere seja tratado consistentemente
    char upper = toupper(c);
    if (upper == 'J') upper = 'I';

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 5; ++col) {
            if (keyMatrix[row][col] == upper) {
                return { row, col };
            }
        }
    }
    throw invalid_argument("Caractere não encontrado na matriz de chave: " + string(1, c));
}

// Constrói a matriz de chave
void PlayfairCipher::buildKeyMatrix(const string& key) {
    string preparedKey = prepareText(key);
    string uniqueChars;
    bool used[26] = { false };

    // Adiciona caracteres da chave primeiro
    for (char c : preparedKey) {
        if (!used[c - 'A']) {
            uniqueChars.push_back(c);
            used[c - 'A'] = true;
        }
    }

    // Adiciona o resto do alfabeto (exceto 'J')
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c != 'J' && !used[c - 'A']) {
            uniqueChars.push_back(c);
        }
    }

    // Preenche a matriz 5x5
    keyMatrix.resize(5, vector<char>(5));
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            keyMatrix[i][j] = uniqueChars[i * 5 + j];
        }
    }
}

// Função para encriptar texto
string PlayfairCipher::encrypt(const string& plaintext) {
    string prepared = prepareText(plaintext);
    if (prepared.empty()) return "";

    string processed = processPairs(prepared);
    string ciphertext;

    for (size_t i = 0; i < processed.size(); i += 2) {
        if (i + 1 >= processed.size()) {
            throw logic_error("Texto processado tem tamanho ímpar - isso não deveria acontecer");
        }

        char a = processed[i];
        char b = processed[i + 1];
        auto posA = findPosition(a);
        auto posB = findPosition(b);

        int rowA = posA.first, colA = posA.second;
        int rowB = posB.first, colB = posB.second;

        if (rowA == rowB) {
            ciphertext += keyMatrix[rowA][(colA + 1) % 5];
            ciphertext += keyMatrix[rowB][(colB + 1) % 5];
        }
        else if (colA == colB) {
            ciphertext += keyMatrix[(rowA + 1) % 5][colA];
            ciphertext += keyMatrix[(rowB + 1) % 5][colB];
        }
        else {
            ciphertext += keyMatrix[rowA][colB];
            ciphertext += keyMatrix[rowB][colA];
        }
    }

    return ciphertext;
}

// Função para desencriptar texto
string PlayfairCipher::decrypt(const string& ciphertext) {
    string prepared = prepareText(ciphertext);
    if (prepared.empty()) return "";
    if (prepared.size() % 2 != 0) {
        throw invalid_argument("Texto cifrado deve ter tamanho par");
    }

    string plaintext;
    for (size_t i = 0; i < prepared.size(); i += 2) {
        char a = prepared[i];
        char b = prepared[i + 1];
        auto posA = findPosition(a);
        auto posB = findPosition(b);

        int rowA = posA.first, colA = posA.second;
        int rowB = posB.first, colB = posB.second;

        if (rowA == rowB) {
            plaintext += keyMatrix[rowA][(colA - 1 + 5) % 5];
            plaintext += keyMatrix[rowB][(colB - 1 + 5) % 5];
        }
        else if (colA == colB) {
            plaintext += keyMatrix[(rowA - 1 + 5) % 5][colA];
            plaintext += keyMatrix[(rowB - 1 + 5) % 5][colB];
        }
        else {
            plaintext += keyMatrix[rowA][colB];
            plaintext += keyMatrix[rowB][colA];
        }
    }

    // Remove apenas 'X' de preenchimento (último caractere se for 'X' e tamanho for ímpar)
    if (!plaintext.empty() && plaintext.back() == 'X' && plaintext.size() > 1) {
        // Verifica se não é um 'X' válido (entre letras iguais)
        if (plaintext[plaintext.size()-2] != 'X') {
            plaintext.pop_back();
        }
    }

    return plaintext;
}

// Processa texto preservando não-alfabéticos
string PlayfairCipher::processText(const string& text, bool encrypt) {
    string result;
    string buffer;

    for (char c : text) {
        if (isalpha(c)) {
            buffer += toupper(c);
        } else {
            if (!buffer.empty()) {
                string processed = encrypt ? this->encrypt(buffer) : this->decrypt(buffer);
                result += processed;
                buffer.clear();
            }
            result += c;
        }
    }

    if (!buffer.empty()) {
        string processed = encrypt ? this->encrypt(buffer) : this->decrypt(buffer);
        result += processed;
    }

    return result;
}

void PlayfairCipher::printKeyMatrix() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            cout << keyMatrix[i][j] << ' ';
        }
        cout << '\n';
    }
}