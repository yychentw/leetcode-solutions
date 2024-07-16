class Solution:
    def closeStrings(self, word1: str, word2: str) -> bool:
        if len(word1) != len(word2):
            return False

        dic1 = {}
        for c1 in word1:
            if dic1.get(c1) is not None:
                dic1[c1] += 1
            else:
                dic1[c1] = 1

        dic2 = {}
        for c2 in word2:
            if dic2.get(c2) is not None:
                dic2[c2] += 1
            else:
                dic2[c2] = 1

        if len(dic1.keys()) != len(dic2.keys()):
            return False

        for k1 in dic1.keys():
            if dic2.get(k1) is None:
                return False

        vals1 = sorted(dic1.values())
        vals2 = sorted(dic2.values())
        for v1, v2 in zip(vals1, vals2):
            if v1 != v2:
                return False

        return True