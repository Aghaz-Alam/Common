Category 1: Frequency / HashMap Based (6 Questions)

input: "aabbcc"
output: true
(All character frequencies unique)

input: "aabbccc"
output: false
(Frequencies: a=2, b=2, c=3 → duplicate)

input: "abcabc"
output: true
(Frequencies: a=2, b=2, c=2 → duplicate → false?) Actually output: false

input: "aabbc"
output: true
(Frequencies: a=2, b=2, c=1 → all frequencies unique?) → careful: 2 appears twice → false

input: "abcd"
output: true
(All characters appear once)

input: "aabbbcccc"
output: true
(Frequencies: a=2, b=3, c=4 → all unique)
















Category 2: Palindrome / Reverse (5 Questions)

input: "racecar"
output: true

input: "hello"
output: false

input: "abba"
output: true

input: "abcba"
output: true

input: "abcd"
output: false















Category 3: Anagram / Permutations (5 Questions)

input: "listen", "silent"
output: true

input: "triangle", "integral"
output: true

input: "apple", "papel"
output: true

input: "rat", "car"
output: false

input: "aabb", "bbaa"
output: true















Category 4: Rearrange / Pattern / Swap (5 Questions)

input: "aabbcc"
output: "abcabc"
(Rearrange so no two adjacent characters are the same)

input: "aaabb"
output: "ababa"
(Rearranged to avoid adjacent same letters)

input: "aaab"
output: ""
(Impossible to rearrange)

input: "abcde"
output: "edcba"
(Reverse string)

input: "hello world"
output: "world hello"
(Reverse words in sentence)




















Category 5: Sliding Window / Substrings / Unique Characters (5 Questions)

input: "abcabcbb"
output: 3
(Length of longest substring without repeating characters)

input: "bbbbb"
output: 1

input: "pwwkew"
output: 3

input: "dvdf"
output: 3

input: "abcdef"
output: 6












Category 6: String Matching / Count (4 Questions)

input: "hello world", "lo"
output: 1
(Count of substring "lo")

input: "ababab", "ab"
output: 3

input: "aaaa", "aa"
output: 3
(Overlapping allowed)

input: "abcdef", "gh"
output: 0


















Category 7: Miscellaneous / Tricky (5 Questions)

input: "aabcc", k=2
output: true
(Can reorganize string so same characters are at least distance k apart)

input: "aaabc", k=3
output: false

input: "abcabc"
output: "acbacb"
(Reorder string in alternate pattern)

input: "abcd"
output: "dcba"
(Reverse string)

input: "mississippi"
output: {'i':4,'s':4,'m':1,'p':2}
(Frequency map of characters)