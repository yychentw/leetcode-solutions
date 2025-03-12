#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    bool validTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> suffix_max(n, 0);

        suffix_max[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; i--) {
            suffix_max[i] = max(suffix_max[i+1], nums[i]);
        }

        int prefix_min = nums[i];
        for (int i = 1; i < n-1; i++) {
            if (nums[i] > prefix_min && nums[i] < suffix_max[i+1]) {
                return true;
            }
            prefix_min = min(prefix_min, nums[i]);
        }
        return false;
    }
};