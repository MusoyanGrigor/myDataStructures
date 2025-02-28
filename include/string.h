#ifndef STRING_H
#define STRING_H

namespace my {
    class string {
    public:
        string();
        explicit string(const char *);
        ~string();

    private:
        char *m_data;
        int m_length{};
    };
}
#endif //STRING_H
