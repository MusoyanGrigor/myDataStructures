#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include "node.h"

namespace my {
    template <typename T>
    class forward_list {
    public:
        forward_list() : m_head(nullptr) {};

        void push_front(T value) {
            Node<T> *new_node = new Node<T>(value);
            new_node->next = m_head;
            m_head = new_node;
        }

        void push_back(T value) {
            Node<T>* newNode = new Node<T>(value);
            if (!m_head) {
                m_head = newNode;
                return;
            }

            Node<T>* temp = m_head;
            while (temp->next)
                temp = temp->next;

            temp->next = newNode;
        }

        void pop_front() {
            if (!m_head) return;
            Node<T>* temp = m_head;
            m_head = m_head->next;
            delete temp;
        }

        ~forward_list() {
            while (m_head) {
               pop_front();
            }
        }


    private:
        Node<T> *m_head;
    };
}

#endif //FORWARD_LIST_H
