//
// Created by Alison on 18/06/2025.
//

#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include <string>
#include <vector>

class HillCipher {
private:
    int block_size;  // Tamanho do bloco usado na cifra (padrão: 2)

    // Métodos auxiliares privados

    // Calcula o determinante de uma matriz 2x2 (mod 26)
    int calculateDeterminant(const std::vector<std::vector<int>>& keyMatrix) const;

    // Calcula o inverso multiplicativo de 'a' módulo 'm' (padrão: m=26)
    // Lança uma exceção se o inverso não existir.
    int calculateModInverse(int numberToInvert, int moduloValue = 26) const;

    // Calcula a matriz adjunta (transposta da matriz de cofatores) de uma matriz 2x2
    std::vector<std::vector<int>> calculateAdjugate(const std::vector<std::vector<int>>& keyMatrix) const;

    // Multiplica uma matriz por um vetor e retorna o resultado módulo 26
    std::vector<int> multiplyMatrixVector(
        const std::vector<std::vector<int>>& keyMatrix,
        const std::vector<int>& inputVector
    ) const;

public:
    // Construtor com tamanho de bloco padrão 2
    explicit HillCipher(int blockSize = 2);

    // Cifra um texto usando a matriz chave fornecida.
    // - Remove caracteres não-alfabéticos e converte para maiúsculas.
    // - Adiciona padding 'X' se necessário.
    std::string encrypt(
        const std::string& plaintext,
        const std::vector<std::vector<int>>& keyMatrix
    ) const;

    // Decifra um texto usando a matriz chave fornecida.
    // - Requer que o texto tenha tamanho múltiplo do bloco.
    // - Lança exceção se a matriz não for invertível.
    std::string decrypt(
        const std::string& ciphertext,
        const std::vector<std::vector<int>>& keyMatrix
    ) const;
};

#endif //HILLCIPHER_H