from typing import List

class Solution:
    def numberOfSubarrays(self, nums: List[int], k: int) -> int:
        count = 0
        prefix_odd_num = 0
        dic = {}
        for n in nums:
            if n % 2 == 1:
                prefix_odd_num += 1
            
            if prefix_odd_num == k:
                count += 1
            if (prefix_odd_num >= k) and (dic.get(prefix_odd_num-k) is not None):
                count += dic[prefix_odd_num-k]
            
            if dic.get(prefix_odd_num) is not None:
                dic[prefix_odd_num] += 1
            else:
                dic[prefix_odd_num] = 1

        return count