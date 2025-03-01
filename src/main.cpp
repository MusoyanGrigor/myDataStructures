#include "vector.h"

int main() {
    my::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vec.push_back(11);
    vec.push_back(12);
    vec.push_back(13);
    vec.push_back(14);
    vec.push_back(15);

    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();

    vec.print();


    return 0;
}
