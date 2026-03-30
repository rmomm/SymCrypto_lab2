#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <map>
#include <cmath>
#include<set>
using namespace std;

const string ALPHABET = "אבגדהוזחטיךכלםמןנסעףפץצקרשתûü‎‏ÿ"; 
const int M = ALPHABET.size();

string readText(const string& filename);
string cleanText(const string& text);
string removeSpaces(const string& text);

double calculateH1(const map<char, int>& freq, int total);
double calculateH2(const map<string, int>& freq, int total);

map<char, int> LetterFreq(const string& text);
map<string, int> BigramFreq(const string& text);
map<string, int> BigramFreqN(const string& text);
void printLetters(const string& text, ofstream& out);
void printBigram(const string& text, ofstream& out);
void printBigramN(const string& text, ofstream& out);
