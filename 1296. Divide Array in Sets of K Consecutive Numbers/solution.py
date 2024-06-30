from typing import List

class Solution:
    def isPossibleDivide(self, nums: List[int], k: int) -> bool:
        if k == 1:
            return True
        
        if len(nums) % k != 0:
            return False

        nums.sort()

        dic = {}
        for num in nums:
            if dic.get(num) is None:
                dic[num] = 1
            else:
                dic[num] += 1

        for num in nums:
            if dic[num] > 0:
                for i in range(num, num+k):
                    if dic.get(i) is None or dic[i] == 0:
                        return False
                    else:
                        dic[i] -= 1

        return True