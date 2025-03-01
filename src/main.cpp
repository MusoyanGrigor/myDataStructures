#include <iostream>
#include "vector.h"
#include "string.h"

int main() {
    const my::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << std::endl;
    }

    return 0;
}
