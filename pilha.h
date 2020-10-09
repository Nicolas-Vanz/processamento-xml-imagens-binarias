// Copyright [2020] <Nicolas Vanz>
#ifndef PILHA_H
#define PILHA_H

#include <stdexcept>

namespace structures {

//! LinkedStack
template<typename T>
class LinkedStack {
 public:
    //! construtor
    LinkedStack();

    //! destrutor
    ~LinkedStack();

    //! limpa pilha
    void clear();

    //! empilha
    void push(const T& data);

    //! desempilha
    T pop();

    //! dado do topo
    T& top() const;

    //! pilha vazia
    bool empty() const;

    //! tamanho da pilha
    std::size_t size() const;

    //! display
    void display();

 private:
    //! node/elemento
    class Node {
     public:
        //! construtor via data
        explicit Node(const T& data) {
            data_ = data;
        }

        //! contrutor via data +  next
        Node(const T& data, Node* next) {
            data_ = data;
            next_ = next;
        }

        //! getter: data
        T& data() {
            return data_;
        }

        //! getter: const data
        const T& data() const {
            return data_;
        }

        //! getter: next
        Node* next() {
            return next_;
        }

        //! getter: next const
        const Node* next() const {
            return next_;
        }

        //! setter: next
        void next(Node* next) {
            next_ = next;
        }

     private:
        T data_;
        Node* next_;
    };

    Node* top_;  // nodo-topo
    std::size_t size_;  // tamanho
};

}  // namespace structures

template<typename T>
structures::LinkedStack<T>::LinkedStack() {
    size_ = 0;
    top_ = nullptr;
}

template<typename T>
structures::LinkedStack<T>::~LinkedStack() {
    clear();
}

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

template<typename T>
void structures::LinkedStack<T>::push(const T& data) {
    Node *t = new Node(data, top_);
    top_ = t;
    size_++;
}

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

template<typename T>
T& structures::LinkedStack<T>::top() const {
    if (empty()) throw std::out_of_range("pilha vazia");
    return top_->data();
}

template<typename T>
bool structures::LinkedStack<T>::empty() const {
    return (!top_);
}

template<typename T>
std::size_t structures::LinkedStack<T>::size() const {
    return (size_);
}
#endif

template<typename T>
void structures::LinkedStack<T>::display() {
    Node *p = top_;
    while (p) {
        std::cout << p->data() << ' ';
        p = p->next();
    }
    std::cout << std::endl;
}
