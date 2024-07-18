#include <string>

using namespace std;

class Solution {
public:
    string removeStars(string s) {
        string ans = "";
        for (char si: s) {
            if (si == '*') {
                ans.pop_back();
                continue;
            }
            ans.push_back(si);
        }
        return ans;
    }
};