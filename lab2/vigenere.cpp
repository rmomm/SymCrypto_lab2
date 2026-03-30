#include "Header.h"

vector<double> russianFreq = {
    0.08613915, 0.01685899, 0.03893518, 0.01580327, 0.02972383, 0.08898129, 0.01021049,
    0.01781720, 0.06185643, 0.01041273, 0.03277422, 0.05639005, 0.03215427,  0.06633811,
    0.11069995, 0.02587894, 0.04293776, 0.05288222, 0.06040346, 0.02841050, 0.00289630,
    0.00756939, 0.00359811, 0.01468375, 0.00940275, 0.00356440, 0.00026363, 0.01974566,
    0.02169459, 0.00341634, 0.00561204, 0.02194498
};

int charToIndex(char c) { 
    return c - 'à'; 
}
char indexToChar(int i) { 
    return 'à' + i; 
}

string readText(const string& filename) {
    ifstream file(filename);
    string text, line;
    while (getline(file, line)) { 
        text += line; 
    }
    return text;
}

string normalizeText(const string& text) {
    string result;
    for (char c : text) {
        if (c == '¸') {
            c = 'å';
        }

        if (c >= 'À' && c <= 'ß') { 
            c = c - 'À' + 'à'; 
        }

        if (c >= 'à' && c <= 'ÿ') {
            result += c;
        }
    }
    return result;
}

string vigenereEncrypt(const string& text, const string& key) {
    string result;
    int r = key.size();
    for (int i = 0; i < text.size(); i++) {
        int x = charToIndex(text[i]);
        int k = charToIndex(key[i % r]);
        int y = (x + k) % M;
        result += indexToChar(y);
    }
    return result;
}

string vigenereDecrypt(const string& text, const string& key) {
    string result;
    int r = key.size();
    for (int i = 0; i < text.size(); i++) {
        int y = charToIndex(text[i]);
        int k = charToIndex(key[i % r]);
        int x = (y - k + M) % M; 
        result += indexToChar(x);
    }
    return result;
}

double indexOfCoincidence(const string& text) {
    map<char, int> freq;
    for (char c : text) { 
        freq[c]++; 
    }
    int n = text.size();
    double sum = 0;
    for (auto& p : freq) { 
        sum += p.second * (p.second - 1); 
    }
    return sum / (double)(n * (n - 1));
}

double calculateH1(const string& text) {
    map<char, int> freq;
    for (char c : text) {
        freq[c]++;
    }

    double H = 0.0;
    int n = text.size();
    for (auto& p : freq) {
        double prob = (double)p.second / n;
        if (prob > 0) H -= prob * log2(prob);
    }
    return H;
}

int coincidenceCount(const string& text, int r) {
    int count = 0;
    int n = text.size();
    for (int i = 0; i < n - r; i++){
        if (text[i] == text[i + r]) {
            count++;
        }
    }
    return count;
}

vector<string> splitIntoBlocks(const string& text, int r) {
    vector<string> blocks(r);
    for (int i = 0; i < text.size(); i++){
        blocks[i % r] += text[i];
    }
    return blocks;
}

char mostFrequentChar(const string& text) {
    map<char, int> freq;
    for (char c : text) { 
        freq[c]++; 
    }
    char bestChar = 'à';
    int maxFreq = 0;
    for (auto& p : freq){
        if (p.second > maxFreq) {
            maxFreq = p.second;
            bestChar = p.first;
        }

    }
    return bestChar;
}


string roughKey(const vector<string>& blocks) {
    string key;
    for (const string& b : blocks) {
        char k = (charToIndex(mostFrequentChar(b)) - charToIndex('î') + M) % M + 'à';
        key += k;
    }
    return key;
}

string findKeyAdvanced(const vector<string>& blocks) {
    string key;
    for (const string& block : blocks) {
        vector<int> freq(M, 0);
        for (char c : block) { 
            freq[charToIndex(c)]++; 
        }
        double maxM = -1;
        int bestShift = 0;
        for (int g = 0; g < M; g++) {
            double Mval = 0;
            for (int t = 0; t < M; t++) {
                int shiftedIndex = (t + g) % M;
                double p = russianFreq[t];
                int count = freq[shiftedIndex];
                Mval += p * count;
            }
            if (Mval > maxM) {
                maxM = Mval;
                bestShift = g;
            }
        }
        key += indexToChar(bestShift);
    }
    return key;
}

double averageIndPeriod(const string& text, int r) {
    vector<string> blocks = splitIntoBlocks(text, r);
    double sum = 0.0;
    for (const string& block : blocks){
        sum += indexOfCoincidence(block);
    }
    return sum / r;
}

