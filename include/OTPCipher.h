//
// Created by Alison on 21/06/2025.
//

#ifndef OTPCIPHER_H
#define OTPCIPHER_H

#pragma once
#include <string>
#include <stdexcept>
#include <random>

class OTPCipher {
private:
    std::string key;
    bool keyGenerated = false;

    std::string generateRandomKey(size_t length);
    std::string xorStrings(const std::string& a, const std::string& b);

public:
    OTPCipher() = default;

    static const std::string caracteresPermitidos;

    explicit OTPCipher(const std::string& userKey);

    void generateKey(size_t length);
    void setKey(const std::string& userKey);
    std::string getKey() const;

    std::string encrypt(const std::string& plaintext);
    std::string decrypt(const std::string& ciphertext);

    std::string toHex(const std::string& input);
    std::string fromHex(const std::string& input);
};

#endif //OTPCIPHER_H
