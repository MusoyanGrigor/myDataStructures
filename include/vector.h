#ifndef VECTOR_H
#define VECTOR_H

#include <initializer_list>
#include <iostream>

namespace my {

    template<typename T>
    class vector {
    public:
        // Constructors
        vector();
        vector(const vector &other);
        vector(vector &&other) noexcept;
        vector(const size_t size, const T &value);
        explicit vector(const size_t size);
        vector(std::initializer_list<T> init);

        // Destructor
        ~vector();

        // Methods
        void reserve(const size_t newCapacity) noexcept;
        void resize(const size_t newCapSize);
        void shrink_to_fit();
        void push_back(const T& value);
        void push_back(T&& value);
        T pop_back();
        [[nodiscard]] size_t size() const;
        [[nodiscard]] size_t capacity() const;
        [[nodiscard]] T at(size_t pos) const;
        const T &operator[](const int index) const;
        bool operator==(const vector<T>& other) const;
        bool operator!=(const vector<T>& other) const;
        bool operator<(const vector<T>& other) const;
        bool operator>(const vector<T>& other) const;
        bool operator<=(const vector<T>& other) const;
        bool operator>=(const vector<T>& other) const;
        [[nodiscard]] bool empty() const;
        T& front();
        T& back();
        [[nodiscard]] T *data();
        [[nodiscard]] const T *data() const;
        void assign(const size_t size, T &value);
        void assign(const std::initializer_list<T> init);
        void clear();
        void swap(vector &other) noexcept;
        void print(const std::string& sym = "\n");

    private:
        T *m_buffer;
        size_t m_size;
        size_t m_capacity;
    };
}

#endif // VECTOR_H
