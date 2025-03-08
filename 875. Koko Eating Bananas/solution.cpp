#include <vector>
using namespace std;

class Solution {
    public:
        int minEatingSpeed(vector<int>& piles, int h) {
            int max_num_bananas = 0;
            for (int num: piles) {
                if (num > max_num_bananas) {
                    max_num_bananas = num;
                }
            }
    
            int left = 1;
            int right = max_num_bananas;
            while (left <= right) {
                int mid  = left + (right-left)/2;
                long required_h = 0;
                for (int num: piles) {
                    required_h += ceil((double)num/mid);
                }
    
                if (required_h > h) {
                    left = mid + 1;
                }
                else if (required_h <= h) {
                    right = mid - 1;
                }
            }
            return left;
        }
    };