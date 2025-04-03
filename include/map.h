#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "pair.h"

namespace my {
    template <typename K, typename V>
    class map {



    private:
        my::vector<my::pair<K, V>> data;

        int findIndex(const K& key) const {
            int left = 0;
            int right = data.size() - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                if (data[mid].first == key) return mid;
                if (data[mid].first < key)
                    left = mid + 1;
                else
                    right = mid - 1;
            }
            return -1;
        }
    };

}

#endif //MAP_H
