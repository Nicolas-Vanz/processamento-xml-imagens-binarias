//Copyright [2020] <Leonardo Rocha & Nicolas Vanz>

#include <iostream>
#include <fstream>
#include <string>
#include "pilha.h"
#include "fila.h"

//! Dataset
/*!
 * Representa uma imagem descrita no arquivo xml.
 */
struct Dataset {
    std::string name; //!< Nome de imagem
    int height; //!< Altura da imagem
    int width; //!< Largura da imagem
    int **data; //!< matriz de 0 e 1 da imagem
};

//! \defgroup grupo1 estruturas de dados
/**@{*/
structures::LinkedQueue<std::string>
fila{}; //!< Fila usada para armazenar todas as linhas do arquivo

structures::LinkedQueue<struct Dataset*>
datasets{}; //!< Fila de todas as imagens organizadas em datasets

structures::LinkedStack<std::string>
stack{}; //!< Pilha para armazenamento das tags na validação do arquivo.
/**@}*/

/*!
 * \brief Verifica se uma tag é de abertura ou de fechamento
 *
 * \param tag tag a ser analisada
 *
 * \return true caso a tag seja de abertura ou
 * false caso a tag seja de fechamento
 */
bool is_open_tag(std::string tag) {
	if (tag[1] == '/') return false;
	return true;
}

/*!
 * \brief Verifica se o arquivo é válido
 *
 * \param filename Nome do arquivo que sera analisado
 *
 * \return true caso o arquivo seja válido ou
 * false caso o arquivo não seja válido
 *
 * \note Uma estrutura de pilha é utilizada para a validação
 */
bool validate_file (char *filename) {
	std::string line, tag, top;
	std::ifstream file(filename);
	int i, j;

	/* Abre o arquivo */
	if (file.is_open()) {

		/* Le cada linha do arquivo */
		while (getline (file, line)) {

			/* Lê cada caractere da linha */
			for (i = 0; i < line.size(); i++) {

				/* Verifica se o caractere indica uma tag */
				if (line[i] == '<') {
					j = i;
					while (line[j] != '>') j++;

					/* Obtém a tag */
					tag = line.substr(i, j - i + 1);

					if (!is_open_tag(tag)) {  /* É uma tag de fechamento */
						/* Analisa a validade da tag
						(se ela faz sentido no contexto do arquivo) */

						/* Se a pilha está vazia significa
						que uma tag não foi aberta */
						if (stack.empty()) return false;

						/* Verifica se a tag fecha a
						tag de abertura correspondente */
						top = stack.pop();
						if (top.substr(1, top.size() - 2) !=
							tag.substr(2, tag.size() - 3))
							return false;

					} else {  /* É uma tag de abertura */
						/* empilha a tag*/
						stack.push(tag);
					}
				}
			}
		}

		/* Se sobrar tags na pilha significa que alguma tag não foi fechada */
		if (!stack.empty()) return false;
		file.close();
		return true;
	}
	return false;
}

/*!
 * \brief Extrai cada elemento do arquivo
 * Percorre todo o arquivo e extrai as tags e seus valores
 *
 * \param filename Nome do arquivo de onde serão retiradas as tags.
 *
 * \note Uma fila é utilizada para armazenar cada elemento (tag ou valor da tag)
 * \note Essa rotina só é chamada depois do arquivo
 * ser validado por validate_file()
 *
 * \see validate_file()
 */
void get_tags (char *filename) {
	std::string tag, data, line;
	std::ifstream file(filename);
	int i, j;

	/* Abre o arquivo */
	if (file.is_open()) {

		/* Lê cada linha do arquivo */
		while (getline (file, line)) {
			i = j = 0;

			/* Percorre cada caractere da linha */
			while (i < line.size()) {
				if (line[i] == '<') {  /* Indica o início de uma tag */
					j = i;

					/* Obtém a tag */
					while (line[j] != '>') j++;
					tag = line.substr(i, j - i + 1);

					/* Adiciona a tag à fila */
					fila.enqueue(tag);
					i = j + 1;

				} else {  /* Indica o início do valor se alguma tag */
					j = i;

					/* Obtém o dado da tag */
					while (line[j] != '<' && j < line.size()) j++;
					data = line.substr(i, j - i);
					i = j;

					/* adiciona o dado à fila */
					if (data[0] != '\0') {
						fila.enqueue(data);
					}
				}
			}
		}
	}
}

/*!
 * \brief Organiza as tags e seus valores em conjuntos de dados
 *
 * \note É utilizada uma fila para armazenar os conjuntos de dados (datasets)
 * \note Essa função só é chamada depois que as tags
 * e seus valores foram processados por get_tags()
 *
 * \see get_tags()
 */
void get_datasets() {
	std::string elemento;
	int i, j;
	struct Dataset *dataset;

	/* Percorre cada elemento da fila de tags e dados */
	while (!fila.empty()) {

		/* Cria um novo conjunto de dados */
		dataset = new Dataset;

		/* Obtém os dados dos conjuntos */
		while (true) {

			/* Obtém a altura da imagem */
			if (elemento == "<height>")
				dataset->height = stoi(fila.dequeue());

			/* Obtém a largura da imagem */
			else if (elemento == "<width>")
				dataset->width = stoi(fila.dequeue());

			/* Obtém o nome da imagem */
			else if (elemento == "<name>")
				dataset->name = fila.dequeue();

			/* Obtém a matriz de 0 e 1 */
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

		/* Adiciona o novo dadaset à fila */
		datasets.enqueue(dataset);
	}
}

/*!
 * \brief Preenche um componente conexo da matriz
 *
 * Percorre todos os elementos iguais a 1
 * adjacentes à coordenada (x, y)
 *
 * \param dataset Ponteiro para o conjunto de dados a ser analisado
 * \param x Linha da matriz a ser analisada
 * \param y Coluna da matriz a ser analisada
 *
 * \note Essa função usa um meio recursivo para preencher o componente
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

/*!
 * \brief Imprime todos os dados de um dataset
 * \note Utilizado como ferramenta para debugar
 *
 * \param p Ponteiro do dataset a ser mostrado
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

/*!
 * \brief Retorna a quantidade de componentes conexos da imagem
 *
 * \param dataset Ponteiro do dataset a ser analisado
 *
 * \return Quantidade de componentes conexos da imagem representada pelo dataset
 *
 * \note É chamado um algoritmo recursivo para
 * o preenchimento do componente conexo
 *
 * \see flood_fill()
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

/*!
 * \brief Imprime os resultados dos cálculos de cada conjunto de dados
 */
void results() {
    int i;
    struct Dataset *dataset;
	/* Percorre a fila de conjunto de dados */
    while (!datasets.empty()) {
		/* retira um conjunto de dados para análise */
        dataset = datasets.dequeue();
        std::cout << dataset->name << ' ';
		/* Calcula a quanidade de pontos conexos */
        std::cout << get_conexes(dataset) << std::endl;
    }
}
