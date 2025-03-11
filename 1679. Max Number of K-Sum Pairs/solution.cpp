#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    int maxOperations(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        int max_ops = 0;
        for (int n: nums) {
            int c = k - n;
            if (umap[c] > 0) {
                max_ops++;
                umap[c]--;
                continue;
            }
            umap[n]++;
        }
        return max_ops;
    }
};