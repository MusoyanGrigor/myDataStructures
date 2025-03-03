#include <iostream>
#include "vector.h"
#include "string.h"


int main() {
    my::vector<my::string> strVec;
    const my::string str("Hello World!");
    strVec.push_back(my::string("asdf"));

    for (int i = 0; i < strVec.size(); i++) {
        std::cout << strVec[i] << std::endl;
    }

    return 0;
}