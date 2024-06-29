from typing import List

class Solution:
    def sortColors(self, nums: List[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """
        i = 0
        end_pos = len(nums)
        while i < end_pos:
            if nums[i] == 0:
                nums.insert(0, nums[i])
                nums.pop(i+1)
            elif nums[i] == 2:
                nums.append(nums[i])
                nums.pop(i)
                end_pos -= 1
                i -= 1
            i += 1