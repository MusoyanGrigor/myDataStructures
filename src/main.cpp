#include <iostream>
#include "forward_list.h"

int main() {
    my::forward_list<int> mylist;
    mylist.push_front(1);
    mylist.push_front(2);
    mylist.push_front(3);
    mylist.push_front(4);
    mylist.push_front(5);

    mylist.clear();

    return 0;
}
