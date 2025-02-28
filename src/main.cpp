#include <iostream>
#include "string.h"

int main() {
    my::string myString("Hello, World!");
    my::string myString2(std::move(myString));

    std::cout << myString2.length() << std::endl;

    return 0;
}
