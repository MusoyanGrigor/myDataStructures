#include "list.h"
int main() {


    my::list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    list1.push_front(5);
    list1.push_back(6);
    list1.push_back(7);

    list1.pop_front();
    list1.pop_back();
    list1.pop_back();
    list1.pop_front();


    return 0;
}
