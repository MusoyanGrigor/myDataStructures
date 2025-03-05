#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include "node.h"

namespace my {
    template<typename T>
    class list {
    public:
        list() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

        list(const size_t size, const T& value) : m_head(nullptr), m_tail(nullptr), m_size(0) {
            for (size_t i = 0; i < size; ++i) {
                push_back(value);
            }
        }

        list(const list& other) : m_head(nullptr), m_tail(nullptr), m_size(0) {
            for (size_t i = 0; i < other.size(); ++i) {
                push_back(other[i]);
            }
        }

        list(list&& other) noexcept {
            this->m_head = other.m_head;
            this->m_tail = other.m_tail;
            this->m_size = other.m_size;


            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
        }

        ~list() { clear(); }

        void push_back(const T& value) {
            auto* newNode = new Node<T>(value);
            if (!m_head) {
                m_head = m_tail = newNode;
            } else {
                m_tail->m_next = newNode;
                newNode->m_prev = m_tail;
                m_tail = newNode;
            }
            m_size++;
        }

        void push_front(const T& value) {
            auto* newNode = new Node<T>(value);
            if (!m_head) {
                m_head = m_tail = newNode;
            } else {
                newNode->m_next = m_head;
                m_head->m_prev = newNode;
                m_head = newNode;
            }
            m_size++;
        }

        void pop_back() {
            if (!m_tail) return;
            Node<T>* temp = m_tail;
            m_tail = m_tail->m_prev;
            if (m_tail) m_tail->m_next = nullptr;
            else m_head = nullptr;
            delete temp;
            m_size--;
        }

        void pop_front() {
            if (!m_head) return;
            Node<T>* temp = m_head;
            m_head = m_head->m_next;
            if (m_head) m_head->m_prev = nullptr;
            else m_tail = nullptr;
            delete temp;
            m_size--;
        }

        T& front() {
            if (!m_head) throw std::out_of_range("List is empty");
            return m_head->m_data;
        }

        const T& front() const {
            if (!m_head) throw std::out_of_range("List is empty");
            return m_head->m_data;
        }

        T& back() {
            if (!m_tail) throw std::out_of_range("List is empty");
            return m_tail->m_data;
        }

        const T& back() const {
            if (!m_tail) throw std::out_of_range("List is empty");
            return m_tail->m_data;
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        [[nodiscard]] size_t size() const { return m_size; }
        [[nodiscard]]  size_t max_size() const {return m_size; }
        [[nodiscard]] bool empty() const { return m_size == 0; }

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
        size_t m_size;
    };
}

#endif // LIST_H
