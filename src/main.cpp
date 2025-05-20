#include "vector.h"
#include "utils.h"


int main() {
    namespace umy = utils::my;
    my::vector<int> nums = {-1,2,1,-4};
    int x = 10;
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(x);


    my::vector<int> nums2 = umy::move(nums);
    for (const int num : nums2) {
        std::cout << num << std::endl;
    }
    return 0;
}
