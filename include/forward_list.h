#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include "node.h"

namespace my {

    template <typename T>
    class ForwardListAllocator {
    public:
        static T* allocate(const std::size_t capacity) {
            return new T[capacity];
        }

        static void deallocate(const T* ptr) {
            delete[] ptr;
        }
    };

    template <typename T>
    class iterator {
    public:
        explicit iterator(Node<T>* node) : m_current(node) {}

        T& operator*() { return m_current->m_data; }
        iterator& operator++() {
            if (m_current) m_current = m_current->m_next;
            return *this;
        }
        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        bool operator==(const iterator& other) const { return m_current == other.m_current; }
        bool operator!=(const iterator& other) const { return m_current != other.m_current; }

    private:
        Node<T>* m_current;
    };

    template <typename T, typename Allocator = ForwardListAllocator<T>>
    class forward_list {
    public:
        forward_list() : m_head(nullptr), m_size(0) {}

        explicit forward_list(std::size_t size, const T& value = T{}) : forward_list() {
            for (std::size_t i = 0; i < size; ++i) {
                push_front(value);
            }
        }

        forward_list(std::initializer_list<T> init) : forward_list() {
            for (auto it = init.end(); it != init.begin();) {
                push_front(*--it);
            }
        }

        forward_list(const forward_list& other) : forward_list() {
            for (Node<T>* curr = other.m_head; curr; curr = curr->m_next) {
                push_back(curr->m_data);
            }
        }

        forward_list(forward_list&& other) noexcept : m_head(other.m_head), m_size(other.m_size) {
            other.m_head = nullptr;
            other.m_size = 0;
        }

        forward_list& operator=(const forward_list& other) {
            if (this != &other) {
                clear();
                for (Node<T>* curr = other.m_head; curr; curr = curr->m_next) {
                    push_back(curr->m_data);
                }
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

        ~forward_list() { clear(); }

        void push_front(const T& value) {
            auto* newNode = new Node<T>(value);
            newNode->m_next = m_head;
            m_head = newNode;
            ++m_size;
        }

        void push_back(const T& value) {
            auto* newNode = new Node<T>(value);
            if (!m_head) {
                m_head = newNode;
            } else {
                Node<T>* temp = m_head;
                while (temp->m_next) {
                    temp = temp->m_next;
                }
                temp->m_next = newNode;
            }
            ++m_size;
        }

        void pop_front() {
            if (!m_head) return;
            Node<T>* temp = m_head;
            m_head = m_head->m_next;
            delete temp;
            --m_size;
        }

        T& front() {
            if (!m_head) throw std::out_of_range("List is empty");
            return m_head->m_data;
        }

        const T& front() const {
            if (!m_head) throw std::out_of_range("List is empty");
            return m_head->m_data;
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        [[nodiscard]] bool empty() const { return m_size == 0; }
        [[nodiscard]] std::size_t size() const { return m_size; }

        iterator<T> begin() { return iterator<T>(m_head); }
        iterator<T> end() { return iterator<T>(nullptr); }

    private:
        Node<T>* m_head;
        std::size_t m_size;
    };

}

#endif // FORWARD_LIST_H
