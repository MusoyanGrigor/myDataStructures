#ifndef SWAP_H
#define SWAP_H

namespace my {
    template <typename T>
    void swap(T& a, T& b) noexcept {
        T temp = a;
        a = b;
        b = temp;
    }
}

#endif // SWAP_H
