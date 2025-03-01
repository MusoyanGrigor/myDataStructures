#include <iostream>
#include "vector.h"

int main() {
    const my::vector<bool> vec = {true, false, true};

    for (int i = 0; i < vec.size(); i++) {
       if (vec[i]) {
           std::cout << i << std::endl;
       }
    }


    return 0;
}
