//Copyright [2020] <Nicolas Vanz & Leonardo Rocha>

#include <iostream>
#include <fstream>
#include <string>
#include "fila.h"

bool get_tags (char *filename);

void get_datasets (char *filename);

int main() {

    char xmlfilename[100];
    structures::LinkedQueue<std::string>fila{};
    while (true){
        std::cin >> xmlfilename;  // entrada

        if (!get_tags(xmlfilename)) {
            std::cout << "error\n";
        } else {
            get_datasets(xmlfilename);
        }
    }
    return 0;
}
