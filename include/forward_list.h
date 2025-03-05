#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <iostream>
#include "node.h"

namespace my {
    template<typename T>
    class forward_list {
    public:
        forward_list() : m_head(nullptr) {};

        explicit forward_list(const size_t size) {
            for (size_t i = 0; i < size; ++i) {
                push_front(0);
            }
        }

        explicit forward_list(const size_t size, const T& value) {
            for (size_t i = 0; i < size; ++i) {
                push_front(value);
            }
        }

        forward_list(std::initializer_list<T> iList) {
            for (auto it = iList.begin(); it != iList.end(); ++it) {
                push_front(*it);
            }
        }

        forward_list(const forward_list& other) {
            for (size_t i = 0; i < other.size(); ++i) {
                push_front(other[i]);
            }
        }

        forward_list(forward_list&& other) noexcept {
            m_head = other.m_head;
            m_size = other.m_size;

            other.m_head = nullptr;
            other.m_size = 0;
        }

        forward_list& operator=(const forward_list& other) {
            if (this != &other) {
                clear();

                Node<T>* current = other.m_head;
                Node<T>** tail = &m_head;

                while (current) {
                    *tail = new Node<T>(current->m_value);
                    tail = &((*tail)->m_next);
                    current = current->m_next;
                }
                m_size = other.m_size;
            }
            return *this;
        }

        forward_list& operator=(forward_list&& other) noexcept {
            if (this != &other) {
                clear();
                m_head = other.m_head;
                m_size = other.m_size;

                other.m_head = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        forward_list& operator=(std::initializer_list<T> iList) {
            clear();
            for (auto it = iList.begin(); it != iList.end(); ++it) {
                push_back(*it);
            }
            return *this;
        }

        ~forward_list() {
            while (m_head) {
                pop_front();
            }
        }

        void push_front(T value) {
            auto *new_node = new Node<T>(value); // Create a new node with the given value
            new_node->m_next = m_head; // Set the new node's next to point to the current head
            m_head = new_node; // Update the head to point to the new node
            ++m_size;
        }

        void push_back(T value) {
            auto *newNode = new Node<T>(value);
            if (!m_head) {
                m_head = newNode;
                ++m_size;
                return;
            }

            Node<T> *temp = m_head;
            while (temp->m_next) {
                temp = temp->m_next;
            }

            temp->m_next = newNode;
            ++m_size;
        }

        void pop_front() {
            if (!m_head) return;
            const Node<T> *temp = m_head;
            m_head = m_head->m_next;
            delete temp;
            --m_size;
        }

        T& front() {
            if (!m_head) { // !nullptr is true
                throw std::out_of_range("Attempted to access front of an empty list");
            }
            return m_head->m_value;
        }

        const T& front() const {
            if (!m_head) {
                throw std::out_of_range("Attempted to access front of an empty list");
            }
            return m_head->m_value;
        }

        void clear() {
            while (m_head) {
                pop_front();
            }
        }

        [[nodiscard]] bool empty() const {
            return m_head == nullptr;
        }

        [[nodiscard]] size_t size() const {
            return m_size;
        }

        [[nodiscard]] size_t max_size() const {
            return m_size;
        }

    private:
        Node<T> *m_head;
        size_t m_size = 0;
    };
}

#endif //FORWARD_LIST_H
