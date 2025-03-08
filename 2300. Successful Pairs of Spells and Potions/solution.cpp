#include <algorithm>
#include <vector>
using namespace std;

class Solution {
    public:
        vector<int> uccessfulPairs(vector<int>& spells, vector<int>& potions, long long success) {
            vector<int> answer(spells.size(), 0);
            sort(potions.begin(), potions.end());
            for (int i = 0; i < spells.size(); i++) {
                int left = 0;
                int right = potions.size() - 1;
                long long target = (success+spells[i]-1)/spells[i];
                while (left <= right) {
                    int mid = left + (right-left)/2;
                    if (potions[mid] < target) {
                        left = mid + 1;
                    }
                    else if (potions[mid] >= target) {
                        right = mid - 1;
                    }
                }
                answer[i] = potions.size() - left;
            }
            return answer;
        }
    };