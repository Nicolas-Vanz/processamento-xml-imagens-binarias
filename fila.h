//Copyright [2020] <Leonardo Rocha & Nicolas Vanz>

#ifndef FILA_H
#define FILA_H

#include <stdexcept>

namespace structures {
/*!
* Classe que opera como uma fila encadeada
*/
template<typename T>
class LinkedQueue {
 public:
	/* Construtor */
	LinkedQueue();

	/* Destrutor */
	~LinkedQueue();

	/* Limpar */
	void clear();

	/* Enfileirar */
	void enqueue(const T& data);

	/* Desenfileirar */
	T dequeue();

	/* Primeiro dado */
	T& front() const;

	/* Último dado */
	T& back() const;

	/* Fila vazia */
	bool empty() const;

	/* Tamanho */
	std::size_t size() const;

	/* Display */
	void display();

 private:
	/*!
	* Classe que representa um elemento da fila
	*/
	class Node {
	 public:
		/* Contrutor */
		/*!
		* Cria um node especificando apenas seu dado
		*/
		explicit Node(const T& data) {
			data_ = data;
		}

		/* Construtor */
		/*!
		* Cria um node especificando seu dado e próximo node
		*/
		Node(const T& data, Node* next) {
			data_ = data;
			next_ = next;
		}

		/* Getter: data */
		/*!
		* Retorna o dado do node
		*/
		T& data() {
			return data_;
		}

		/* Getter: const data */
		/*!
		* Retorna o dado do node
		*/
		const T& data() const {
			return data_;
		}

		/* Getter: next */
		/*!
		* Retorna o próximo node
		*/
		Node* next() {
			return next_;
		}

		/* Getter: const next */
		/*!
		* Retorna o próximo node
		*/
		const Node* next() const {
			return next_;
		}

		/* Setter: next */
		/*!
		* Determina o próximo node
		*/
		void next(Node* next) {
			next_ = next;
		}

	 private:
		T data_;  //!< dado do node
		Node* next_;  //!< ponteiro para o próximo node
	};

	Node* head;  //!< ponteiro para o início da fila
	Node* tail;  //!< ponteiro para o final da fila
	std::size_t size_;  //!< tamanho da fila
};

}  // namespace structures
#endif

/*!
 * \brief Rotina construtora da fila
 */
template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
	head = nullptr;
	tail = nullptr;
	size_ = 0;
}

/*!
 * \brief Rotina destrutora da fila
 */
template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
	clear();
}

/*!
 * \brief Retira todos os elementos da fila
 */
template<typename T>
void structures::LinkedQueue<T>::clear() {
	Node *p = head, *q;
	while (p) {
		q = p;
		p = p->next();
		delete q;
	}
	head = nullptr;
	tail = nullptr;
	size_ = 0;
}

/*!
 * \brief Adiciona um elemento à fila
 * \param data dado tipo T a ser enfileirado
 * \note O novo elemento é adicionado no final da fila
 */
template<typename T>
void structures::LinkedQueue<T>::enqueue(const T& data) {
	Node *t = new Node(data, nullptr);
	if (empty()) {
		head = t;
		tail = t;
	} else {
		tail->next(t);
		tail = t;
	}
	size_++;
}

/*!
 * \brief Retira um elemento da fila
 * \return Dado removido da fila
 * \note O primeiro elemento da fila é o retirado
 */
template<typename T>
T structures::LinkedQueue<T>::dequeue() {
	if (empty()) throw std::out_of_range("fila vazia");
	Node *p = head;
	T t = p->data();
	head = head->next();
	delete p;
	size_--;
	return t;
}

/*!
 * \brief Retorna o primeiro dado da fila
 */
template<typename T>
T& structures::LinkedQueue<T>::front() const {
	if (empty()) throw std::out_of_range("fila vazia");
	return head->data();
}

/*!
 * \brief Retorna o último elemento da fila
 */
template<typename T>
T& structures::LinkedQueue<T>::back() const {
	if (empty()) throw std::out_of_range("fila vazia");
	return tail->data();
}

/*!
 * \brief Verifica se a fila está vazia
 * \return true caso a lista esteja vazia ou false caso não esteja vazia
 */
template<typename T>
bool structures::LinkedQueue<T>::empty() const {
	return (!head);
}

/*!
 * \brief Retorna a quantidade de elementos da fila
 */
template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
	return size_;
}

/*!
 * \brief Imprime o conteúdo da fila
 * \note Utilizado como recurso para debugar
 */
template<typename T>
void structures::LinkedQueue<T>::display() {
	Node *p = head;
	while (p) {
		std::cout << p->data() << std::endl;
		p = p->next();
	}
}
