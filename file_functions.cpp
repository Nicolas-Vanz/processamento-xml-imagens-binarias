//  Copyright [2020] <Nicolas Vanz & Leonardo Rocha>

#include <iostream>
#include "pilha.h"
#include "fila.h"
#include <fstream>
#include <string>

//! struct Dataset
/*!
* Estrutura para definir informações dos blocos de cada IMG e seus respectivos atributos gerais.
*/
struct Dataset {
    std::string name; //!< Nome de imagem atual, ex: 06.png
    int height; //!< Altura(numero de linhas), do desenho.
    int width; //!< Largura(numero de colunas), do desenho.
    int **data; //!< Conteudo do desenho da imagem atual.
};

structures::LinkedQueue<std::string>fila{}; //!< Fila de todas as linhas do arquivo
structures::LinkedQueue<struct Dataset*>datasets{}; //!< Fila de todas estruturas organizadas e ordem.

//! is_open_tag
/*!
* Metodo para retornar se uma tag é de abertura <exemplo> ou de fechamento </exemplo>
* \param tag uma string com a tag dada como parametro.
*/
bool is_open_tag(std::string tag) {
    if (tag[1] == '/') return false;
    return true;
}

//! validate_file
/*!
* Metodo para verificar se o arquivo atual é um XML válido, para isso foi utilizado uma lógica com pilhas, 
* onde para descobrirmos se é um arquivo valido, basta olhar oque esta no topo da pilha e comparar.
* Além disso, neste método é realizado a extração das tags da string através do SUBSTR.
* \param filename Nome do arquivo que sera verificado o XML.
*/
bool validade_file (char *filename) {
    std::string line, tag, top;
    std::ifstream file(filename);
    structures::LinkedStack<std::string>stack{}; //!< Pilha para armazenamento das tags.
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
//! get_tags
/*!
* Esse metodo percorre todo o arquivo, e extrai as tags e os valores para armazenar em uma fila.
* \param filename Nome do arquivo que sera retirada as tags.
*/
void get_tags (char *filename) {
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
                    i = j + 1;
                } else {
                    j = i;
                    while (line[j] != '<' && j < line.size()) j++;
                    data = line.substr(i, j - i);
                    i = j;
                    if (data[0] != '\0') {
                        fila.enqueue(data);
                    }
                }
            }
        }
    }
}
//! get_datasets
/*!
* Percorre a fila de tags e valores armazenados, e atraves dele cria estruturas organizadas dos dados.
*/
void get_datasets() {
    std::string elemento;
    int i, j;
    struct Dataset *dataset;
    while (!fila.empty()) {
        dataset = new Dataset;
        while (true) {
            if (elemento == "<height>") dataset->height = stoi(fila.dequeue());
            else if (elemento == "<width>") dataset->width = stoi(fila.dequeue());
            else if (elemento == "<name>") dataset->name = fila.dequeue();
            else if (elemento == "<data>") {
                int **matrix = new int*[dataset->height];
                for (i = 0; i < dataset->height; i++) {
                    matrix[i] = new int[dataset->width];
                }
                for (i = 0; i < dataset->height; i++) {
                    elemento = fila.dequeue();
                    for (j = 0; j < dataset->width; j++) {
                        if (elemento[j]){
                            matrix[i][j] = (int)elemento[j] - 48;
                        }
                    }
                }
                dataset->data = matrix;
            }
            if (elemento == "</img>" || fila.empty()) break;
            elemento = fila.dequeue();
        }
        elemento = fila.dequeue();
        datasets.enqueue(dataset);
    }
}
//! flood_fill
/*!
* Aplicação do algoritmo de flood to fill, para realizar o preenchimento das áreas e organizar os dados para calculo
* dos pontos conexos.
* \param dataset , recebe um ponteiro para os dados organizados onde o mais importante é o atributo DATA.
* \param x recebe um inteiro
* \param y recebe um inteiro
*/
void flood_fill(struct Dataset *dataset, int x, int y) {
    if (dataset->data[x][y] == 1) {
        dataset->data[x][y] = 0;
    	if (x > 0) flood_fill(dataset, x - 1, y);
    	if (y > 0) flood_fill(dataset, x    , y - 1);
    	if (x < dataset->height - 1) flood_fill(dataset, x + 1, y);
    	if (y < dataset->width - 1) flood_fill(dataset, x    , y + 1);
    }
}
//! Display
/*!
* Metodo criado com intuito apenas de depuração e testes internos, similar ao toString() do java por exemplo.
* \param p , recebe um dataset especifico para ser mostrado
*/
void display(struct Dataset *p) {
    int i, j;
    for (i = 0; i < p->height; i++) {
        for (j = 0; j < p->width; j++) {
            std::cout << p->data[i][j] << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
//! get_conexes
/*!
* Metodo que da o retorno o numero de conexões totais no <data></data> respectivo, esta função tem uma dependencia total 
* do do flood_to_fill declarado anteriormente.
* \param *dataset , recebe um dataset especifico para dar o retorno do seu numero de conexões.
*/
int get_conexes(struct Dataset *dataset) {
	int i, j, conexes = 0;
	for (i = 0; i < dataset->height; i++) {
		for (j = 0; j < dataset->width; j++) {
			if (dataset->data[i][j] == 1) {
				conexes += 1;
				flood_fill(dataset, i, j);
			}
		}
	}
	return conexes;
}
//! Results
/*!
* Metodo criado com intuito apenas de depuração e testes internos, similar ao toString() do java por exemplo.
* \param p , recebe um dataset especifico para ser mostrado
*/
void results() {
    int i;
    struct Dataset *dataset;
    while (!datasets.empty()) {
        dataset = datasets.dequeue();
        std::cout << dataset->name << ' ';
        std::cout << get_conexes(dataset) << std::endl;
    }
}
