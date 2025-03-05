#include <iostream>
#include "list.h"

int main() {

    my::list<int> original (5,10);
    my::list<int> movedList(std::move(original));


    const size_t size = movedList.size();
    for (size_t i = 0; i < size; i++) {
        std::cout << movedList.front() << std::endl;
        movedList.pop_front();
    }


    return 0;
}
