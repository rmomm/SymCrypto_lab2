#include "Header.h"

string readText(const string& filename) {
    ifstream file(filename);

    string text;
    string line;

    while (getline(file, line)) {
        text += line + " ";
    }
    return text;
}

string cleanText(const string& text) {
    string result;
    string alphabet = "абвгдежзийклмнопрстуфхцчшщъыьэюя";

    for (char c : text) {
        c = tolower((unsigned char)c);

        if (alphabet.find(c) != string::npos) {
            result += c;
        }
        else if (c == ' ') {
            result += ' ';
        }
    }
    return result;
}

void printLetters(const string& text, ofstream& out) {
    map<char, int> freq;
    int total = text.size();

    for (char c : text) {
        freq[c]++;
    }

    vector<pair<char, double>> vec;

    for (auto& p : freq) {
        double prob = (double)p.second / total;
        vec.push_back({ p.first, prob });
    }

    sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        }
    );

    out << "Частоти букв:\n";
    for (auto& p : vec) {
        char dchar = (p.first == ' ') ? '_' : p.first;
        out << dchar << " : " << p.second << "\n";
    }
}


void printBigram(const string& text, ofstream& out) {
    map<string, int> freq;
    set<char> letters;

    int total = 0;
    for (char c : text) {
        letters.insert(c);
    }

    for (size_t i = 0; i + 1 < text.size(); i++) {
        string bg;
        bg += text[i];
        bg += text[i + 1];

        freq[bg]++;
        total++;
    }

    out << "\nМатриця біграм (з перетином):\n   ";

    for (char c : letters) {
        char dchar = (c == ' ') ? '_' : c;
        out << setw(9) << dchar;
    }
    out << "\n";

    for (char row : letters) {
        char drow = (row == ' ') ? '_' : row;
        out << setw(6) << drow;

        for (char col : letters) {
            string bg;
            bg += row;
            bg += col;

            double prob = (double)freq[bg] / total;
            out << setw(9) << fixed << setprecision(6) << prob;
        }
        out << "\n";
    }
}

void printBigramN(const string& text, ofstream& out) {
    map<string, int> freq;
    set<char> letters;
    int total = 0;

    for (char c : text) {
        letters.insert(c);
    }

    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        string bg;
        bg += text[i];
        bg += text[i + 1];
        freq[bg]++;
        total++;
    }

    out << "\nМатриця біграм (без перетину):\n   ";

    for (char c : letters) {
        char dchar = (c == ' ') ? '_' : c;
        out << setw(9) << dchar;
    }
    out << "\n";

    for (char row : letters) {
        char drow = (row == ' ') ? '_' : row;
        out << setw(6) << drow;

        for (char col : letters) {
            string bg;
            bg += row;
            bg += col;

            double prob = (double)freq[bg] / total;
            out << setw(9) << fixed << setprecision(6) << prob;
        }
        out << "\n";
    }
}

string removeSpaces(const string& text) {
    string result;

    for (char c : text) {
        if (c != ' ') {
            result += c;
        }
    }

    return result;
}