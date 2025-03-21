#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include <algorithm>

namespace my {
    template<typename T, std::size_t Size>
    class ArrayAllocator {
    public:
        static T* allocate() {
            return new T[Size]{};
        }

        static void deallocate(const T* ptr) {
            delete[] ptr;
        }

        static void copy(T* dest, const T* src) {
            std::copy(src, src + Size, dest);
        }
    };

    template<typename T>
    class iterator {
    public:
        explicit iterator(T* ptr) : m_ptr(ptr) {}

        T& operator*() { return *m_ptr; }
        T* operator->() { return m_ptr; }

        iterator& operator++() { ++m_ptr; return *this; }
        iterator operator++(int) { iterator temp = *this; ++(*this); return temp; }

        iterator& operator--() { --m_ptr; return *this; }
        iterator operator--(int) { iterator temp = *this; --(*this); return temp; }

        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return m_ptr != other.m_ptr; }

    private:
        T* m_ptr;
    };

    template<typename T, std::size_t Size, typename Allocator = ArrayAllocator<T, Size>>
    class array {
    public:
        array() : m_data(Allocator::allocate()) {}

        array(const array& other) : m_data(Allocator::allocate()) {
            Allocator::copy(m_data, other.m_data);
        }

        array(array&& other) noexcept : m_data(other.m_data) {
            other.m_data = nullptr;
        }

        array(std::initializer_list<T> init) : m_data(Allocator::allocate()) {
            if (init.size() > Size) throw std::out_of_range("Initializer list size exceeds array size");
            std::copy(init.begin(), init.end(), m_data);
        }

        array& operator=(const array& other) {
            if (this != &other) {
                Allocator::copy(m_data, other.m_data);
            }
            return *this;
        }

        array& operator=(array&& other) noexcept {
            if (this != &other) {
                Allocator::deallocate(m_data);
                m_data = other.m_data;
                other.m_data = nullptr;
            }
            return *this;
        }

        ~array() { Allocator::deallocate(m_data); }

        [[nodiscard]] static size_t size()  { return Size; }
        [[nodiscard]] static bool empty() { return Size == 0; }
        [[nodiscard]] constexpr size_t size() const { return size(); }


        T& at(std::size_t pos) {
            if (pos >= Size) throw std::out_of_range("Index out of bounds");
            return m_data[pos];
        }

        T& operator[](std::size_t index) { return m_data[index]; }
        const T& operator[](std::size_t index) const { return m_data[index]; }

        T& front() { return m_data[0]; }
        T& back() { return m_data[Size - 1]; }

        T* data() { return m_data; }
        const T* data() const { return m_data; }

        void fill(const T& value) {
            std::fill(m_data, m_data + Size, value);
        }

        void swap(array& other) noexcept {
            std::swap(m_data, other.m_data);
        }

        bool operator==(const array& other) const { return std::equal(m_data, m_data + Size, other.m_data); }
        bool operator!=(const array& other) const { return !(*this == other); }
        bool operator<(const array& other) const { return std::lexicographical_compare(m_data, m_data + Size, other.m_data, other.m_data + Size); }
        bool operator>(const array& other) const { return other < *this; }
        bool operator<=(const array& other) const { return !(other < *this); }
        bool operator>=(const array& other) const { return !(*this < other); }

        iterator<T> begin() { return iterator<T>(m_data); }
        iterator<T> end() { return iterator<T>(m_data + Size); }

    private:
        T* m_data;
    };
}

#endif // ARRAY_H
