#include <queue>
#include <string>

using namespace std;

class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> qd;
        queue<int> qr;
        int num_senators = senate.size();
        for (int i = 0; i < num_senators; ++i) {
            if (senate[i] == 'D') {
                qd.push(i);
            }
            else {
                qr.push(i);
            }
        }

        while (!qd.empty() && !qr.empty()) {
            int d = qd.front();
            int r = qr.front();

            qd.pop();
            qr.pop();

            if (d < r) {
                qd.push(d+num_senators);
            }
            else if (d > r) {
                qr.push(r+num_senators);
            }
        }

        if (!qd.empty()) {
            return "Dire";
        }
        else {
            return "Radiant";
        }
    }
};