#ifndef PAIR_H
#define PAIR_H

namespace my {
    template <typename T1, typename T2>
    class pair {
        pair(const pair<T1, T2> &p) : first(p.first), second(p.second) {}

        auto operator<=>(const pair& other) const = default;

    private:
        T1 first;
        T2 second;
    };
}

#endif //PAIR_H
