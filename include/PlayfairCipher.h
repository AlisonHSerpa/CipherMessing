#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <string>
#include <vector>

class PlayfairCipher {
public:
    // Construtor que recebe a chave para inicializar a cifra
    PlayfairCipher(const std::string& key);

    // Encripta o texto fornecido (somente letras, sem formata��o)
    std::string encrypt(const std::string& plaintext);

    // Decripta o texto fornecido (somente letras, sem formata��o)
    std::string decrypt(const std::string& ciphertext);

    // Processa texto preservando caracteres n�o-alfab�ticos
    // Se encrypt=true, encripta; se false, decripta
    std::string processText(const std::string& text, bool encrypt);

    // Exibe a matriz de chave (para depura��o)
    void printKeyMatrix();

private:
    std::vector<std::vector<char>> keyMatrix; // Matriz 5x5 da chave

    // Prepara o texto removendo caracteres n�o-alfab�ticos e tratando 'J'
    std::string prepareText(const std::string& text) const;

    // Processa pares de caracteres para adicionar 'X' se necess�rio
    std::string processPairs(const std::string& text) const;

    // Encontra a posi��o de um caractere na matriz de chave
    std::pair<int, int> findPosition(char c) const;

    // Constr�i a matriz de chave a partir da chave fornecida
    void buildKeyMatrix(const std::string& key);
};

#endif // PLAYFAIRCIPHER_H