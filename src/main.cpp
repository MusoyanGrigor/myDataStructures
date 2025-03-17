#include <iostream>
#include <vector>
#include "../include/vector.h"

int main() {
    std::vector<float> stdVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const my::vector<float> myVec(std::move(stdVec));

    for(int i = 0; i < myVec.size(); ++i) {
        std::cout << myVec[i] << " ";
    }
    std::cout << std::endl;

    std::cout <<"size of stdVec: "<< stdVec.size() << std::endl;

    return 0;
}
