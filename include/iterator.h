#ifndef ITERATOR_H
#define ITERATOR_H

#include <iterator>

namespace my {
    template<typename T>
    class iterator {
    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        explicit iterator(T* ptr) : m_ptr(ptr) {}

        // Dereference
        reference operator*() const { return *m_ptr; }
        pointer operator->() const { return m_ptr; }

        // Increment / Decrement
        iterator& operator++() { ++m_ptr; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        iterator& operator--() { --m_ptr; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }

        // Arithmetic
        iterator operator+(difference_type n) const { return iterator(m_ptr + n); }
        iterator operator-(difference_type n) const { return iterator(m_ptr - n); }
        difference_type operator-(const iterator& other) const { return m_ptr - other.m_ptr; }

        iterator& operator+=(difference_type n) { m_ptr += n; return *this; }
        iterator& operator-=(difference_type n) { m_ptr -= n; return *this; }

        reference operator[](difference_type n) const { return *(m_ptr + n); }

        // Comparison
        bool operator==(const iterator& other) const { return m_ptr == other.m_ptr; }
        bool operator!=(const iterator& other) const { return m_ptr != other.m_ptr; }
        bool operator<(const iterator& other) const { return m_ptr < other.m_ptr; }
        bool operator>(const iterator& other) const { return m_ptr > other.m_ptr; }
        bool operator<=(const iterator& other) const { return m_ptr <= other.m_ptr; }
        bool operator>=(const iterator& other) const { return m_ptr >= other.m_ptr; }

    private:
        T* m_ptr;
    };
}

#endif // ITERATOR_H
