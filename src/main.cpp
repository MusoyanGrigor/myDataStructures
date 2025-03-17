#include <iostream>
#include <vector>
#include "../include/vector.h"

int main() {
    my::vector<int> myVector;

    myVector.push_back(1);
    myVector.push_back(2);
    myVector.push_back(3);
    myVector.push_back(4);
    myVector.push_back(5);

    std::vector<int> stdVector = myVector.toStdVector(myVector);

    std::cout << "size of std vector: " <<stdVector.size() << std::endl;
    for (const int & it : stdVector) {
        std::cout << it << std::endl;
    }

    return 0;
}
