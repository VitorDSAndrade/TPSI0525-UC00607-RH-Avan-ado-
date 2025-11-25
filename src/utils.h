#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <algorithm>

// Cifra simples XOR para ofuscar nomes no ficheiro
inline std::string cifraXOR(const std::string &txt, unsigned char chave = 0x5A) {
    std::string r = txt;
    for (char &c : r) {
        c = c ^ chave;
    }
    return r;
}

// Converter string para minúsculas (para comparar nomes)
inline std::string minusculas(std::string s) {
    for (char &c : s) c = std::tolower(c);
    return s;
}

#endif
