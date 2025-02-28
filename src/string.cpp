#include "string.h"

#include <iostream>
#include "utils.h"


namespace my {
    string::string() {
        // default ctor
        m_data = new char[1];
        m_data[0] = '\0';
    }

    string::string(const char* str) {
        // param ctor
        if (str) {
            m_length = utils::strlen(str) + 1;
            m_data = new char[m_length];
            utils::strcpy(m_data, str);
            m_data[m_length - 1] = '\0';
        } else {
            m_data = nullptr;
            m_length = 0;
        }
    }

    string::string(const string& other) : m_length(other.m_length) {
        // copy ctor
        m_data = new char[m_length + 1];
        utils::strcpy(m_data, other.m_data);
    }

    string::string(string&& other) noexcept {
        // move ctor
        this->m_length = other.m_length;
        this->m_data = other.m_data;

        other.m_length = 1;
        other.m_data = new char[1];
        other.m_data[0] = '\0';
    }

    string::string(const size_t count, const char ch) : m_length(count) {
        std::cout << "string constructor called" << std::endl;
        m_data = new char[count + 1];
        for (size_t i = 0; i < count; ++i) {
            m_data[i] = ch;
        }

        m_data[count] = '\0';
    }


    string::~string() {
        delete[] m_data;
    }

    string& string::operator=(const string& str) {
        if (this != &str) {
            delete[] m_data;

            m_length = str.m_length;
            m_data = new char[m_length + 1];
            utils::strcpy(m_data, str.m_data);
        }

        return *this;
    }

    string& string::operator=(string&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_length = other.m_length;
            m_data = other.m_data;

            other.m_data = new char[1];
            other.m_length = 1;
            m_data[0] = '\0';
        }
        return *this;
    }

    const char& string::operator[](const int index) const {
        return m_data[index];
    }

    char string::at(size_t pos) const {
        if (pos >= m_length) {
            throw std::exception();
        }
        return m_data[pos];
    }

    char& string::front() const {
        if (m_data != nullptr) return m_data[0];
        throw std::out_of_range("Empty vector.");
    }

    char& string::back() const {
        if (m_data != nullptr) return m_data[m_length];
        throw std::out_of_range("Empty vector.");
    }

    void string::clear() {
        if (m_data != nullptr) {
            delete[] m_data;
            m_data = new char[1];
            m_length = 1;
            m_data[0] = '\0';
        }
    }

    std::ostream& operator<<(std::ostream& os, const string& str) {
        if (str.get_data()) {
            os << str.get_data();
        }
        return os;
    }
}
