#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "pair.h"

namespace my {
    template <typename K, typename V>
    class map {
    public:
      void insert(const K& key, const V& value) {
        int index = findIndex(key);
        if (index != -1) {
          m_data[index].second = value;
        } else {
            int pos = 0;
            while (pos < m_data.size() && m_data[pos].first < key) {
              ++pos;
               m_data.insert(pos, my::pair<K, V>(key, value));
            }
        }
      }


    private:
        my::vector<my::pair<K, V>> m_data;

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

#endif //MAP_H
