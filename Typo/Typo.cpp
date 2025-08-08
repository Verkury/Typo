#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <json.hpp>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]) {
    // Проверяем, передан ли аргумент (имя файла)
    if (argc == 2) {
        const string filename = argv[1];
        ifstream file(filename);

        if (!file.is_open()) {
            cerr << "Error: Could not open file '" << filename << "'\n";
            return 1;
        }

        // Просто выводим содержимое файла (аналог `cat`)
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
            cerr << "Не удалось открыть файл!\n";
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