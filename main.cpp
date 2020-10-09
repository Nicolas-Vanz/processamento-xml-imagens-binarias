//Copyright [2020] <Nicolas Vanz & Leonardo Rocha>

#include <iostream>
#include <fstream>
#include <string>
#include "fila.h"

bool validade_file (char *filename);

void get_tags (char *filename);

void get_datasets();

void results();

int main() {

    char xmlfilename[100];
    structures::LinkedQueue<std::string>fila{};
    while (true){
        std::cin >> xmlfilename;  // entrada

        if (!validade_file(xmlfilename)) {
            std::cout << "error\n";
        } else {
            get_tags(xmlfilename);
            get_datasets();
            results();
        }
    }
    return 0;
}
