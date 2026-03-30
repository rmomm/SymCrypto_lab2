#include "Header.h"

map<char, int> LetterFreq(const string& text) {
    map<char, int> freq;

    for (char c : text) {
        freq[c]++;
    }
    return freq;
}

map<string, int> BigramFreq(const string& text) {
    map<string, int> freq;

    for (size_t i = 0; i + 1 < text.size(); i++) {
        string bg;
        bg += text[i];
        bg += text[i + 1];

        freq[bg]++;
    }
    return freq;
}

map<string, int> BigramFreqN(const string& text) {
    map<string, int> freq;
    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        string bg;
        bg += text[i];
        bg += text[i + 1];
        freq[bg]++;
    }
    return freq;
}


double calculateH1(const map<char, int>& freq, int total) {
    double H1 = 0.0;
    for (auto& pair : freq) {
        double p = (double)pair.second / total;
        if (p > 0) {
            H1 -= p * log2(p);
        }
    }

    return H1;
}

double calculateH2(const map<string, int>& freq, int total) {
    double H2 = 0.0;
    for (auto& pair : freq) {
        double p = (double)pair.second / total;
        if (p > 0) {
            H2 -= p * log2(p);
        }
    }

    return H2 / 2.0;
}