1️⃣ Count frequency using dictionary
def main():
    nums = [1, 2, 2, 3, 3, 3]
    freq = {}
    for n in nums:
        freq[n] = freq.get(n, 0) + 1
    print(freq)

if __name__ == "__main__":
    main()

"""
Output
{1: 1, 2: 2, 3: 3}
"""






2️⃣ Reverse dictionary (values → keys)
def main():
    d = {'a': 1, 'b': 2, 'c': 3}
    rev = {v: k for k, v in d.items()}
    print(rev)

if __name__ == "__main__":
    main()

"""
Output
{1: 'a', 2: 'b', 3: 'c'}
"""






3️⃣ List comprehension – even squares
def main():
    result = [x*x for x in range(1, 11) if x % 2 == 0]
    print(result)

if __name__ == "__main__":
    main()

"""
Output
[4, 16, 36, 64, 100]
"""







4️⃣ Dictionary comprehension
def main():
    squares = {x: x*x for x in range(1, 6)}
    print(squares)

if __name__ == "__main__":
    main()

"""
Output
{1: 1, 2: 4, 3: 9, 4: 16, 5: 25}
"""






5️⃣ Remove duplicates while preserving order
def main():
    nums = [1, 2, 2, 3, 1, 4]
    result = list(dict.fromkeys(nums))
    print(result)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3, 4]
"""






6️⃣ Use enumerate to find index
def main():
    items = ["a", "b", "c"]
    for i, v in enumerate(items):
        print(i, v)

if __name__ == "__main__":
    main()

"""
Output
0 a
1 b
2 c
"""





7️⃣ Zip two lists into dictionary
def main():
    keys = ["name", "age"]
    values = ["Alice", 25]
    d = dict(zip(keys, values))
    print(d)

if __name__ == "__main__":
    main()

"""
Output
{'name': 'Alice', 'age': 25}
"""




8️⃣ map(): Convert strings to int
def main():
    s = ["1", "2", "3"]
    nums = list(map(int, s))
    print(nums)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3]
"""





9️⃣ filter(): Words longer than 3 chars
def main():
    words = ["hi", "hello", "cat", "python"]
    result = list(filter(lambda x: len(x) > 3, words))
    print(result)

if __name__ == "__main__":
    main()

"""
Output
['hello', 'python']
"""





🔟 reduce(): Product of list
from functools import reduce

def main():
    nums = [1, 2, 3, 4]
    product = reduce(lambda a, b: a * b, nums)
    print(product)

if __name__ == "__main__":
    main()

"""
Output
24
"""





11️⃣ Shallow copy behavior
def main():
    a = [[1, 2], [3, 4]]
    b = a.copy()
    b[0].append(99)
    print(a)
    print(b)

if __name__ == "__main__":
    main()

"""
Output
[[1, 2, 99], [3, 4]]
[[1, 2, 99], [3, 4]]
"""




12️⃣ Deep copy behavior
import copy

def main():
    a = [[1, 2], [3, 4]]
    b = copy.deepcopy(a)
    b[0].append(99)
    print(a)
    print(b)

if __name__ == "__main__":
    main()

"""
Output
[[1, 2], [3, 4]]
[[1, 2, 99], [3, 4]]
"""






13️⃣ Exception handling
def main():
    try:
        x = int("abc")
    except ValueError:
        print("Conversion error")

if __name__ == "__main__":
    main()

"""
Output
Conversion error
"""





14️⃣ File write & read using with
def main():
    with open("test.txt", "w") as f:
        f.write("Hello")

    with open("test.txt", "r") as f:
        print(f.read())

if __name__ == "__main__":
    main()

"""
Output
Hello
"""




15️⃣ Generator function
def gen_numbers():
    for i in range(3):
        yield i

def main():
    for x in gen_numbers():
        print(x)

if __name__ == "__main__":
    main()

"""
Output
0
1
2
"""





16️⃣ Iterator using iter()
def main():
    nums = [1, 2, 3]
    it = iter(nums)
    print(next(it))
    print(next(it))

if __name__ == "__main__":
    main()

"""
Output
1
2
"""





17️⃣ *args usage
def add(*args):
    return sum(args)

def main():
    print(add(1, 2, 3))

if __name__ == "__main__":
    main()

"""
Output
6
"""




18️⃣ **kwargs usage
def show(**kwargs):
    print(kwargs)

def main():
    show(name="Alice", age=30)

if __name__ == "__main__":
    main()

"""
Output
{'name': 'Alice', 'age': 30}
"""






19️⃣ Lambda sorting
def main():
    pairs = [(1, 3), (2, 1), (4, 2)]
    pairs.sort(key=lambda x: x[1])
    print(pairs)

if __name__ == "__main__":
    main()

"""
Output
[(2, 1), (4, 2), (1, 3)]
"""




20️⃣ Set operations
def main():
    a = {1, 2, 3}
    b = {3, 4, 5}
    print(a & b)
    print(a | b)

if __name__ == "__main__":
    main()

"""
Output
{3}
{1, 2, 3, 4, 5}
"""




21️⃣ Mutable default argument trap
def add_item(item, lst=[]):
    lst.append(item)
    return lst

def main():
    print(add_item(1))
    print(add_item(2))

if __name__ == "__main__":
    main()


"""
Output
[1]
[1, 2]
"""




22️⃣ Fix mutable default argument
def add_item(item, lst=None):
    if lst is None:
        lst = []
    lst.append(item)
    return lst

def main():
    print(add_item(1))
    print(add_item(2))

if __name__ == "__main__":
    main()


"""
Output
[1]
[2]
"""


23️⃣ String frequency
def main():
    s = "banana"
    freq = {}
    for ch in s:
        freq[ch] = freq.get(ch, 0) + 1
    print(freq)

if __name__ == "__main__":
    main()


"""
Output
{'b': 1, 'a': 3, 'n': 2}
"""



24️⃣ Palindrome check
def main():
    s = "madam"
    print(s == s[::-1])

if __name__ == "__main__":
    main()


"""
Output
True
"""





25️⃣ List flattening
def main():
    lst = [[1, 2], [3, 4]]
    flat = [x for sub in lst for x in sub]
    print(flat)

if __name__ == "__main__":
    main()


"""
Output
[1, 2, 3, 4]
"""






5️⃣1️⃣ Find common elements using set
def main():
    a = [1, 2, 3, 4]
    b = [3, 4, 5, 6]
    common = list(set(a) & set(b))
    print(common)

if __name__ == "__main__":
    main()

"""
Output
[3, 4]
"""






5️⃣2️⃣ Remove keys with None values
def main():
    d = {'a': 1, 'b': None, 'c': 3}
    result = {k: v for k, v in d.items() if v is not None}
    print(result)

if __name__ == "__main__":
    main()

"""
Output
{'a': 1, 'c': 3}
"""






5️⃣3️⃣ Count vowels in a string
def main():
    s = "python programming"
    vowels = "aeiou"
    count = sum(1 for ch in s if ch in vowels)
    print(count)

if __name__ == "__main__":
    main()

"""
Output
4
"""






5️⃣4️⃣ Swap keys and values (duplicates allowed)
def main():
    d = {'a': 1, 'b': 1, 'c': 2}
    result = {}
    for k, v in d.items():
        result.setdefault(v, []).append(k)
    print(result)

if __name__ == "__main__":
    main()

"""
Output
{1: ['a', 'b'], 2: ['c']}
"""







5️⃣5️⃣ Sort dictionary by value
def main():
    d = {'a': 3, 'b': 1, 'c': 2}
    result = dict(sorted(d.items(), key=lambda x: x[1]))
    print(result)

if __name__ == "__main__":
    main()

"""
Output
{'b': 1, 'c': 2, 'a': 3}
"""





5️⃣6️⃣ Check all elements are unique
def main():
    nums = [1, 2, 3, 4]
    print(len(nums) == len(set(nums)))

if __name__ == "__main__":
    main()

"""
Output
True
"""







5️⃣7️⃣ Merge two dictionaries
def main():
    d1 = {'a': 1, 'b': 2}
    d2 = {'b': 3, 'c': 4}
    merged = {**d1, **d2}
    print(merged)

if __name__ == "__main__":
    main()

"""
Output
{'a': 1, 'b': 3, 'c': 4}
"""






5️⃣8️⃣ Find second largest number
def main():
    nums = [10, 20, 30, 40]
    unique = list(set(nums))
    unique.sort()
    print(unique[-2])

if __name__ == "__main__":
    main()

"""
Output
30
"""






5️⃣9️⃣ Check anagram
def main():
    s1 = "listen"
    s2 = "silent"
    print(sorted(s1) == sorted(s2))

if __name__ == "__main__":
    main()

"""
Output
True
"""






6️⃣0️⃣ Convert list of tuples to dict
def main():
    pairs = [("a", 1), ("b", 2)]
    d = dict(pairs)
    print(d)

if __name__ == "__main__":
    main()

"""
Output
{'a': 1, 'b': 2}
"""






6️⃣1️⃣ Rotate list right by k
def main():
    nums = [1, 2, 3, 4, 5]
    k = 2
    k %= len(nums)
    result = nums[-k:] + nums[:-k]
    print(result)

if __name__ == "__main__":
    main()

"""
Output
[4, 5, 1, 2, 3]
"""




6️⃣2️⃣ Remove duplicates using loop
def main():
    nums = [1, 2, 2, 3]
    result = []
    for n in nums:
        if n not in result:
            result.append(n)
    print(result)

if __name__ == "__main__":
    main()

"""
Output
[1, 2, 3]
"""





6️⃣3️⃣ Find intersection of lists using list comprehension
def main():
    a = [1, 2, 3]
    b = [2, 3, 4]
    result = [x for x in a if x in b]
    print(result)

if __name__ == "__main__":
    main()

"""
Output
[2, 3]
"""





6️⃣4️⃣ Sum of digits using while loop
def main():
    n = 1234
    total = 0
    while n > 0:
        total += n % 10
        n //= 10
    print(total)

if __name__ == "__main__":
    main()

"""
Output
10
"""





6️⃣5️⃣ Count words in sentence
def main():
    s = "Python is very powerful"
    print(len(s.split()))

if __name__ == "__main__":
    main()

"""
Output
4
"""





6️⃣6️⃣ Generator for even numbers
def even_gen(n):
    for i in range(n):
        if i % 2 == 0:
            yield i

def main():
    print(list(even_gen(10)))

if __name__ == "__main__":
    main()

"""
Output
[0, 2, 4, 6, 8]
"""







6️⃣7️⃣ Custom iterator class
class Count:
    def __init__(self, limit):
        self.num = 0
        self.limit = limit

    def __iter__(self):
        return self

    def __next__(self):
        if self.num < self.limit:
            val = self.num
            self.num += 1
            return val
        raise StopIteration

def main():
    for i in Count(3):
        print(i)

if __name__ == "__main__":
    main()

"""
Output
0
1
2
"""






6️⃣8️⃣ Check prime using function
def is_prime(n):
    if n <= 1:
        return False
    for i in range(2, int(n**0.5) + 1):
        if n % i == 0:
            return False
    return True

def main():
    print(is_prime(7))

if __name__ == "__main__":
    main()

"""
Output
True
"""





6️⃣9️⃣ Find factorial using recursion
def fact(n):
    if n == 0:
        return 1
    return n * fact(n - 1)

def main():
    print(fact(5))

if __name__ == "__main__":
    main()

"""
Output
120
"""








7️⃣0️⃣ Fibonacci using loop
def main():
    a, b = 0, 1
    for _ in range(5):
        print(a, end=" ")
        a, b = b, a + b

if __name__ == "__main__":
    main()

"""
Output
0 1 1 2 3
"""







7️⃣1️⃣ Check key existence
def main():
    d = {'a': 1, 'b': 2}
    print('a' in d)

if __name__ == "__main__":
    main()

"""
Output
True
"""






7️⃣2️⃣ Count characters using defaultdict
from collections import defaultdict

def main():
    s = "apple"
    d = defaultdict(int)
    for ch in s:
        d[ch] += 1
    print(dict(d))

if __name__ == "__main__":
    main()

"""
Output
{'a': 1, 'p': 2, 'l': 1, 'e': 1}
"""







7️⃣3️⃣ Sort list of dicts
def main():
    data = [{'age': 30}, {'age': 20}, {'age': 25}]
    result = sorted(data, key=lambda x: x['age'])
    print(result)

if __name__ == "__main__":
    main()

"""
Output
[{'age': 20}, {'age': 25}, {'age': 30}]
"""







7️⃣4️⃣ Find max value using reduce
from functools import reduce

def main():
    nums = [3, 7, 2, 9]
    print(reduce(lambda a, b: a if a > b else b, nums))

if __name__ == "__main__":
    main()

"""
Output
9
"""








7️⃣5️⃣ Count occurrences using Counter
from collections import Counter

def main():
    nums = [1, 2, 2, 3, 3, 3]
    print(Counter(nums))

if __name__ == "__main__":
    main()

"""
Output
Counter({3: 3, 2: 2, 1: 1})
"""







7️⃣6️⃣ String join example
def main():
    words = ["Python", "is", "fun"]
    print(" ".join(words))

if __name__ == "__main__":
    main()

"""
Output
Python is fun
"""






7️⃣7️⃣ Replace substring
def main():
    s = "hello world"
    print(s.replace("world", "python"))

if __name__ == "__main__":
    main()

"""
Output
hello python
"""






7️⃣8️⃣ File line count
def main():
    with open("sample.txt", "w") as f:
        f.write("a\nb\nc")

    with open("sample.txt", "r") as f:
        print(len(f.readlines()))

if __name__ == "__main__":
    main()

"""
Output
3
"""





7️⃣9️⃣ Tuple unpacking
def main():
    t = (10, 20)
    a, b = t
    print(a, b)

if __name__ == "__main__":
    main()

"""
Output
10 20
"""





8️⃣0️⃣ Swap variables (Pythonic)
def main():
    a, b = 5, 10
    a, b = b, a
    print(a, b)

if __name__ == "__main__":
    main()

"""
Output
10 5
"""
