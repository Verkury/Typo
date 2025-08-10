#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <json.hpp>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <stdlib.h>

using namespace std;
using json = nlohmann::json;


char getch() {
    char ch;
    struct termios old_settings, new_settings;
    
    tcgetattr(STDIN_FILENO, &old_settings);
    new_settings = old_settings;
    new_settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
    read(STDIN_FILENO, &ch, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    
    return ch;
}

void writeText(string text, string& userText) {
    for (int textIndex = 0; textIndex < text.size(); textIndex++) {
        if (textIndex < userText.size()) {
            if (text[textIndex] == userText[textIndex]) {
                cout << "\033[32m" << text[textIndex] << "\033[0m";
            }
            else cout << "\033[31m" << text[textIndex] << "\033[0m";
        }
        else cout << "\033[37m" << text[textIndex] << "\033[0m";
    }
}

void displayKeyboard(const string& ch) {
    vector<vector<string>>keys={
    {"[~] ","[1] ","[2] ","[3] ","[4] ","[5] ","[6] ","[7] ","[8] ","[9] ","[0] ","[-] ","[=] ","[<-- ]\n"},
    {"[Tab] ","[q] ","[w] ","[e] ","[r] ","[t] ","[y] ","[u] ","[i] ","[o] ","[p] ","[{] ","[}] ","[\\ ]\n"},
    {"[Caps] ","[a] ","[s] ","[d] ","[f] ","[g] ","[h] ","[j] ","[k] ","[l] ","[;] ","[\'] ","[Enter]\n"},
    {"[Shift] ","[z] ","[x] ","[c] ","[v] ","[b] ","[n] ","[m] ","[,] ","[.] ","[/] ","[  Shift ]\n"},
    {"[Ctrl] ","[Win] ","[Alt] ","[    Space   ] ","[Alt] ","[Fn] ","[Menu] ","[Ctrl]\n"}};

    vector<vector<string>>keys_for_find={
    {"`","1","2","3","4","5","6","7","8","9","0","-","=","backspace"},
    {"tab","q","w","e","r","t","y","u","i","o","p","[","]","\\"},
    {"caps","a","s","d","f","g","h","j","k","l",";","\'","\n"},
    {"shift","z","x","c","v","b","n","m",",",".","/","shift"},
    {"ctrl","win","alt"," ","alt","fn","menu","ctrl"}};

    vector<vector<string>>keys_for_find_caps={
    {"`","1","2","3","4","5","6","7","8","9","0","-","=","backspace"},
    {"tab","Q","W","E","R","T","Y","U","I","O","P","[","]","\\"},
    {"caps","A","S","D","F","G","H","J","K","L",":","\"","\n"},
    {"shift","Z","X","C","V","B","N","M",",",".","/","shift"},
    {"ctrl","win","alt"," ","alt","fn","menu","ctrl"}};
    
    bool shift = false;

    for (int indexUp = 0; indexUp < keys_for_find.size(); indexUp++) {
        for (int indexDown = 0; indexDown < keys_for_find[indexUp].size(); indexDown++) {
            if (indexUp == 0 && indexDown == 13 && ch == "backspace") {
                cout << "\033[31m" << keys[indexUp][indexDown] << "\033[0m";
            }
            else if (ch == keys_for_find[indexUp][indexDown]) {
                cout << "\033[34m" << keys[indexUp][indexDown] << "\033[0m";
            }
            else {
                if (ch == keys_for_find_caps[indexUp][indexDown]){
                    cout << "\033[34m" << keys[indexUp][indexDown] << "\033[0m";
                    shift = true;
                    continue;
                }
                if (shift && indexUp == 3 && indexDown == 11) {
                    cout << "\033[34m" << keys[indexUp][indexDown] << "\033[0m";
                    shift = true;
                    continue;
                }
                cout << "\033[37m" << keys[indexUp][indexDown] << "\033[0m";
            }
        }
    }
}

int engine(string text) {
    string userTextOld = "st";
    string userText;

    while (userText != text) {
        if (userText != userTextOld) {
            system("clear");
            writeText(text, userText);

            cout << "\n\n\n";
            cout << userText << "|";
            cout << "\n\n\n";

            if (text.find(userText) == string::npos) {
                displayKeyboard("backspace");
            }
            else{ 
                displayKeyboard(string(1, text[userText.size()]));
            }
            userTextOld = userText;
        }
        char cha = getch();
        if (cha == 127 || cha == '\b') { 
            if (!userText.empty()) {
                userText.pop_back();
            }
        }else userText += cha;
    }
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        const string filename = argv[1];
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename << "'\n";
            return 1;
        }

        string line;
        string text;
        while (getline(file, line)) {
            text += line += "\n";
        }
        int code = engine(text);
        return code;
    }
    else if (argc == 1) 
    {
        ifstream file("Texts.json", ios::binary);

        if (!file.is_open()) {
            cerr << "Erorr: Could not open file,try again, if the error remains, let us know.\n";
            return 1;
        }

        json data;
        file >> data;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 20);
        int index = distrib(gen);

        int code = engine(to_string(data[to_string(index)]));
        return code;
    }
    else {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
}