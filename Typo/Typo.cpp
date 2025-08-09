#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <json.hpp>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    if (argc == 2) {
        const string filename = argv[1];
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename << "'\n";
            return 1;
        }

        string line;
        while (getline(file, line)) {
            cout << line << "\n";
        }
        return 0;

    }
    else if (argc == 1) 
    {
        ifstream file("Texts.json");

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

        cout << data[to_string(index)];
    }
    
    else {
        cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
}

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

void engine(string& text) {
    string userText;
    bool erorr = false;

    while (userText != text)
    {
        userText += getch();
        writeText(text, userText);
        if (text.find(userText) == string::npos) {
            erorr == true;
        } else erorr = false;
        displayKeyboard(text[userText.size()], erorr);
    }

}

void writeText(string& text, string& userText) {
    for (int textIndex = 0; textIndex < text.size(); textIndex++) {
        if (textIndex < userText.size()) {
            if (text[textIndex] == userText[textIndex]) {
                cout << "\033[32" << text[textIndex] << "\033[0m";
            }
            else cout << "\033[31" << text[textIndex] << "\033[0m";
        }
        else cout << "\033[37" << text[textIndex] << "\033[0m";
    }
}

void displayKeyboard(char& ch, bool& erorr) {
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
    {"ctrl","win","alt","space","alt","fn","menu","ctrl"}};

    vector<vector<string>>keys_for_find_caps={
    {"`","1","2","3","4","5","6","7","8","9","0","-","=","backspace"},
    {"tab","Q","W","E","R","T","Y","U","I","O","P","[","]","\\"},
    {"caps","A","S","D","F","G","H","J","K","L",":","\"","\n"},
    {"shift","Z","X","C","V","B","N","M",",",".","/","shift"},
    {"ctrl","win","alt","space","alt","fn","menu","ctrl"}};

    
}