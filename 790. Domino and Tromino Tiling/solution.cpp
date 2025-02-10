#include <vector>
using namespace std;

class Solution {
public:
    int numTilings(int n) {
        int m = 1000000007;

        if (n == 1) {
            return 1;
        }

        if (n == 2) {
            return 2;
        }

        vector<long> dp(n+1, 0);
        dp[0] = 1;
        dp[1] = 1;
        dp[2] = 2;

        vector<long> prefix_sum(n+1, 0);
        prefix_sum[0] = 1;
        prefix_sum[1] = 2;
        prefix_sum[2] = 4;

        for (int i = 3; i <= n; ++i) {
            dp[i] = dp[i-1] % m + dp[i-2] % m + 2 * prefix_sum[i-3] % m;
            prefix_sum[i] = prefix_sum[i-1] % m + dp[i] % m;
        }

        return (int)(dp[n]%m);
    }
};