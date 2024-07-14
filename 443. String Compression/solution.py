from typing import List

class Solution:
    def compress(self, chars: List[str]) -> int:
        def append_compressed_str(value, count):
            chars.append(value)
            if count >= 10:
                s = str(count)
                for si in s:
                    chars.append(si)
            elif count > 1:
                chars.append(str(count))
        
        n = len(chars)
        for i in range(n):
            c = chars.pop(0)
            if i == 0:
                v = c
                count = 1
            elif c == v:
                count += 1
            else:
                append_compressed_str(v, count)
                v = c
                count = 1
        append_compressed_str(v, count)

        return len(chars)