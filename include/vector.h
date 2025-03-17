#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "swap.h"
#include <vector>

namespace my {
    template<typename T>
    class vector {

    public:
        vector() : m_size{0}, m_capacity{1} {
            //default ctor
            m_buffer = new T[m_capacity];
        }

        vector(const vector &other) : m_size(other.m_size), m_capacity(other.m_capacity) {
            //copy ctor
            m_buffer = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = other.m_buffer[i];
            }
        }

        vector(vector &&other) noexcept {
            //move ctor
            this->m_size = other.m_size;
            this->m_capacity = other.m_capacity;
            this->m_buffer = other.m_buffer;

            other.m_size = 0;
            other.m_capacity = 0;
            other.m_buffer = nullptr;
        }

        vector(const size_t size, const T& value) : m_buffer(new T[size]), m_size(size), m_capacity(size) {
            // param ctor 1
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = value;
            }
        }

        explicit vector(const size_t size) : m_size(size), m_capacity(size) {
            // param ctor 2
            m_buffer = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = T{};
            }
        }

        vector(std::initializer_list<T> init) : m_buffer(new T[init.size() * 2]), m_size(init.size()),m_capacity(init.size()) {
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = init.begin()[i];
            }
        }

        vector& operator=(vector&& other) noexcept {
            if (this != &other) {
                delete[] m_buffer;
                m_buffer = other.m_buffer;
                m_size = other.m_size;
                m_capacity = other.m_capacity;

                other.m_buffer = nullptr;
                other.m_size = 0;
                other.m_capacity = 0;
            }
            return *this;
        }

        ~vector() {
            delete[] m_buffer;
        }

        void reserve(const size_t newCapacity) noexcept {
            if (newCapacity < m_size) {
                throw std::invalid_argument("Capacity must be greater than or equal to size.");
            }

            T *newBuffer = new T[newCapacity];
            for (size_t i = 0; i < m_size; ++i) {
                newBuffer[i] = m_buffer[i];
            }

            delete[] m_buffer;
            m_buffer = newBuffer;
            m_capacity = newCapacity;
        }

        void resize(const size_t newCapSize) {
            const T &value = T{};
            if (newCapSize > m_capacity) {
                reserve(newCapSize);
            }

            if (newCapSize > m_size) {
                for (size_t i = m_size; i < newCapSize; ++i) {
                    m_buffer[i] = value;
                }
            }

            m_size = newCapSize;
        }

        void shrink_to_fit() {
            if (m_size == m_capacity) return;
            m_capacity = m_size;
        }

        void push_back(const T& value) {
            if (m_size == m_capacity) {
                reserve(m_capacity * 2);
            }
            if (m_buffer != nullptr) {
                m_buffer[m_size++] = value;
            }
        }

        void push_back(T&& value) {
            if (m_size == m_capacity) {
                reserve(m_capacity * 2);
            }
            m_buffer[m_size++] = std::move(value);
        }


        T pop_back() {
            if (m_buffer != nullptr) {
                return m_buffer[--m_size];
            }
            throw std::invalid_argument("Empty vector.");
        }

        [[nodiscard]] size_t size() const {
            return m_size;
        }

        [[nodiscard]] size_t capacity() const {
            return m_capacity;
        }

        [[nodiscard]] T at(size_t pos) const {
            if (pos >= m_size) {
                throw std::exception();
            }
            return m_buffer[pos];
        }

        const T &operator[](const int index) const {
            return m_buffer[index]; // like in standard vector
        }

        bool operator==(const vector<T>& other) const {
            return m_size == other.m_size;
        }

        bool operator!=(const vector<T>& other) const {
            return m_size != other.m_size;
        }

        bool operator<(const vector<T>& other) const {
            return m_size < other.m_size;
        }

        bool operator>(const vector<T>& other) const {
            return m_size > other.m_size;
        }

        bool operator<=(const vector<T>& other) const {
            return m_size <= other.m_size;
        }

        bool operator>=(const vector<T>& other) const {
            return m_size >= other.m_size;
        }

        [[nodiscard]] bool empty() const {
            return m_size == 0;
        }

        T& front() {
            if (m_buffer != nullptr) return m_buffer[0];
            throw std::out_of_range("Empty vector.");
        }

        T& back() {
            if (m_buffer != nullptr) return m_buffer[m_size - 1];
            throw std::out_of_range("Empty vector.");
        }

        [[nodiscard]] T *data() {
            return m_buffer;
        }

        [[nodiscard]] const T *data() const {
            return m_buffer;
        }

        void assign(const size_t size, T &value) {
            resize(size);
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = value;
            }
        }
        void assign(const std::initializer_list<T> init) {
            resize(init.size());
            size_t i = 0;
            for (const T &value : init) {
                m_buffer[i++] = value;
            }
        }

        void clear() {
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i].~T();
            }

            delete[] m_buffer;
            m_buffer = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        void swap(vector &other) noexcept {
            my::swap(m_size, other.m_size);
            my::swap(m_capacity, other.m_capacity);
            my::swap(m_buffer, other.m_buffer);
        }

        std::vector<T> toStdVector() {
          std::vector<T> result(m_size);
          for (size_t i = 0; i < m_size; ++i) {
              result[i] = m_buffer[i];
          }
            return result;
        }


    private:
        T *m_buffer;
        size_t m_size;
        size_t m_capacity;
    };
}

#endif // VECTOR_H
