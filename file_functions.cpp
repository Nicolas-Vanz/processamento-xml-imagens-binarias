//  Copyright [2020] <Nicolas Vanz & Leonardo Rocha>

#include <iostream>
#include "pilha.h"
#include <fstream>
#include <string>

bool is_open_tag(std::string tag) {
    if (tag[1] == '/') return false;
    return true;
}

bool validade_file (char *filename) {
    std::string line, tag, top;
    std::ifstream file(filename);
    structures::LinkedStack<std::string>stack{};
    int i, j;
    if (file.is_open()) {
        while (getline (file, line)) {
            for (i = 0; i < line.size(); i++) {
                if (line[i] == '<') {
                    j = i;
                    while (line[j] != '>') j++;
                    tag = line.substr(i, j - i + 1);
                    if (!is_open_tag(tag)) {
                        if (stack.empty()) return false;
                        if (!is_open_tag(stack.top())) return false;
                        top = stack.pop();
                        if (top.substr(1, top.size() - 2) != tag.substr(2, tag.size() - 3)) return false;
                    } else {
                        stack.push(tag);
                    }
                }
            }
        }
    if (!stack.empty()) return false;
    file.close();
    return true;
    }
    return false;
}
