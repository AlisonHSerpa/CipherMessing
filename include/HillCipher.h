//
// Created by Alison on 18/06/2025.
//

#ifndef HILLCIPHER_H
#define HILLCIPHER_H

#include <string>
#include <vector>

class HillCipher {
private:
    int block_size;  // Tamanho do bloco usado na cifra (padr�o: 2)

    // M�todos auxiliares privados

    // Calcula o determinante de uma matriz 2x2 (mod 26)
    int calculateDeterminant(const std::vector<std::vector<int>>& keyMatrix) const;

    // Calcula o inverso multiplicativo de 'a' m�dulo 'm' (padr�o: m=26)
    // Lan�a uma exce��o se o inverso n�o existir.
    int calculateModInverse(int numberToInvert, int moduloValue = 26) const;

    // Calcula a matriz adjunta (transposta da matriz de cofatores) de uma matriz 2x2
    std::vector<std::vector<int>> calculateAdjugate(const std::vector<std::vector<int>>& keyMatrix) const;

    // Multiplica uma matriz por um vetor e retorna o resultado m�dulo 26
    std::vector<int> multiplyMatrixVector(
        const std::vector<std::vector<int>>& keyMatrix,
        const std::vector<int>& inputVector
    ) const;

public:
    // Construtor com tamanho de bloco padr�o 2
    explicit HillCipher(int blockSize = 2);

    // Cifra um texto usando a matriz chave fornecida.
    // - Remove caracteres n�o-alfab�ticos e converte para mai�sculas.
    // - Adiciona padding 'X' se necess�rio.
    std::string encrypt(
        const std::string& plaintext,
        const std::vector<std::vector<int>>& keyMatrix
    ) const;

    // Decifra um texto usando a matriz chave fornecida.
    // - Requer que o texto tenha tamanho m�ltiplo do bloco.
    // - Lan�a exce��o se a matriz n�o for invert�vel.
    std::string decrypt(
        const std::string& ciphertext,
        const std::vector<std::vector<int>>& keyMatrix
    ) const;
};

#endif //HILLCIPHER_H