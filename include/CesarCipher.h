#pragma once
#include <string>

class CesarCipher {
public:
    CesarCipher() = default;
    std::string encrypt(const std::string& text, int key);
    std::string decrypt(const std::string& text, int key);
};