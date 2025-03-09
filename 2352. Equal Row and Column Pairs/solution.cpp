#include <map>
#include <vector>
using namespace std;

class Solution {
public:
    int equalPairs(vector<vector<int>>& grid) {
        int n = grid.size();
        map<vector<int>, int> mp;
        for (int i = 0; i < n; i++) {
            mp[grid[i]]++;
        }

        int count = 0;
        for (int j = 0; j < n; j++) {
            vector<int> tmp(n, 0);
            for (int i = 0; i < n; i++) {
                tmp[i] = grid[i][j];
            }
            count += mp[tmp];
        }
        return count;
    }
};