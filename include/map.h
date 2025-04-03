#ifndef MAP_H
#define MAP_H

#include "vector.h"
#include "pair.h"

namespace my {
    template <typename K, typename V>
    class map {



    private:
        my::vector<my::pair<K, V>> data;
    };

}

#endif //MAP_H
