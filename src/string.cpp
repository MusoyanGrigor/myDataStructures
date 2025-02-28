#include "string.h"
#include "utils.h"
#include <ostream>

namespace my {
    string::string() : m_data(nullptr) {}

    string::string(const char* str) {
        if (str) {
            m_length = utils::strlen(str);
            m_data = new char[m_length + 1];
            utils::strcpy(m_data, str);
        } else {
            m_data = nullptr;
            m_length = 0;
        }
    }

    string::string(const string& other) {
        m_length = other.m_length;
        m_data = new char[m_length + 1];
        utils::strcpy(m_data, other.m_data);
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

    std::ostream& operator<<(std::ostream& os, const string& str) {
        if (str.get_data()) {
            os << str.get_data();
        }
        return os;
    }
}
