#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>
#include <vector>
#include "iterator.h"

namespace my {

    template<typename T>
    class VectorAllocator {
    public:
        static T* allocate(const size_t capacity) {
            return new T[capacity];
        }

        static void deallocate(const T* ptr) {
            delete[] ptr;
        }

        static void copy(T* dest, const T* src, const size_t size) {
            for (size_t i = 0; i < size; ++i) {
                dest[i] = src[i];
            }
        }

        void move(T* dest, T* src, const size_t size) {
            for (size_t i = 0; i < size; ++i) {
                dest[i] = std::move(src[i]);
            }
        }
    };

    template<typename T, typename Allocator = VectorAllocator<T>>
    class vector {
    public:
        using iterator = my::iterator<T>;
        using const_iterator = my::iterator<const T>;

        vector() : m_size{0}, m_capacity{1}, m_allocator{} {
            m_buffer = m_allocator.allocate(m_capacity);
        }

        vector(const vector& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_allocator{} {
            m_buffer = m_allocator.allocate(m_capacity);
            m_allocator.copy(m_buffer, other.m_buffer, m_size);
        }

        vector(vector&& other) noexcept : m_size(other.m_size), m_capacity(other.m_capacity), m_allocator{} {
            m_buffer = other.m_buffer;
            other.m_buffer = nullptr;
            other.m_size = 0;
            other.m_capacity = 0;
        }

        explicit vector(const size_t size, const T& value) : m_size(size), m_capacity(size), m_allocator{} {
            m_buffer = m_allocator.allocate(m_capacity);
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = value;
            }
        }

        explicit vector(const size_t size) : m_size(size), m_capacity(size), m_allocator{} {
            m_buffer = m_allocator.allocate(m_capacity);
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = T{};
            }
        }

        vector(std::initializer_list<T> init) : m_size(init.size()), m_capacity(init.size()), m_allocator{} {
            m_buffer = m_allocator.allocate(m_capacity);
            size_t i = 0;
            for (const T& value : init) {
                m_buffer[i++] = value;
            }
        }

        vector& operator=(vector&& other) noexcept {
            if (this != &other) {
                m_allocator.deallocate(m_buffer);
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
            m_allocator.deallocate(m_buffer);
        }

        void reserve(const size_t newCapacity) noexcept {
            if (newCapacity < m_size) {
                throw std::invalid_argument("Capacity must be greater than or equal to size.");
            }
            T* newBuffer = m_allocator.allocate(newCapacity);
            m_allocator.copy(newBuffer, m_buffer, m_size);
            m_allocator.deallocate(m_buffer);
            m_buffer = newBuffer;
            m_capacity = newCapacity;
        }

        void resize(const size_t newCapSize) {
            const T& value = T{};
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
            m_buffer[m_size++] = value;
        }

        void push_back(T&& value) {
            if (m_size == m_capacity) {
                reserve(m_capacity * 2);
            }
            m_buffer[m_size++] = std::move(value);
        }

        T pop_back() {
            if (m_buffer != nullptr && m_size > 0) {
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
                throw std::out_of_range("Index out of bounds.");
            }
            return m_buffer[pos];
        }

        const T& operator[](const int index) const {
            return m_buffer[index];
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
            if (m_size == 0) {
                throw std::out_of_range("Empty vector.");
            }
            return m_buffer[0];
        }

        T& back() {
            if (m_size == 0) {
                throw std::out_of_range("Empty vector.");
            }
            return m_buffer[m_size - 1];
        }

        [[nodiscard]] T* data() {
            return m_buffer;
        }

        [[nodiscard]] const T* data() const {
            return m_buffer;
        }

        void assign(const size_t size, T& value) {
            resize(size);
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i] = value;
            }
        }

        void assign(const std::initializer_list<T> init) {
            resize(init.size());
            size_t i = 0;
            for (const T& value : init) {
                m_buffer[i++] = value;
            }
        }

        void clear() {
            for (size_t i = 0; i < m_size; ++i) {
                m_buffer[i].~T();
            }
            m_allocator.deallocate(m_buffer);
            m_buffer = nullptr;
            m_size = 0;
            m_capacity = 0;
        }

        void swap(vector& other) noexcept {
            std::swap(m_size, other.m_size);
            std::swap(m_capacity, other.m_capacity);
            std::swap(m_buffer, other.m_buffer);
        }

        std::vector<T> toStdVector() {
            std::vector<T> result(m_size);
            for (size_t i = 0; i < m_size; ++i) {
                result[i] = m_buffer[i];
            }
            return result;
        }

        iterator insert(iterator pos, const T& value) {
            size_t index = pos - begin();

            if (m_size == m_capacity) {
                reserve(m_capacity * 2);
            }

            for (size_t i = m_size; i > index; --i) {
                m_buffer[i] = std::move(m_buffer[i - 1]);
            }

            m_buffer[index] = value;
            ++m_size;

            return iterator(m_buffer + index);
        }


        iterator begin() {
            return iterator(m_buffer);
        }

        iterator end() {
            return iterator(m_buffer + m_size);
        }

    private:
        T* m_buffer;
        size_t m_size;
        size_t m_capacity;
        Allocator m_allocator;
    };

}

#endif // VECTOR_H
