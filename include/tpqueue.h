// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
  char ch;
  int prior;
  SYM(char c = '\0', int p = 0) : ch(c), prior(p) {}
};

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* nextElem;
        Node(const T& d, Node* n = nullptr) : data(d), nextElem(n) {}
    };

    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void push(const T& value) {
        Node* newNode = new Node(value);

        // Если очередь пуста или приоритет нового выше (чем у головы)
        if (!head || value.prior > head->data.prior) {
            newNode->nextElem = head;
            head = newNode;
            return;
        }

        // Иначе ищем подходящее место
        Node* current = head;
        while (current->nextElem && current->nextElem->data.prior >= value.prior) {
            current = current->nextElem;
        }

        newNode->nextElem = current->nextElem;
        current->nextElem = newNode;
    }

    T pop() {
        if (isEmpty()) {
            throw std::underflow_error("TPQueue is empty");
        }

        Node* temp = head;
        T result = head->data;
        head = head->nextElem;
        delete temp;
        return result;
    }

    const T& front() const {
        if (isEmpty()) {
            throw std::underflow_error("TPQueue is empty");
        }
        return head->data;
    }

    // (опционально) - очистка всей очереди
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    // (опционально) - для отладки
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data.ch << " (priority " << current->data.prior << ") -> ";
            current = current->nextElem;
        }
        std::cout << "NULL\n";
    }
};

#endif  // INCLUDE_TPQUEUE_H_
