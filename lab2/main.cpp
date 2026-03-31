#include "Header.h"

    int main() {
        ofstream out("result.txt");

        string plain = readText("text.txt");
        plain = normalizeText(plain);

        out << "Довжина відкритого тексту: " << plain.size() << "\n";

        vector<string> keys = {
            "ау",        
            "мир",    
            "игла",  
            "крыша",     
            "социализация" 
        };

        double I_plain = indexOfCoincidence(plain);
        out << "\nІндекс відповідності відкритого тексту: " << I_plain << "\n\n";

        for (const string& key : keys) {
            string cipher = vigenereEncrypt(plain, key);

            double I = indexOfCoincidence(cipher);

            out << "Ключ: " << key << "\n";
            out << "Довжина ключа: " << key.size() << "\n";
            out << "Індекс відповідності: " << I << "\n\n";

            out << "Шифротекст:\n";
            out << cipher.substr(0, 300) << "...\n\n";
        }

        out << "---------------------------------------------\n";
        out << "Варіант 12\n";
        string text = readText("text_12.txt");
        text = normalizeText(text);

        out << "Довжина тексту: " << text.size() << "\n\n";

        out << "Метод збігів D(r) \n";

        int best_r_D = 0;
        int maxD = 0;

        for (int r = 2; r <= 30; r++) {
            int D = coincidenceCount(text, r);
            out << "r = " << r << " -> D = " << D << "\n";

            if (D > maxD) {
                maxD = D;
                best_r_D = r;
            }
        }

        out << "\nНайкращий r (D): " << best_r_D << "\n\n";

        out << " Метод індексу відповідності \n";

        int best_r_I = 0;
        double bestI = 0;

        for (int r = 2; r <= 30; r++) {
            double I = averageIndPeriod(text, r);
            out << "r = " << r << " -> I = " << I << "\n";

            if (I > bestI) {
                bestI = I;
                best_r_I = r;
            }
        }

        out << "\nНайкращий r (I): " << best_r_I << "\n\n";

        int r = best_r_D;

        vector<string> blocks = splitIntoBlocks(text, r);

        string keyRough = roughKey(blocks);
        out << "Грубий ключ: " << keyRough << "\n";

        string keyAdvanced = findKeyAdvanced(blocks);
        out << "Точний ключ: " << keyAdvanced << "\n\n";

        string decrypted = vigenereDecrypt(text, keyAdvanced);

        out << " ДЕШИФРОВАНИЙ ТЕКСТ \n";
        out << decrypted << "\n\n";

        double Itext = indexOfCoincidence(decrypted);
        out << "Індекс відповідності дешифрованого тексту: " << Itext << "\n";

        double H = calculateH1(decrypted);
        out << "Ентропія H1: " << H << "\n";

        out.close();


        return 0;
    }
