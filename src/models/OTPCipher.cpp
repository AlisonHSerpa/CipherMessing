//
// Created by Alison on 21/06/2025.
//

#include "../../include/OTPCipher.h"
#include <algorithm>

const std::string OTPCipher::caracteresPermitidos = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

OTPCipher::OTPCipher(const std::string& userKey) : key(userKey) {
    keyGenerated = true;
}

std::string OTPCipher::generateRandomKey(size_t length) {
    std::string randomKey;
    randomKey.reserve(length);

    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribuicao(0, caracteresPermitidos.size() - 1);

    for (size_t i = 0; i < length; i++) {
        int indice = distribuicao(generator);
        randomKey += caracteresPermitidos[indice];
    }

    return randomKey;
}

std::string OTPCipher::xorStrings(const std::string& a, const std::string& b) {
    if (a.length() != b.length()) {
        throw std::invalid_argument("Strings devem ter o mesmo comprimento");
    }

    std::string result;
    result.reserve(a.length());

    for (size_t i = 0; i < a.length(); ++i) {
        result.push_back(a[i] ^ b[i]);
    }

    return result;
}

void OTPCipher::generateKey(size_t length) {
    key = generateRandomKey(length);
    keyGenerated = true;
}

void OTPCipher::setKey(const std::string& userKey) {
    key = userKey;
    keyGenerated = true;
}

std::string OTPCipher::getKey() const {
    if (!keyGenerated) {
        throw std::runtime_error("Nenhuma chave foi gerada ou definida");
    }
    return key;
}

std::string OTPCipher::encrypt(const std::string& plaintext) {
    if (!keyGenerated) {
        key = generateRandomKey(plaintext.length());
        keyGenerated = true;
    }
    else if (key.length() < plaintext.length()) {
        throw std::invalid_argument("A chave é menor que o texto plano");
    }

    return xorStrings(plaintext, key.substr(0, plaintext.length()));
}

std::string OTPCipher::decrypt(const std::string& ciphertext) {
    if (!keyGenerated) {
        throw std::runtime_error("Nenhuma chave foi definida para descriptografia");
    }
    if (key.length() < ciphertext.length()) {
        throw std::invalid_argument("A chave é menor que o texto cifrado");
    }

    return xorStrings(ciphertext, key.substr(0, ciphertext.length()));
}

std::string OTPCipher::toHex(const std::string& input) {
    const char* hex_chars = "0123456789ABCDEF";
    std::string output;
    for (unsigned char c : input) {
        output += hex_chars[(c >> 4) & 0x0F];
        output += hex_chars[c & 0x0F];
    }
    return output;
}

std::string OTPCipher::fromHex(const std::string& input) {
    std::string output;
    if (input.length() % 2 != 0) {
        throw std::invalid_argument("String hexadecimal inválida");
    }

    for (size_t i = 0; i < input.length(); i += 2) {
        unsigned char high = (unsigned char)std::stoi(input.substr(i, 1), nullptr, 16);
        unsigned char low = (unsigned char)std::stoi(input.substr(i + 1, 1), nullptr, 16);
        output.push_back((high << 4) | low);
    }
    return output;
}
