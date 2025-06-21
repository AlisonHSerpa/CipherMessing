//
// Created by Alison on 21/05/2025.
//
#pragma once
#include <string>


class MonoalphabetCipher {
public:
    static void createKey(std::array<int, 26>& keyArray);
    static std::string encrypt(const std::string& plainText, const std::array<int, 26>& key);
    static std::string normalizarTexto(const std::string &input);
    static std::string decrypt(const std::string &cipherText, const std::array<int, 26>& key);
};

