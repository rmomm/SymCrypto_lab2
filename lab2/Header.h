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
const int M = 32;

string readText(const string& filename);
string normalizeText(const string& text);

int charToIndex(char c);
char indexToChar(int i);

string vigenereEncrypt(const string& text, const string& key);
string vigenereDecrypt(const string& text, const string& key);
double indexOfCoincidence(const string& text);


double calculateH1(const string& text);
