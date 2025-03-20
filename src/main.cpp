#include <iostream>
#include "../include/vector.h"

int main() {
    for (my::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; const int & it : vec) {
        std::cout << it << std::endl;
    }

    return 0;
}
