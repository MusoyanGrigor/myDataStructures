#ifndef LIST_H
#define LIST_H

#include <cstddef>
#include <stdexcept>
#include "node.h"

namespace my {

    template <typename T>
    class ListAllocator {
    public:
        static T* allocate(const std::size_t capacity) {
            return new T[capacity];
        }

        static void deallocate(const T* ptr) {
            delete[] ptr;
        }

        static Node<T>* allocateNode(const T& value) {
            return new Node<T>(value);
        }

        static void deallocateNode(const Node<T>* node) {
            delete node;
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

    template <typename T, typename Allocator = ListAllocator<T>>
    class list {
    public:
        list() : m_head(nullptr), m_tail(nullptr), m_size(0) {}

        list(std::initializer_list<T> init) : list() {
            for (const T& value : init) {
                push_back(value);
            }
        }

        list(const list& other) : list() {
            for (Node<T>* curr = other.m_head; curr; curr = curr->m_next) {
                push_back(curr->m_data);
            }
        }

        list(list&& other) noexcept
            : m_head(other.m_head), m_tail(other.m_tail), m_size(other.m_size) {
            other.m_head = other.m_tail = nullptr;
            other.m_size = 0;
        }

        list& operator=(const list& other) {
            if (this != &other) {
                clear();
                for (Node<T>* curr = other.m_head; curr; curr = curr->m_next) {
                    push_back(curr->m_data);
                }
            }
            return *this;
        }

        list& operator=(list&& other) noexcept {
            if (this != &other) {
                clear();
                m_head = other.m_head;
                m_tail = other.m_tail;
                m_size = other.m_size;

                other.m_head = other.m_tail = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        ~list() { clear(); }

        void push_back(const T& value) {
            auto* newNode = Allocator::allocateNode(value);
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
            auto* newNode = Allocator::allocateNode(value);
            if (!m_head) {
                m_head = m_tail = newNode;
            } else {
                newNode->m_next = m_head;
                m_head->m_prev = newNode;
                m_head = newNode;
            }
            ++m_size;
        }

        void pop_back() {
            if (!m_tail) return;
            Node<T>* temp = m_tail;
            m_tail = m_tail->m_prev;
            if (m_tail) m_tail->m_next = nullptr;
            else m_head = nullptr;
            Allocator::deallocateNode(temp);
            --m_size;
        }

        void pop_front() {
            if (!m_head) return;
            Node<T>* temp = m_head;
            m_head = m_head->m_next;
            if (m_head) m_head->m_prev = nullptr;
            else m_tail = nullptr;
            Allocator::deallocateNode(temp);
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
        [[nodiscard]] bool empty() const { return m_size == 0; }

        iterator<T> begin() { return iterator<T>(m_head); }
        iterator<T> end() { return iterator<T>(nullptr); }

    private:
        Node<T>* m_head;
        Node<T>* m_tail;
        size_t m_size;
    };

}

#endif // LIST_H
