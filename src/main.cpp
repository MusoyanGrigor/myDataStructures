#include <iostream>
#include "map.h"

int main() {
    my::map<int,int> mymap;
    mymap.insert(5,4);
    mymap.insert(3,3);
    mymap.insert(2,2);
    mymap.insert(1,1);
    mymap.insert(0,0);
    mymap.insert(4,4);
    mymap.insert(6,6);
    mymap.insert(7,7);



    return 0;
}
