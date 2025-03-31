#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

namespace my {
    template<typename T>
    class iterator {
    public:
        using reference_type = T&;
        using pointer_type = T*;

        explicit iterator(T* ptr) : m_ptr(ptr) {}

        reference_type operator*() { return *m_ptr; }

        pointer_type operator->() { return m_ptr; }

        iterator& operator++() {
            ++m_ptr;
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        iterator& operator--() {
            --m_ptr;
            return *this;
        }

        iterator operator--(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }

        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return m_ptr != other.m_ptr; }
        bool operator<(const iterator& other) const { return m_ptr < other.m_ptr; }
        bool operator>(const iterator& other) const { return m_ptr > other.m_ptr; }

        iterator operator+(size_t n) const { return iterator(m_ptr + n); }
        iterator operator-(size_t n) const { return iterator(m_ptr - n); }
        size_t operator-(const iterator& other) const { return m_ptr - other.m_ptr; }

    private:
        T* m_ptr;
     };
}

#endif //ITERATOR_H
