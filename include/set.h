#ifndef SET_H
#define SET_H

#include <iostream>
#include <vector>
#include <algorithm>

namespace my {
template <typename K>
class set {
private:
    std::vector<K> data;

public:
    void insert(const K& value) {
        if (!contains(value)) {
            data.push_back(value);
            std::sort(data.begin(), data.end());
        }
    }

    void erase(const K& value) {
        auto it = std::find(data.begin(), data.end(), value);
        if (it != data.end()) {
            data.erase(it);
        }
    }

    bool contains(const K& value) const {
        return std::binary_search(data.begin(), data.end(), value);
    }

    void print() const {
        for (const K& val : data) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

}

#endif //SET_H
