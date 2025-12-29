🔥 slicing with steps ([::2], [::-1])
🔥 slicing vs indexing internals
🔥 range() vs slicing comparison




1️⃣ SLICING WITH STEPS ([start:end:step])
🔹 General Syntax
arr[start : end : step]

| Part  | Meaning                   |
| ----- | ------------------------- |
| start | starting index (included) |
| end   | ending index (excluded)   |
| step  | jump size                 |

✅ Example 1: Every 2nd element ([::2])
def main():
    arr = [1, 2, 3, 4, 5, 6]
    print(arr[::2])

if __name__ == "__main__":
    main()


🖥 Output
[1, 3, 5]


Why?

start = 0
end   = len(arr)
step  = 2


✅ Example 2: Reverse list ([::-1]) ⭐⭐⭐
def main():
    arr = [1, 2, 3, 4]
    print(arr[::-1])

if __name__ == "__main__":
    main()

🖥 Output
[4, 3, 2, 1]

📌 Negative step → move backwards



✅ Example 3: Reverse part of list
def main():
    arr = [1, 2, 3, 4, 5]
    print(arr[1:4][::-1])

if __name__ == "__main__":
    main()

🖥 Output
[4, 3, 2]

🔥 Example 4: Negative step with start & end (TRAP)
def main():
    arr = [1, 2, 3, 4, 5]
    print(arr[4:1:-1])

if __name__ == "__main__":
    main()

🖥 Output
[5, 4, 3]


📌 Rule:
If step < 0 → start must be greater than end




🔥 2️⃣ SLICING vs INDEXING (INTERNAL BEHAVIOR)
This is VERY IMPORTANT.

🔹 Indexing (arr[i])
def main():
    arr = [10, 20, 30]

    print(arr[1])
    print(arr[10])  # ❌

if __name__ == "__main__":
    main()

🖥 Output
20
IndexError: list index out of range

🔍 Internals
Accesses exact memory location
Must exist

❌ Raises IndexError

🔹 Slicing (arr[a:b])
def main():
    arr = [10, 20, 30]

    print(arr[1:10])
    print(arr[-100:100])

if __name__ == "__main__":
    main()

🖥 Output
[20, 30]
[10, 20, 30]

🔍 Internals
Creates new list
Automatically clamps bounds
❌ NEVER throws IndexError

🔥 Key Differences (Interview Table)
| Feature    | Indexing       | Slicing    |
| ---------- | -------------- | ---------- |
| Returns    | Single element | New list   |
| IndexError | Yes            | No         |
| Memory     | No new memory  | New memory |
| Speed      | O(1)           | O(k)       |



🔥 3️⃣ range() vs SLICING (CONFUSION POINT)
🔹 range()
def main():
    r = range(1, 6)
    print(list(r))

if __name__ == "__main__":
    main()

🖥 Output
[1, 2, 3, 4, 5]

🔍 Internals
Lazy sequence
No memory allocation
Values generated on demand

🔹 Slicing
def main():
    arr = list(range(1, 6))
    print(arr[1:4])

if __name__ == "__main__":
    main()

🖥 Output
[2, 3, 4]

🔍 Internals
Eager
Allocates memory
Copies elements

🔥 Comparison Table (INTERVIEW)
| Feature   | range()          | slicing                 |
| --------- | ---------------- | ----------------------- |
| Memory    | O(1)             | O(k)                    |
| Mutable   | ❌                | ✅                       |
| Indexable | Yes              | Yes                     |
| Returns   | range object     | list                    |
| Speed     | Faster iteration | Slower for large slices |






🔥 Hybrid Trick (ADVANCED)
def main():
    r = range(10)
    print(list(r[2:8:2]))

if __name__ == "__main__":
    main()

🖥 Output
[2, 4, 6]

📌 range supports slicing efficiently.

🎯 FINAL INTERVIEW GOLD RULES
✔ [::-1] → fastest reverse
✔ slicing never crashes
✔ indexing crashes if invalid
✔ range = lazy
✔ slicing = eager

🧠 One-Liner Interview Answer
Python slicing uses half-open intervals and creates new sequences, while indexing accesses exact elements; range is lazy whereas slicing allocates memory.






arr = [1,2,3,4]

print(arr[:])     # [0:len(arr))
print(arr[:3])    # [0:3)
print(arr[2:])    # [2:len(arr))
print(arr[-3:-1]) # [-3:-1)

Output: 
[1, 2, 3, 4]
[1, 2, 3]
[3, 4]
[2, 3]
