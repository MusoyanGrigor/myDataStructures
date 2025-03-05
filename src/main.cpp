#include <iostream>
#include "list.h"

int main() {

    my::list<int> list1;
    list1.push_front(1);
    list1.push_front(2);
    list1.push_front(3);
    list1.push_front(4);

    const size_t size = list1.size();
    for (size_t i = 0; i < size; i++) {
        std::cout<< list1.front() << std::endl;
        list1.pop_front();
    }

    return 0;
}
