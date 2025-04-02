#ifndef PAIR_H
#define PAIR_H

#include <iostream>

namespace my {
    template <typename T1, typename T2>
    class pair {
        pair(const pair<T1, T2> &p) : first(p.first), second(p.second) {}

        auto operator<=>(const pair& other) const = default;

        void print() const {
            std::cout << "(" << first << ", " << second << ")\n";
        }

    private:
        T1 first;
        T2 second;
    };
}

#endif //PAIR_H
