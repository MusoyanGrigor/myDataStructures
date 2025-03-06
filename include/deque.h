#ifndef DEQUE_H
#define DEQUE_H

#include <cstddef>
#include "deque.h"
#include "node.h"

namespace my {
    template <typename T>
    class deque {
    public:
        deque() : m_front(nullptr), m_rear(nullptr) {};

        [[nodiscard]] bool isEmpty() const {
            return m_size == 0;
        }

        void push_front(const T& value) {
            auto* new_node = new Node<T>(value);
            if (isEmpty()) {
                m_front = m_rear = new_node;
            } else {
                new_node->m_next = m_front;
                m_front->m_prev = new_node;
                m_front = new_node;
            }
            m_size++;
        }

        void push_back(const T& value) {
            auto* new_node = new Node<T>(value);
            if (isEmpty()) {
                m_rear = m_front = new_node;
            } else {
                new_node->m_prev = m_rear;
                m_rear->m_next = new_node;
                m_rear = new_node;
            }
           m_size++;
        }

    private:
        Node<T>* m_front;
        Node<T> * m_rear;
        size_t m_size{};
    };
}

#endif //DEQUE_H
