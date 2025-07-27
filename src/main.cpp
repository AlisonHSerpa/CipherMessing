#include <array>
#include <iostream>
#include "../include/CesarCipher.h"
#include "../include/MonoalphabetCipher.h"
#include "../include/VigenereCipher.h"
#include "../include/HillCipher.h"
#include "../include/PlayfairCipher.h"
#include "../include/OTPCipher.h"
#include "../include/RailFenceCipher.h"
#include "../include/TPCCipher.h"
#include "../include/DoubleTranspositionCipher.h"

using namespace std;

int main() {

    //CIFRA DE CESAR
    CesarCipher cipher;
    int key = 30;

    string plainText = "BanaNAÇa";
    string cipherText = cipher.encrypt(plainText, key);

    cout << "Texto original cifra de Cesar: " << plainText << endl;
    cout << "Texto cifrado cifra de Cesar: " << cipherText << endl;
    cout << "Texto decifrado cifra de Cesar: " << cipher.decrypt(cipherText, key) << '\n' << endl;




    //CIFRA MONOALPHABETICA
    std::array<int, 26> myKey;
    MonoalphabetCipher::createKey(myKey);

    plainText = "ALison";
    cipherText = MonoalphabetCipher::encrypt(plainText, myKey);

    std::cout << "texto original Monoalfabetico: " << plainText << std::endl;
    std::cout << "texto encriptado Monoalfabetico: " << cipherText<< std::endl;
    std::cout << "texto decifrado Monoalfabetico: " << MonoalphabetCipher::decrypt(cipherText, myKey) << '\n' << std::endl;




    //CIFRA DE VIGENERE
    VigenereCipher vigenereCipher;
    string viginerekey = "cipher";

    plainText = "Abacaxi";
    cipherText = vigenereCipher.encrypt(plainText, viginerekey);

    std::cout << "texto original Vigenere: " << plainText << std::endl;
    std::cout << "texto cifrado Vigenere: " << cipherText << std::endl;
    std::cout << "texto decifrado Vigenere: " << vigenereCipher.decrypt(cipherText, viginerekey) << '\n' << std::endl;




    //CIFRA DE HILL
    // Cria o cifrador com bloco de tamanho 2
    HillCipher hillcipher(2);

    // Define a chave (matriz 2x2)
    std::vector<std::vector<int>> hillkey = {
        {3, 3},
        {2, 5}
    };

    // Texto para encriptar (deve ter o numero de letras sendo multiplo do bloco)
    plainText = "AliSOn";
    std::cout << "Texto original cifra de hill: " << plainText << std::endl;

    // Encriptacao
    cipherText = hillcipher.encrypt(plainText, hillkey);
    std::cout << "Texto encriptado cifra de hill: " << cipherText << std::endl;

    // Decriptaçcao
    std::string decrypted = hillcipher.decrypt(cipherText, hillkey);
    std::cout << "Texto decriptado cifra de hill: " << decrypted << '\n' << std::endl;




    //CIFRA DE PLAYFAIR
    std::string playfairKey = "MONARCHY";
    PlayfairCipher playfairCipher(playfairKey);

    plainText = "Hello World!";
    std::cout << "Texto original cifra de playfair: " << plainText;

    // Mostra a matriz de chave
    std::cout << "\nMatriz de chave:\n";
    playfairCipher.printKeyMatrix();

    // Encripta o texto
    cipherText = playfairCipher.encrypt(plainText);
    std::cout << "Texto encriptado cifra de playfair: " << cipherText << '\n';

    // Decripta o texto
    decrypted = playfairCipher.decrypt(cipherText);
    std::cout << "Texto decriptado cifra de playfair: " << decrypted << '\n' << std::endl;



    //CIFRA DE ONE TIME PAD (MODO ALEATORIO)
    OTPCipher otpcipher;
    plainText = "Secret Message";

    cipherText = otpcipher.encrypt(plainText);
    std::string hexCiphertext = otpcipher.toHex(cipherText);

    std::cout << "Texto original cifra one time pad: " << plainText << "\n";
    std::cout << "Texto cifrado em hexadecimal por one time pad: " << hexCiphertext << "\n";

    decrypted = otpcipher.decrypt(cipherText);
    std::cout << "Texto decriptado cifra de one time pad: " << decrypted << "\n\n";



    //CIFRA DE ONE TIME PAD (MODO VERNAM)
    std::string userKey = "MySecretKey12345";
    OTPCipher vernamcipher(userKey);
    plainText = "Another Message";

    cipherText = vernamcipher.encrypt(plainText);
    hexCiphertext = vernamcipher.toHex(cipherText);

    std::cout << "Example 2 - Pre-defined key:\n";
    std::cout << "Plaintext: " << plainText << "\n";
    std::cout << "Ciphertext (hex): " << hexCiphertext << "\n";

    OTPCipher cipher2(userKey);
    decrypted = cipher2.decrypt(cipherText);
    std::cout << "Decrypted: " << decrypted << "\n\n";




    // CIFRA DE RAILFENCE (TRANSPOSICAO)
    RailFenceCipher railFence(3);

    std::string plaintext = "ATAQUEAOAMANHECER";
    std::string encrypted = railFence.encrypt(plaintext);
    std::string decrypted_railfence = railFence.decrypt(encrypted);

    std::cout << "Texto original cifra de Rail Fence: " << plaintext << "\n";
    std::cout << "Texto cifrado Rail Fence: " << encrypted << "\n";
    std::cout << "Texto decifrado Rail Fence: " << decrypted_railfence << "\n\n";




    // CIFRA DE TRANSPOSICAO POR COLUNAS
    std::string columnKey = "ZEBRAS";
    ColumnarTranspositionCipher columnCipher(columnKey);

    plainText = "ATTACKATDAWN";
    cipherText = columnCipher.encrypt(plainText);
    decrypted = columnCipher.decrypt(cipherText);

    std::cout << "Texto original cifra de Colunas: " << plainText << "\n";
    std::cout << "Texto cifrado por Colunas: " << cipherText << "\n";
    std::cout << "Texto decifrado por Colunas: " << decrypted << "\n\n";



    // CIFRA DE DUPLA TRANSPOSIÇÃO
    std::string key1 = "ZEBRAS";
    std::string key2 = "LOVELY";
    DoubleTranspositionCipher doubleTrans(key1, key2);

    plainText = "ATAQUEAOAMANHECER";
    cipherText = doubleTrans.encrypt(plainText);
    decrypted = doubleTrans.decrypt(cipherText);

    std::cout << "Texto original cifra de Dupla Transposicao: " << plainText << "\n";
    std::cout << "Texto cifrado Dupla Transposicao: " << cipherText << "\n";
    std::cout << "Texto decifrado Dupla Transposicao: " << decrypted << "\n";

    return 0;
}