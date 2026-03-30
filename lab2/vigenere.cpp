#include "Header.h"

int charToIndex(char c) {
    return ALPHABET.find(c);
}

char indexToChar(int i) {
    return ALPHABET[i % M];
}

string vigenereEncrypt(const string& text, const string& key) {
    string result;

    int r = key.size();

    for (int i = 0; i < text.size(); i++) {
        int xi = charToIndex(text[i]);
        int ki = charToIndex(key[i % r]);

        int yi = (xi + ki) % M;

        result += indexToChar(yi);
    }

    return result;
}

