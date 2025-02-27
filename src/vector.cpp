#include "vector.h"
#include "swap.h"

namespace my {

    // Constructors
    template<typename T>
    vector<T>::vector() : m_size{0}, m_capacity{1} {
        m_buffer = new T[m_capacity];
    }

    template<typename T>
    vector<T>::vector(const vector &other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        m_buffer = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i] = other.m_buffer[i];
        }
    }

    template<typename T>
    vector<T>::vector(vector &&other) noexcept {
        this->m_size = other.m_size;
        this->m_capacity = other.m_capacity;
        this->m_buffer = other.m_buffer;

        other.m_size = 0;
        other.m_capacity = 0;
        other.m_buffer = nullptr;
    }

    template<typename T>
    vector<T>::vector(const size_t size, const T &value) : m_buffer(new T[size]), m_size(size), m_capacity(size) {
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i] = value;
        }
    }

    template<typename T>
    vector<T>::vector(const size_t size) : m_size(size), m_capacity(size) {
        m_buffer = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i] = T{};
        }
    }

    template<typename T>
    vector<T>::vector(std::initializer_list<T> init) : m_buffer(new T[init.size() * 2]), m_size(init.size()), m_capacity(init.size() * 2) {
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i] = init.begin()[i];
        }
    }

    // Destructor
    template<typename T>
    vector<T>::~vector() {
        delete[] m_buffer;
    }

    // Methods
    template<typename T>
    void vector<T>::reserve(const size_t newCapacity) noexcept {
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

    template<typename T>
    void vector<T>::resize(const size_t newCapSize) {
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

    template<typename T>
    void vector<T>::shrink_to_fit() {
        if (m_size == m_capacity) return;
        m_capacity = m_size;
    }

    template<typename T>
    void vector<T>::push_back(const T& value) {
        if (m_size == m_capacity) {
            reserve(m_capacity * 2);
        }
        m_buffer[m_size++] = value;
    }

    template<typename T>
    void vector<T>::push_back(T&& value) {
        if (m_size == m_capacity) {
            reserve(m_capacity * 2);
        }
        m_buffer[m_size++] = std::move(value);
    }

    template<typename T>
    T vector<T>::pop_back() {
        if (m_buffer != nullptr) {
            return m_buffer[--m_size];
        }
        throw std::invalid_argument("Empty vector.");
    }

    template<typename T>
    size_t vector<T>::size() const {
        return m_size;
    }

    template<typename T>
    size_t vector<T>::capacity() const {
        return m_capacity;
    }

    template<typename T>
    T vector<T>::at(size_t pos) const {
        if (pos >= m_size) {
            throw std::out_of_range("Index out of range");
        }
        return m_buffer[pos];
    }

    template<typename T>
    const T& vector<T>::operator[](const int index) const {
        return m_buffer[index];
    }

    template<typename T>
    bool vector<T>::operator==(const vector<T>& other) const {
        return m_size == other.m_size;
    }

    template<typename T>
    bool vector<T>::operator!=(const vector<T>& other) const {
        return m_size != other.m_size;
    }

    template<typename T>
    bool vector<T>::operator<(const vector<T>& other) const {
        return m_size < other.m_size;
    }

    template<typename T>
    bool vector<T>::operator>(const vector<T>& other) const {
        return m_size > other.m_size;
    }

    template<typename T>
    bool vector<T>::operator<=(const vector<T>& other) const {
        return m_size <= other.m_size;
    }

    template<typename T>
    bool vector<T>::operator>=(const vector<T>& other) const {
        return m_size >= other.m_size;
    }

    template<typename T>
    bool vector<T>::empty() const {
        return m_size == 0;
    }

    template<typename T>
    T& vector<T>::front() {
        if (m_buffer != nullptr) return m_buffer[0];
        throw std::out_of_range("Empty vector.");
    }

    template<typename T>
    T& vector<T>::back() {
        if (m_buffer != nullptr) return m_buffer[m_size - 1];
        throw std::out_of_range("Empty vector.");
    }

    template<typename T>
    T* vector<T>::data() {
        return m_buffer;
    }

    template<typename T>
    const T* vector<T>::data() const {
        return m_buffer;
    }

    template<typename T>
    void vector<T>::assign(const size_t size, T& value) {
        resize(size);
        for (size_t i = 0; i < m_size; ++i) {
            m_buffer[i] = value;
        }
    }

    template<typename T>
    void vector<T>::assign(const std::initializer_list<T> init) {
        resize(init.size());
        size_t i = 0;
        for (const T& value : init) {
            m_buffer[i++] = value;
        }
    }

    template<typename T>
    void vector<T>::clear() {
        m_buffer = nullptr;
        m_size = 0;
        m_capacity = 0;
    }

    template<typename T>
    void vector<T>::swap(vector &other) noexcept {
        using std::swap;
        my::swap(m_size, other.m_size);
        my::swap(m_capacity, other.m_capacity);
        my::swap(m_buffer, other.m_buffer);
    }

    template<typename T>
    void vector<T>::print(const std::string& sym) {
        if (m_buffer != nullptr) {
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << m_buffer[i] << sym;
            }
        }
    }

}

template class my::vector<int>;
template class my::vector<double>;
template class my::vector<float>;
template class my::vector<std::string>;