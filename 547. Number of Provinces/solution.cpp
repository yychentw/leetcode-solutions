#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution {
    public:
        int findCircleNum(vector<vector<int>>& isConnected) {
            stack<int> st;
            unordered_set<int> visited;
            int n = isConnected.size();
            int ans = 0;
            for (int i = 0; i < n; ++i) {
                if (visited.find(i) != visited.end()) {
                    continue;
                }
    
                visited.insert(i);
                st.push(i);
                ++ans;
                while (!st.empty()) {
                    int current = st.top();
                    st.pop();
                    for (int j = 0; j < n; ++j) {
                        if (isConnected[current][j] == 1 && visited.find(j) == visited.end()) {
                            visited.insert(j);
                            st.push(j);
                        }
                    }
                }
            }
            return ans;
        }
    };