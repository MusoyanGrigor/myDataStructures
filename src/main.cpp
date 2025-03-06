#include <iostream>
#include "deque.h"

int main() {

    my::deque<int> my_deque;

    my_deque.push_back(1);
    my_deque.push_back(2);
    my_deque.push_back(3);
    my_deque.push_back(4);
    my_deque.push_back(5);
    my_deque.push_front(6);
    my_deque.push_front(7);

    my_deque.pop_back();
    my_deque.pop_front();
    my_deque.pop_back();
    my_deque.pop_front();

    return 0;
}
