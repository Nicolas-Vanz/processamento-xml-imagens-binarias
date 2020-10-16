//Copyright [2020] <Leonardo Rocha & Nicolas Vanz>

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
    std::cin >> xmlfilename;  //!< arquivo a ser processado
	/* verifica se o arquivo é válido*/
    if (!validade_file(xmlfilename)) {
        std::cout << "error\n";
    } else {
		/* processa o arquivo e obtém as tags e seus valores*/
        get_tags(xmlfilename);
		/* organiza as tags e valores em datasets */
        get_datasets();
		/* processa os datasets e calcula os resultados */
        results();
    }
    return 0;
}
