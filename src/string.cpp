#include "string.h"
#include "utils.h"


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



    string::~string() {
        delete[] m_data;
    }


}
