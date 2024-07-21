#include <cctype>
#include <stack>
#include <string>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        stack<string> st;
        string temp = "";
        for (char si: s) {
            if (isdigit(si)) {
                if (temp.empty() || !isdigit(temp[0])) {
                    st.push(temp);
                    temp = si;
                }
                else {
                    temp += si;
                }
            }
            else if (si == '[') {
                st.push(temp);
                temp = "";
            }
            else if (si == ']') {
                int k = stoi(st.top());
                st.pop();
                string decoded = "";
                for (int i = 0; i < k; ++i) {
                    decoded += temp;
                }
                temp = st.top() + decoded;
                st.pop();
            }
            else {  // English letters
                temp += si;
            }
        }
        return temp;
    }
};