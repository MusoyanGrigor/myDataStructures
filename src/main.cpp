#include <iostream>
#include "../include/list.h"
#include <list>


int main() {
    std::list<int> list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    my::list<int> vec = {1,2,3,4,5,6,7,8,9,10};
    for (const int & it : vec) {
        std::cout << it << std::endl;
    }

    return 0;
}
