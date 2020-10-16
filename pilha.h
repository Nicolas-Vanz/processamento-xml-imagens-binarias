//Copyright [2020] <Leonardo Rocha & Nicolas Vanz>

#ifndef PILHA_H
#define PILHA_H

#include <stdexcept>

namespace structures {
//! LinkedStack
/*!
 * Classe que opera como uma pilha encadeada
 */
template<typename T>
class LinkedStack {
 public:
    //! Construtor
    LinkedStack();

    //! Destrutor
    ~LinkedStack();

    //! Limpar
    void clear();

    //! Empilhar
    void push(const T& data);

    //! Desempilhar
    T pop();

    //! Dado do topo
    T& top() const;

    //! Pilha vazia
    bool empty() const;

    //! Tamanho da pilha
    std::size_t size() const;

    //! Display
    void display();

 private:
	//! Node
 	/*!
 	 * Classe que representa um elemento da pilha
 	 */
    class Node {
     public:
		//! Contrutor
 		/*!
 		 * Cria um node especificando apenas seu dado
 		 */
        explicit Node(const T& data) {
            data_ = data;
        }

		//! Construtor
		/*!
		 * Cria um node especificando seu dado e próximo node
		 */
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

		//! Getter: data
		/*!
		 * Retorna o dado do node
		 */
        T& data() {
            return data_;
        }

		//! Getter: const data
		/*!
		 * Retorna o dado do node
		 */
        const T& data() const {
            return data_;
        }

		//! Getter: next
		/*!
		 * Retorna o próximo node
		 */
        Node* next() {
            return next_;
        }

		//! Getter: next const
		/*!
		 * Retorna o próximo node
		 */
        const Node* next() const {
            return next_;
        }

		//! Setter: next
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

    Node* top_;  //!< ponteiro para o topo da fila
    std::size_t size_;  //!< tamanho da pilha
};

}  // namespace structures
#endif

//! Contrutor
/*!
 * \brief Rotina construtora da pilha
 */
template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    size_ = 0;
    top_ = nullptr;
}

//! Destrutor
/*!
 * \brief Rotina destrutora da pilha
 */
template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

//! Limpar
/*!
 * \brief Remove todos os elementos da pilha
 */
template<typename T>
void structures::LinkedStack<T>::clear() {
    Node *p = top_, *q;
    while (p) {
        q = p;
        p = p->next();
        delete q;
    }
    size_ = 0;
    top_ = nullptr;
}

//! Empilhar
/*!
 * \brief Adiciona um elemento à pilha
 * \param data dado a ser empilhado
 * \note O dado é colocado no topo da pilha
 */
template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *t = new Node(data, top_);
    top_ = t;
    size_++;
}

//! Desmpilhar
/*!
 * \brief Retira um dado da pilha
 * \return Dado retirado da pilha
 * \note O dado é retirado do topo da pilha
 */
template<typename T>
T structures::LinkedStack<T>::pop() {
    if (empty()) throw std::out_of_range("lista vazia");
    Node *t = top_;
    T data = t->data();
    top_ = top_->next();
    delete t;
    size_--;
    return data;
}

//! Dado do topo
/*!
 * \brief Retorna o dado no topo da pilha
 */
template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) throw std::out_of_range("pilha vazia");
    return top_->data();
}

//! Pilha vazia
/*!
 * \brief Verifica se a pilha está vazia
 * \return true caso a pilha esteja vazia ou false caso não esteja vazia
 */
template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (!top_);
}

//! Tamanho da pilha
/*!
 * \brief Retorna a quantidade de elementos da pilha
 */
template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return (size_);
}

//! Display
/*!
 * \brief Imprime o conteúdo da pilha
 * Utilizado como recurso de debug
 */
template<typename T>
void structures::LinkedStack<T>::display() {
    Node *p = top_;
    while (p) {
        std::cout << p->data() << ' ';
        p = p->next();
    }
    std::cout << std::endl;
}
