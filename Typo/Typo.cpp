#include <iostream>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Ошибка: Укажите файл. Пример: typo file.txt\n");
        return 1;
    }
    
    if (argc == 1) {
        FILE* file = fopen(argv[1], "r");
        if (!file) {
            perror("Ошибка открытия файла");
            return 1;
        }

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }

        fclose(file);
        return 0;
    }
    else {

    }
}