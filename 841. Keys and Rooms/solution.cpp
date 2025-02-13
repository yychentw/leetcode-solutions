#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        vector<int> visited(rooms.size(), 0);
        stack<int> keys;

        for (int k: rooms[0]) {
            keys.push(k);
        }
        visited[0] = 1;

        while (!keys.empty()) {
            int current_key = keys.top();
            keys.pop();
            if (visited[current_key] == 0) {
                for (int k: rooms[current_key]) {
                    keys.push(k);
                }
                visited[current_key] = 1;
            }
        }

        for (int v: visited) {
            if (v == 0) {
                return false;
            }
        }
        return true;
    }
};