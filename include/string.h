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
        string(size_t count,char ch);

        ~string();

        string& operator=(const string& str);
        string &operator=(string &&other) noexcept;
        const char &operator[](int index) const;
        [[nodiscard]] char at(size_t pos) const;
        [[nodiscard]] char& front() const;
        [[nodiscard]] char& back() const;

        [[nodiscard]] const char* get_data() const { return m_data;}
        [[nodiscard]] size_t length() const { return m_length; }
        [[nodiscard]] size_t size() const { return m_length; }
        [[nodiscard]] bool empty() const { return m_length == 0; }
        void clear();



    private:
        char *m_data;
        size_t m_length{};
    };

    std::ostream& operator<<(std::ostream& os, const string& str);
}

#endif // STRING_H
