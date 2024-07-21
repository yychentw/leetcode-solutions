#include <vector>

using namespace std;

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> ans;
        
        for (int asteroid: asteroids) {
            bool alive = true;
            while (!ans.empty() && asteroid < 0 && ans.back() > 0) {
                if (ans.back() < -asteroid) {
                    ans.pop_back();
                    continue;
                } else if (ans.back() == -asteroid) {
                    ans.pop_back();
                }
                alive = false;
                break;
            }
            if (alive) {
                ans.push_back(asteroid);
            }
        }
        
        return ans;
    }
};