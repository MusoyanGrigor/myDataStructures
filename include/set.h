#ifndef SET_H
#define SET_H

#include <iostream>
#include <algorithm>
#include "vector.h"

namespace my {

template <typename K>
class set {
public:
    using iterator = typename my::vector<K>::iterator;

    void insert(const K& value) {
        auto it = std::lower_bound(data.begin(), data.end(), value);
        if (it == data.end() || *it != value) {
            data.insert(it, value);
        }
    }

    void erase(const K& value) {
        auto it = std::lower_bound(data.begin(), data.end(), value);
        if (it != data.end() && *it == value) {
            data.erase(it);
        }
    }

    bool contains(const K& value) const {
        return std::binary_search(data.begin(), data.end(), value);
    }

    std::size_t size() const {
        return data.size();
    }

    bool empty() const {
        return data.empty();
    }

    void clear() {
        data.clear();
    }

private:
    my::vector<K> data;
};

}

#endif // SET_H
