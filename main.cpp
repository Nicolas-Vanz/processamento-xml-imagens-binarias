//Copyright [2020] <Nicolas Vanz & Leonardo Rocha>

#include <iostream>
#include <fstream>
#include <string>

bool validade_file (char *filename);

int main() {

    char xmlfilename[100];
    while (true){
    std::cin >> xmlfilename;  // entrada

    if (!validade_file(xmlfilename)) {
        std::cout << "error\n";
    }

    std::cout << xmlfilename << std::endl;  // esta linha deve ser removida
    }
    return 0;
}
