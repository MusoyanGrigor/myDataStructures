#include "utils.h"

namespace utils {
    int strlen(const char* str)  {
        int length = 0;
        while (str[length] != '\0') {
            ++length;
        }
        return length;
    }


    char* strcpy(char *dest, const char *src)  {
        int i = 0;
        while (src[i] != '\0') {
            dest[i] = src[i];
            ++i;
        }
        dest[i] = '\0';
        return dest;
    }
}