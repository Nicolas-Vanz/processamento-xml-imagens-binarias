//  Copyright [2020] <Nicolas Vanz & Leonardo Rocha>

#include <iostream>
#include "pilha.h"
#include "fila.h"
#include <fstream>
#include <string>

struct Dataset {
    std::string name;
    int height;
    int width;
    int *data;
};

structures::LinkedQueue<std::string>fila{};


bool is_open_tag(std::string tag) {
    if (tag[1] == '/') return false;
    return true;
}

bool get_tags (char *filename) {
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


void get_datasets (char *filename) {
    std::string tag, data, line;
    std::ifstream file(filename);
    int i, j;
    if (file.is_open()) {
        while (getline (file, line)) {
            i = j = 0;
            while (i < line.size()) {
                if (line[i] == '<') {
                    j = i;
                    while (line[j] != '>') j++;
                    tag = line.substr(i, j - i + 1);
                    fila.enqueue(tag);
                    i = j;
                } else {
                    j = i;
                    while (line[j] != '<' && j < line.size()) j++;
                    data = line.substr(i + 1, j - i - 1);
                    i = j;
                    if (data[0] != '\0') {
                        fila.enqueue(data);
                    }
                }
            }
        }
    }
}
/*
DoublyLinkedList get_datasets(char *filename) {
    structures::DoublyLinkedList<struct *Dataset>lista{};
    std::string line;
    int start, end;
    std::ifstream file(filename);
    structures::LinkedStack<std::string>stack{};
    int i, j;
    if (file.is_open()) {
        while (getline (file, line)) {
            struct Dataset *dataset;
            start = IndexOf(line, "<name>");
            end = IndexOf(line, "</name>");
            dataset->name = line.substr(start + 6, end -1);
        }
    }
}
*/
