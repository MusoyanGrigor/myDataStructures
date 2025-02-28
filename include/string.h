#ifndef STRING_H
#define STRING_H

#include <ostream>

namespace my {
    class string {
    public:
        string();
        explicit string(const char *);
        string(const string& other);
        string(string&& other) noexcept;
        ~string();

        string& operator=(const string& str);

        [[nodiscard]] const char* get_data() const { return m_data;}
        [[nodiscard]] int length() const { return m_length; }

    private:
        char *m_data;
        int m_length{};
    };

    std::ostream& operator<<(std::ostream& os, const string& str);
}

#endif // STRING_H
