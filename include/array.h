#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include "swap.h"

namespace my {
    template<typename T, std::size_t size>
    class array {
    public:
        array() = default;

        array(const array &) = default;

        array(array &&) = default;

        array(std::initializer_list<T> init) {
            if (init.size() > size) {
                throw std::out_of_range("initializer list size exceeds array size");
            }
            for (std::size_t i = 0; i < size; i++) {
                m_data[i] = init.begin()[i];
            }
        }

        [[nodiscard]] size_t length() const { return m_count; }

        T &at(std::size_t pos) {
            if (pos >= size) {
                throw std::out_of_range("array index out of range");
            }
            return m_data[pos];
        }

        T &operator[](std::size_t index) {
            return m_data[index];
        }

        bool operator==(const array &other) const {
                for (std::size_t i = 0; i < size; i++) {
                    if (m_data[i] != other.m_data[i]) {
                        return false;
                    }
                }

            return true;
        }

        bool operator!=(const array &other) const {
            for (std::size_t i = 0; i < size; i++) {
                if (m_data[i] != other.m_data[i]) {
                    return true;
                }
            }

            return false;
        }

        bool operator>(const array &other) const {
            for (std::size_t i = 0; i < size; i++) {
                if (m_data[i] < other.m_data[i]) {
                    return false;
                }
                if (m_data[i] > other.m_data[i]) {
                    return true;
                }
            }
            return false;
        }

        bool operator<(const array &other) const {
            for (std::size_t i = 0; i < size; i++) {
                if (m_data[i] < other.m_data[i]) {
                    return true;
                }
                if (m_data[i] > other.m_data[i]) {
                    return false;
                }
            }
            return false;
        }

        bool operator>=(const array &other) const {
            for (std::size_t i = 0; i < size; i++) {
                if (m_data[i] > other.m_data[i]) {
                    return true;
                }
                if (m_data[i] < other.m_data[i]) {
                    return false;
                }
            }
            return true;
        }

        bool operator<=(const array &other) const {
            for (std::size_t i = 0; i < size; i++) {
                if (m_data[i] > other.m_data[i]) {
                    return false;
                }
                if (m_data[i] < other.m_data[i]) {
                    return true;
                }
            }
            return true;
        }

        T &front() {
            return m_data[0];
        }

        T &back() {
            return m_data[size - 1];
        }

        T data() {
            return m_data;
        }

        void fill(const T &value) {
            for (std::size_t i = 0; i < size; ++i) {
                m_data[i] = value;
            }
        }

        void swap(T &other) {
            for (size_t i = 0; i < size; ++i) {
                my::swap(m_data[i], other.m_data[i]);
            }
        }

        [[nodiscard]] size_t max_size() const {
            return m_count;
        }

        [[nodiscard]] bool empty() const {
            return m_count == 0;
        }

    private:
        T m_data[size];
        size_t m_count = size;
    };
}

#endif //ARRAY_H
