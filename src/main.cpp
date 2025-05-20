#include "vector.h"

int main() {
    my::vector<int> nums = {-1,2,1,-4};
    int x = 10;
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(x);
    for (int i = 0; i < nums.size(); ++i) {
        std::cout << nums[i] << std::endl;
    }
    return 0;
}
