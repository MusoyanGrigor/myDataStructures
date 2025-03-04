#include <iostream>
#include "array.h"

int main() {
    const my::array<int, 3> arr1 = {1, 2, 3};
    const my::array<int, 3> arr2 = {1, 2, 3};
    const my::array<int, 3> arr3 = {3, 2, 1};
    const my::array<int, 3> arr4 = {2, 3, 4};
    const my::array<int, 3> arr5 = {1, 2, 3};

    std::cout << "arr1 > arr2: " << (arr1 > arr2 ? "true" : "false") << std::endl;
    std::cout << "arr1 >= arr3: " << (arr1 >= arr3 ? "true" : "false") << std::endl;
    std::cout << "arr1 <= arr4: " << (arr1 <= arr4 ? "true" : "false") << std::endl;
    std::cout << "arr4 < arr1: " << (arr4 < arr1 ? "true" : "false") << std::endl;
    std::cout << "arr1 == arr5: " << (arr1 == arr5 ? "true" : "false") << std::endl;

    return 0;
}
