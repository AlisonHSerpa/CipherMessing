cmake_minimum_required(VERSION 3.31)
project(CipherMessing)

set(CMAKE_CXX_STANDARD 20)

add_executable(CipherMessing src/main.cpp
        src/models/CesarCipher.cpp
        src/models/MonoalphabetCipher.cpp
        src/models/VigenereCipher.cpp
        src/models/HillCipher.cpp
        src/models/PlayfairCipher.cpp
        src/models/OTPCipher.cpp
        src/models/RailFenceCipher.cpp
        src/models/TPCCipher.cpp
        src/models/DoubleTranspositionCipher.cpp
)
