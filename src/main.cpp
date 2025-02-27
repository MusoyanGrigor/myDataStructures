#include "../include/vector.h"

int main() {

    my::vector<int> vec(5, 10);
    my::vector<int> vec2(7, 20);

    vec.swap(vec2);
    vec.print();

    return 0;
}
