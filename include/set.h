#ifndef SET_H
#define SET_H

#include <iostream>
#include "vector.h"
#include <algorithm>

namespace my {
template <typename K>
class set {
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

    private:
    my::vector<K> data;

    int findIndex(const K& key) const {
        int left = 0;
        int right = m_data.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (m_data[mid].first == key) return mid;
            if (m_data[mid].first < key)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }
};

}

#endif //SET_H
