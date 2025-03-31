#include <iostream>
#include "array.h"

int main() {
    my::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (const int & it : arr) {
        std::cout << it << std::endl;
    }

    const my::iterator<int>::value_type first_value = *arr.begin();
    std::cout << "First element: " << first_value << std::endl;

    return 0;
}
