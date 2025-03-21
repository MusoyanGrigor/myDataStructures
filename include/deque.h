#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>

namespace my {
    template<typename T>
    class DequeAllocator {
    public:
        static T* allocate(const size_t size) {
            return new T[size];
        }

        static void deallocate(T* ptr) {
            delete[] ptr;
        }
    };

    template<typename T>
    struct Node {
        T data;
        Node* prev;
        Node* next;

        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    template<typename T>
    class DequeIterator {
    public:
        explicit DequeIterator(Node<T>* ptr) : m_ptr(ptr) {}

        T& operator*() { return m_ptr->data; }
        T* operator->() { return &m_ptr->data; }

        DequeIterator& operator++() {
            if (m_ptr) m_ptr = m_ptr->next;
            return *this;
        }

        DequeIterator operator++(int) {
            DequeIterator temp = *this;
            ++(*this);
            return temp;
        }

        DequeIterator& operator--() {
            if (m_ptr) m_ptr = m_ptr->prev;
            return *this;
        }

        DequeIterator operator--(int) {
            DequeIterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const DequeIterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const DequeIterator& other) const { return m_ptr != other.m_ptr; }

    private:
        Node<T>* m_ptr;
    };

    template<typename T, typename Allocator = DequeAllocator<T>>
    class deque {
    public:
        deque() : m_front(nullptr), m_rear(nullptr), m_size(0) {}

        deque(std::initializer_list<T> init) : deque() {
            for (const T& value : init) {
                push_back(value);
            }
        }

        deque(const deque& other) : deque() {
            for (Node<T>* node = other.m_front; node != nullptr; node = node->next) {
                push_back(node->data);
            }
        }

        deque(deque&& other) noexcept : m_front(other.m_front), m_rear(other.m_rear), m_size(other.m_size) {
            other.m_front = other.m_rear = nullptr;
            other.m_size = 0;
        }

        deque& operator=(const deque& other) {
            if (this != &other) {
                clear();
                for (Node<T>* node = other.m_front; node != nullptr; node = node->next) {
                    push_back(node->data);
                }
            }
            return *this;
        }

        deque& operator=(deque&& other) noexcept {
            if (this != &other) {
                clear();
                m_front = other.m_front;
                m_rear = other.m_rear;
                m_size = other.m_size;
                other.m_front = other.m_rear = nullptr;
                other.m_size = 0;
            }
            return *this;
        }

        ~deque() {
            clear();
        }

        void push_front(const T& value) {
            Node<T>* new_node = new Node<T>(value);
            if (empty()) {
                m_front = m_rear = new_node;
            } else {
                new_node->next = m_front;
                m_front->prev = new_node;
                m_front = new_node;
            }
            ++m_size;
        }

        void push_back(const T& value) {
            Node<T>* new_node = new Node<T>(value);
            if (empty()) {
                m_front = m_rear = new_node;
            } else {
                new_node->prev = m_rear;
                m_rear->next = new_node;
                m_rear = new_node;
            }
            ++m_size;
        }

        void pop_front() {
            if (empty()) {
                throw std::underflow_error("Deque is empty!");
            }
            Node<T>* temp = m_front;
            m_front = m_front->next;
            if (m_front) m_front->prev = nullptr;
            else m_rear = nullptr;
            delete temp;
            --m_size;
        }

        void pop_back() {
            if (empty()) {
                throw std::underflow_error("Deque is empty!");
            }
            Node<T>* temp = m_rear;
            m_rear = m_rear->prev;
            if (m_rear) m_rear->next = nullptr;
            else m_front = nullptr;
            delete temp;
            --m_size;
        }

        [[nodiscard]] T& front() const {
            if (empty()) throw std::underflow_error("Deque is empty!");
            return m_front->data;
        }

        [[nodiscard]] T& back() const {
            if (empty()) throw std::underflow_error("Deque is empty!");
            return m_rear->data;
        }

        [[nodiscard]] bool empty() const {
            return m_size == 0;
        }

        [[nodiscard]] size_t size() const {
            return m_size;
        }

        T& operator[](size_t index) {
            if (index >= m_size) throw std::out_of_range("Index out of bounds.");
            Node<T>* current = traverse(index);
            return current->data;
        }

        [[nodiscard]] T& at(size_t pos) {
            return (*this)[pos];
        }

        void clear() {
            while (!empty()) {
                pop_front();
            }
        }

        void swap(deque& other) noexcept {
            std::swap(m_front, other.m_front);
            std::swap(m_rear, other.m_rear);
            std::swap(m_size, other.m_size);
        }

        bool operator==(const deque<T>& other) const {
            if (m_size != other.m_size) return false;
            Node<T>* a = m_front;
            Node<T>* b = other.m_front;
            while (a && b) {
                if (a->data != b->data) return false;
                a = a->next;
                b = b->next;
            }
            return true;
        }

        bool operator!=(const deque<T>& other) const {
            return !(*this == other);
        }

        bool operator<(const deque<T>& other) const {
            return m_size < other.m_size;
        }

        bool operator>(const deque<T>& other) const {
            return m_size > other.m_size;
        }

        bool operator<=(const deque<T>& other) const {
            return m_size <= other.m_size;
        }

        bool operator>=(const deque<T>& other) const {
            return m_size >= other.m_size;
        }

        DequeIterator<T> begin() {
            return DequeIterator<T>(m_front);
        }

        DequeIterator<T> end() {
            return DequeIterator<T>(nullptr);
        }

    private:
        Node<T>* m_front;
        Node<T>* m_rear;
        size_t m_size;

        Node<T>* traverse(size_t index) {
            Node<T>* current = (index < m_size / 2) ? m_front : m_rear;
            if (index < m_size / 2) {
                for (size_t i = 0; i < index; ++i) {
                    current = current->next;
                }
            } else {
                for (size_t i = m_size - 1; i > index; --i) {
                    current = current->prev;
                }
            }
            return current;
        }
    };

}

#endif // DEQUE_H
