'''
15. Modules
🔹 Short Note
Reuse code from other files/modules
Example: math module
'''

#✅ Program
import math

def main():
    print(math.sqrt(16))

if __name__ == "__main__":
    main()


'''
🖥 Output
4.0
'''





🔹 1️⃣ math Module (Basic)
import math
def main():
    print(math.sqrt(25))
    print(math.factorial(5))

if __name__ == "__main__":
    main()

""" 
🖥 Output
5.0
120
"""





🔹 2️⃣ sys Module (Command-line & system)
import sys
def main():
    print("Python Version:", sys.version)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Python Version: 3.x.x
"""





🔹 3️⃣ os Module (Operating System)
import os
def main():
    print("Current Working Directory:")
    print(os.getcwd())

if __name__ == "__main__":
    main()

""" 
🖥 Output
/path/to/current/directory
"""





🔹 4️⃣ datetime Module (Date & Time)
import datetime
def main():
    now = datetime.datetime.now()
    print("Current Date & Time:", now)

if __name__ == "__main__":
    main()

""" 
🖥 Output
Current Date & Time: 2025-xx-xx xx:xx:xx.xxxxxx
"""



🔹 5️⃣ time Module (Delay & time)
import time
def main():
    print("Start")
    time.sleep(2)
    print("End")

if __name__ == "__main__":
    main()

""" 
🖥 Output
Start
End
"""






🔹 6️⃣ random Module (Random values)
import random
def main():
    print(random.randint(1, 10))
    print(random.choice([10, 20, 30]))

if __name__ == "__main__":
    main()

""" 
🖥 Output
7
20
"""






🔹 7️⃣ statistics Module (Data analysis – basic)
import statistics

def main():
    data = [10, 20, 30, 40]
    print("Mean:", statistics.mean(data))

if __name__ == "__main__":
    main()

""" 
🖥 Output
Mean: 25
"""







🔹 8️⃣ collections Module (Advanced data structures)
from collections import Counter

def main():
    data = ["a", "b", "a", "c", "b", "a"]
    print(Counter(data))

if __name__ == "__main__":
    main()

""" 
🖥 Output
Counter({'a': 3, 'b': 2, 'c': 1})
"""









🔹 9️⃣ itertools Module (Advanced iteration)
import itertools

def main():
    nums = [1, 2, 3]
    result = list(itertools.permutations(nums))
    print(result)

if __name__ == "__main__":
    main()

""" 
🖥 Output
[(1, 2, 3), (1, 3, 2), (2, 1, 3), (2, 3, 1), (3, 1, 2), (3, 2, 1)]
"""






🔹 🔟 functools Module (Functional programming)
from functools import reduce
def main():
    nums = [1, 2, 3, 4]
    result = reduce(lambda a, b: a + b, nums)
    print(result)

if __name__ == "__main__":
    main()

""" 
🖥 Output
10
"""





🔹 1️⃣1️⃣ re Module (Regular Expressions)
import re
def main():
    text = "Python123"
    result = re.findall(r"\d+", text)
    print(result)

if __name__ == "__main__":
    main()

""" 
🖥 Output
['123']
"""




🔹 1️⃣2️⃣ json Module (Data exchange)
import json
def main():
    data = {"name": "Alice", "age": 20}
    json_data = json.dumps(data)
    print(json_data)

if __name__ == "__main__":
    main()

""" 
🖥 Output
{"name": "Alice", "age": 20}
"""




🔹 1️⃣3️⃣ pickle Module (Object serialization)
import pickle
def main():
    data = {"a": 1, "b": 2}
    with open("data.pkl", "wb") as f:
        pickle.dump(data, f)

    with open("data.pkl", "rb") as f:
        print(pickle.load(f))

if __name__ == "__main__":
    main()

""" 
🖥 Output
{'a': 1, 'b': 2}
"""





🔹 1️⃣4️⃣ logging Module (Production-level)
import logging
def main():
    logging.basicConfig(level=logging.INFO)
    logging.info("This is an info message")

if __name__ == "__main__":
    main()

""" 
🖥 Output
INFO:root:This is an info message
"""



🔹 1️⃣5️⃣ abc Module (Abstraction)
from abc import ABC, abstractmethod

class Shape(ABC):
    @abstractmethod
    def area(self):
        pass

class Square(Shape):
    def area(self):
        return 25

def main():
    s = Square()
    print(s.area())

if __name__ == "__main__":
    main()

""" 
🖥 Output
25
"""