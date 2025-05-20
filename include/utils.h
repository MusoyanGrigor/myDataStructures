#ifndef UTILS_H
#define UTILS_H
#include <type_traits>

namespace utils {
    int strlen(const char* str);
    char* strcpy(char *dest, const char *src);

    namespace my {
        template <typename T>
        std::remove_reference_t<T>&& move(T&& value) {
            return static_cast<std::remove_reference_t<T>&&>(value);
        }
    }

}

#endif //UTILS_H
