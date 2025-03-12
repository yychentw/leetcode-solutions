#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    bool validTriplet(vector<int>& nums) {
        int n = nums.size();
        vector<int> prefix_min(n, 0);
        vector<int> suffix_max(n, 0);

        prefix_min[0] = nums[0];
        for (int i = 1; i < n; i++) {
            prefix_min[i] = min(prefix_min[i-1], nums[i]);
        }

        suffix_max[n-1] = nums[n-1];
        for (int i = n-2; i >= 0; i--) {
            suffix_max[i] = max(suffix_max[i+1], nums[i]);
        }

        for (int i = 1; i < n-1; i++) {
            if (nums[i] > prefix_min[i-1] && nums[i] < suffix_max[i+1]) {
                return true;
            }
        }
        return false;
    }
};