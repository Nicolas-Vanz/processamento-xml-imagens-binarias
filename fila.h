// Copyright [2020] <Nicolas Vanz>
#include <stdexcept>
namespace structures {

//! LinkedQueue
template<typename T>
class LinkedQueue {
 public:
    //! construtor
    LinkedQueue();

    //! destrutor
    ~LinkedQueue();

    //! limpar
    void clear();

    //! enfileirar
    void enqueue(const T& data);

    //! desenfileirar
    T dequeue();

    //! primeiro dado
    T& front() const;

    //! último dado
    T& back() const;

    //! fila vazia
    bool empty() const;

    //! tamanho
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
    Node* head;  // nodo-cabeça
    Node* tail;  // nodo-fim
    std::size_t size_;  // tamanho
};

}  // namespace structures

//! LinkedQueue
template<typename T>
structures::LinkedQueue<T>::LinkedQueue() {
    head = nullptr;
    tail = nullptr;
    size_ = 0;
}

//! ~LinkedQueue
template<typename T>
structures::LinkedQueue<T>::~LinkedQueue() {
    clear();
}

//! clear
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

//! enqueue
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

//! dequeue
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

//! front
template<typename T>
T& structures::LinkedQueue<T>::front() const {
    if (empty()) throw std::out_of_range("fila vazia");
    return head->data();
}

//! back
template<typename T>
T& structures::LinkedQueue<T>::back() const {
    if (empty()) throw std::out_of_range("fila vazia");
    return tail->data();
}

//! empty
template<typename T>
bool structures::LinkedQueue<T>::empty() const {
    return (!head);
}

//! size
template<typename T>
std::size_t structures::LinkedQueue<T>::size() const {
    return size_;
}

//! display
template<typename T>
void structures::LinkedQueue<T>::display() {
    Node *p = head;
    while (p) {
        std::cout << p->data() << std::endl;
        p = p->next();
    }
}
