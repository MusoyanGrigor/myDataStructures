#include <iostream>
#include <array.h>


int main() {
    my::array<int, 3> arr = {1, 2, 3};

    for (int i = 0; i < 3; i++) {
        std::cout << arr[i] << std::endl;
    }

    std::cout <<"array size: "<<arr.max_size()<< std::endl;


    return 0;
}