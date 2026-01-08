
#How to avoid this surprise (best practice)
#✔ Option 1: Don’t use loop variable later
for _ in range(3):
    pass




#✔ Option 2: Use a function scope
def f():
    for i in range(3):
        pass

f()
# print(i) ❌ NameError

'''
Final takeaway (memorize this)
🔥 In Python, loop variables do NOT have block scope
'''












# ❌ Surprise 2: if does NOT create a scope
if True:
    x = 10

print(x)   # 10
'''
Where is the error?
➡ No error

Why?
if blocks do not create scope in Python
Same rule as for loops
'''
#C++ contrast
'''
if (true) {
    int x = 10;
}
cout << x;   // ❌ error
'''







# ❌ Surprise 3: Late binding in loops (lambda trap)
funcs = []

for i in range(3):
    funcs.append(lambda: i)

for f in funcs:
    print(f())
'''
Output
2
2
2

Where is the error?
➡ Logical error due to late binding
'''

#Fix
funcs.append(lambda i=i: i)







# ❌ Surprise 4: Assignment ≠ Copy
a = [1, 2, 3]
b = a
b.append(4)

print(a)   # [1, 2, 3, 4]
'''
Where is the error?
➡ Both variables point to the same object
'''
#Fix
b = a.copy()

# ❌ Surprise 5: == vs is
a = [1,2,3]
b = [1,2,3]

print(a == b)   # True
print(a is b)   # False
'''
Where is the error?
➡ Using is for value comparison
'''
# Rule
'''
| Operator | Meaning                |
| -------- | ---------------------- |
| `==`     | value equality         |
| `is`     | identity (same object) |
'''











#❌ Surprise 6: Integer caching (looks like a bug)
a = 256
b = 256
print(a is b)   # True

a = 300
b = 300
print(a is b)   # False
'''
Where is the error?
➡ No error, CPython optimization

Rule
Small integers are cached (usually -5 to 256)
'''











#❌ Surprise 7: Default argument evaluated ONCE
def f(x=[]):
    x.append(1)
    return x

print(f())
print(f())
'''
Output
[1]
[1, 1]
'''
#Fix (ALWAYS DO THIS)
def f(x=None):
    if x is None:
        x = []










#❌ Surprise 8: Floating-point equality fails
print(0.1 + 0.2 == 0.3)   # False

#Where is the error?
#➡ Floating-point representation

#Fix
import math
print(math.isclose(0.1 + 0.2, 0.3))


# ❌ Surprise 9: Truthiness rules
if []:
    print("Yes")
else:
    print("No")   # No

'''
Truthy / Falsy
| Value  | Boolean |
| ------ | ------- |
| `0`    | False   |
| `""`   | False   |
| `[]`   | False   |
| `{}`   | False   |
| `None` | False   |
'''



# ❌ Surprise 10: Function returns None by default
def f():
    pass

print(f())   # None

# Where is the error?
#➡ No return → None implicitly returned









#❌ Surprise 11: else with for loop
#❌ Confusing Code
def main():
    for i in range(3):
        if i == 5:
            break
    else:
        print("Loop finished normally")

if __name__ == "__main__":
    main()
'''
🖥 Output
Loop finished normally

❓ Where is the error?
➡ No error
➡ else runs only if loop does NOT break
'''










# ❌ Surprise 12: else with while
def main():
    i = 0
    while i < 3:
        i += 1
    else:
        print("While loop completed")

if __name__ == "__main__":
    main()
'''
🖥 Output
While loop completed
'''











#❌ Surprise 13: Mutable object passed to function
def modify(arr):
    arr.append(100)

def main():
    nums = [1, 2, 3]
    modify(nums)
    print(nums)

if __name__ == "__main__":
    main()
'''
🖥 Output
[1, 2, 3, 100]

❓ Where is the error?

➡ No error
➡ Lists behave like C++ pointers
'''







# ❌ Surprise 14: Immutable object not modified
def modify(x):
    x += 10

def main():
    n = 5
    modify(n)
    print(n)

if __name__ == "__main__":
    main()
'''
🖥 Output
5

🧠 Reason
int is immutable
Similar to pass-by-value in C++
'''









# ❌ Surprise 15: Chained comparison
def main():
    x = 5
    print(1 < x < 10)

if __name__ == "__main__":
    main()
'''
🖥 Output
True

❓ Where is the error?
➡ No error
➡ Python evaluates as: 1 < x and x < 10
'''







#❌ Surprise 16: Negative indexing
def main():
    arr = [10, 20, 30, 40]
    print(arr[-1])
    print(arr[-2])

if __name__ == "__main__":
    main()
'''
🖥 Output
40
30

🧠 C++ dev shock
➡ No bounds error
➡ Negative index counts from end
'''




#❌ Surprise 17: Slicing never crashes
def main():
    arr = [1, 2, 3]
    print(arr[0:10])

if __name__ == "__main__":
    main()
'''
🖥 Output
[1, 2, 3]
'''








# ❌ Surprise 18: += behaves differently
def main():
    a = [1, 2]
    b = a
    a += [3, 4]
    print(a)
    print(b)

if __name__ == "__main__":
    main()
'''
🖥 Output
[1, 2, 3, 4]
[1, 2, 3, 4]

🧠 Reason
➡ += modifies object in-place
'''









# ❌ Surprise 19: * with lists
def main():
    matrix = [[0] * 3] * 3
    matrix[0][0] = 1
    print(matrix)

if __name__ == "__main__":
    main()
'''
🖥 Output
[[1, 0, 0], [1, 0, 0], [1, 0, 0]]

❓ Where is the error?
➡ All rows share same reference

✔ Fix
matrix = [[0] * 3 for _ in range(3)]
'''





#❌ Surprise 20: Dictionary iteration
def main():
    d = {"a": 1, "b": 2}
    for x in d:
        print(x)

if __name__ == "__main__":
    main()
'''
🖥 Output
a
b

🧠 Rule
➡ Iterating dict gives keys, not key-value pairs
'''






#❌ Surprise 21: Order preserved in dict (Python 3.7+)
def main():
    d = {}
    d["x"] = 1
    d["y"] = 2
    d["z"] = 3
    print(d)

if __name__ == "__main__":
    main()
'''
🖥 Output
{'x': 1, 'y': 2, 'z': 3}

➡ Unlike old C++ map
'''









#❌ Surprise 23: Recursion limit
def f(n):
    return f(n + 1)

f(1)
'''
🖥 Output
RecursionError: maximum recursion depth exceeded

🧠 Unlike C++, Python limits recursion depth
'''







#❌ Surprise 24: return inside finally
def main():
    try:
        return 10
    finally:
        return 20

print(main())
'''
🖥 Output
20

➡ finally overrides return
'''



#❌ Surprise 25: Modifying list during iteration
def main():
    nums = [1, 2, 3, 4, 5]
    for n in nums:
        if n % 2 == 0:
            nums.remove(n)
    print(nums)         
if __name__ == "__main__":
    main()
''' 
🖥 Output
[1, 3, 5]
➡ Modifying list while iterating causes skipping elements
'''

#✔ Fix: Iterate over a copy
def main():
    nums = [1, 2, 3, 4, 5]
    for n in nums[:]:  # Iterate over a copy
        if n % 2 == 0:
            nums.remove(n)
    print(nums)         
if __name__ == "__main__":
    main()
'''     
🖥 Output
[1, 3, 5]
'''


#❌ Surprise 26: setdefault vs defaultdict
from collections import defaultdict
def main():
    d1 = {}
    d2 = defaultdict(list)

    d1.setdefault('a', []).append(1)
    d2['a'].append(1)

    print(d1)  # {'a': [1]}
    print(d2)  # defaultdict(<class 'list'>, {'a': [1]})
if __name__ == "__main__":
    main()
''' 
🖥 Output
{'a': [1]}
defaultdict(<class 'list'>, {'a': [1]})
➡ defaultdict auto-creates entries
'''



#✔ Fix: Use defaultdict for auto-creation
from collections import defaultdict
def main():
    d = defaultdict(list)
    d['a'].append(1)
    print(d)  # defaultdict(<class 'list'>, {'a': [1]})
if __name__ == "__main__":
    main()
'''         
🖥 Output   
defaultdict(<class 'list'>, {'a': [1]})
''' 







#❌ Surprise 27: Mutable default args with dict
def add_entry(key, value, d={}):
    d[key] = value
    return d    
def main():
    print(add_entry('a', 1))  # {'a': 1}
    print(add_entry('b', 2))  # {'a': 1, 'b': 2}
if __name__ == "__main__":
    main()
'''
🖥 Output
{'a': 1}
{'a': 1, 'b': 2}
➡ Mutable default arg retains changes
'''




#✔ Fix: Use None as default
def add_entry(key, value, d=None):
    if d is None:
        d = {}
    d[key] = value
    return d    
def main():
    print(add_entry('a', 1))  # {'a': 1}
    print(add_entry('b', 2))  # {'b': 2}
if __name__ == "__main__":
    main()
''' 
🖥 Output
{'a': 1}
{'b': 2}
''' 



