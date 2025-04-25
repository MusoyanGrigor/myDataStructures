#include "../include/set.h"
#include <iostream>

int main() {
    my::set<int> s = {4, 3, 1, 2};

    for (int x : s) {
        std::cout << x << " ";
    }


    return 0;
}
