#include <string>
using namespace std;

class Solution {
public:
    string reverseWords(string s) {
        string ans = "";
        string tmp = "";
        for (char si: s) {
            if (si != ' ') {
                tmp += si;
            }
            else if (!tmp.empty()) {
                ans = tmp + " " + ans;
                tmp = "";
            }
        }
        if (!tmp.empty()) {
            ans = tmp + " " + ans;
        }
        ans.erase(ans.end()-1);
        return ans;
    }
};