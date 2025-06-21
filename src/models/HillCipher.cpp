//
// Created by Alison on 18/06/2025.
//

#include "../../include/HillCipher.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

using namespace std;

// Implementação do construtor
HillCipher::HillCipher(int blockSize) : block_size(blockSize) {}

    // Implementação dos métodos privados
    int HillCipher::calculateDeterminant(const vector<vector<int>>& matrix) const {
        if (matrix.size() == 2) {
            return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
        }
        throw runtime_error("Tamanho de matriz não suportado");
    }

    int HillCipher::calculateModInverse(int a, int m) const {
        a = a % m;
        for (int x = 1; x < m; x++) {
            if ((a * x) % m == 1) {
                return x;
            }
        }
        throw runtime_error("Inverso multiplicativo não encontrado");
    }

    vector<vector<int>> HillCipher::calculateAdjugate(const vector<vector<int>>& matrix) const {
        if (matrix.size() == 2) {
            return {
                {matrix[1][1], -matrix[0][1]},
                {-matrix[1][0], matrix[0][0]}
            };
        }
        throw runtime_error("Tamanho de matriz não suportado");
    }

    vector<int> HillCipher::multiplyMatrixVector(const vector<vector<int>>& matrix, const vector<int>& vec) const {
        vector<int> result;
        for (const auto& row : matrix) {
            int sum = 0;
            for (size_t i = 0; i < row.size(); i++) {
                sum += row[i] * vec[i];
            }
            result.push_back(sum % 26);
        }
        return result;
    }

// Implementação dos métodos públicos
string HillCipher::encrypt(const string& plaintext,
                         const vector<vector<int>>& key_matrix) const {
    string processed_text;
    for (char c : plaintext) {
        if (isalpha(c)) {
            processed_text += toupper(c);
        }
    }

    int padding = block_size - (processed_text.size() % block_size);
    if (padding != block_size) {
        processed_text += string(padding, 'X');
    }

    string ciphertext;
    for (size_t i = 0; i < processed_text.size(); i += block_size) {
        vector<int> block_vec;
        for (int j = 0; j < block_size; j++) {
            block_vec.push_back(processed_text[i + j] - 'A');
        }

        vector<int> encrypted_vec = multiplyMatrixVector(key_matrix, block_vec);
        for (int num : encrypted_vec) {
            ciphertext += static_cast<char>(num + 'A');
        }
    }
    return ciphertext;
}

string HillCipher::decrypt(const string& ciphertext,
                         const vector<vector<int>>& key_matrix) const {
    // Verifica se o tamanho do texto é múltiplo do bloco
    if (ciphertext.size() % block_size != 0) {
        throw runtime_error("O tamanho do texto cifrado deve ser multiplo do bloco");
    }

    int det = calculateDeterminant(key_matrix);
    if (gcd(det, 26) != 1) {
        throw runtime_error("A matriz chave nao eh invertivel modulo 26");
    }

    int det_inv = calculateModInverse(det);
    vector<vector<int>> adj = calculateAdjugate(key_matrix);
    vector<vector<int>> inv_key(block_size, vector<int>(block_size));

    // Calcula a matriz inversa modular
    for (int i = 0; i < block_size; i++) {
        for (int j = 0; j < block_size; j++) {
            inv_key[i][j] = (adj[i][j] * det_inv) % 26;
            if (inv_key[i][j] < 0) inv_key[i][j] += 26;
        }
    }

    string plaintext;
    for (size_t i = 0; i < ciphertext.size(); i += block_size) {
        vector<int> block_vec;
        for (int j = 0; j < block_size; j++) {
            char c = ciphertext[i + j];
            if (c < 'A' || c > 'Z') {
                throw runtime_error("Texto cifrado deve conter apenas letras maiusculas");
            }
            block_vec.push_back(c - 'A');
        }

        vector<int> decrypted_vec = multiplyMatrixVector(inv_key, block_vec);
        for (int num : decrypted_vec) {
            plaintext += static_cast<char>(num + 'A');
        }
    }
    return plaintext;
}