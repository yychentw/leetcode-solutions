from typing import List

class Solution:
    def subarraysDivByK(self, nums: List[int], k: int) -> int:
        ans = 0
        prefix_sum = 0
        map = {0: 1}    # need to further add 1 to the count if prefix_mod == 0
        for n in nums: 
            prefix_sum += n
            prefix_mod = prefix_sum % k
            if map.get(prefix_mod) is not None:
                ans += map[prefix_mod]
                map[prefix_mod] += 1
            else:
                map[prefix_mod] = 1
        return ans