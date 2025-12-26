/* ------------------------------------- */
input: {1,2,3,4,5,6,7}
output: {7,1,6,2,5,3,4}
(reverse-interleave: last, first, second-last...)



//Method 1 — Two-Pointer Direct Construction
#include <iostream>
#include<vector>
using namespace std;

int main() {
    vector<int> a = {1,2,3,4,5,6,7};
    vector<int> res;

    int l = 0, r = a.size() - 1;
    while (l <= r) {
        res.push_back(a[r--]);
        if (l <= r) res.push_back(a[l++]);
    }

    for (int x : res) cout << x << " ";
}
//7 1 6 2 5 3 4 



/* ------------------------------------- */




input: {1,2,3,4,5,6}
output: {1,4,2,5,3,6}
(interleave odd and even indexed elements)




input: {1,3,5,2,4,6}
output: {1,5,3,4,2,6}
(convert to zig-zag: a < b > c < d > e)




input: {1,4,45,6,10,8}, sum = 16
output: true
(pair with sum exists → 10 + 6)




input: {1,2,3,4,5}, k = 2
output: {4,5,1,2,3}
(right rotate by k)





input: {1,2,3,4,5}, k = 2
output: {3,4,5,1,2}
(left rotate by k)




input: {2,3,4,7,11}, target = 9
output: {2,7}
(pick pair with given target sum)



input: {1,2,3,4,5}
output: {1,3,6,10,15}
(prefix sum)




input: {1,2,3,4}
output: {24,12,8,6}
(product of all except self)





input: {1,2,3,4,5}
output: {1,3,6,10,15}
(running sum)





input: {5,4,3,2,1}
output: {1,2,3,4,5}
(sort ascending)



input: {10,5,20,40}
output: {5,10,20,40}
(sort with minimum comparisons)



input: {1,2,3,4}
output: {1,4,3,8}
(double the value at even index)




input: {3,30,34,5,9}
output: "9534330"
(form the largest number)


input: {5,3,9,7}
output: {3,5,7,9}
(sort ascending)


input: {"a","bb","c"}
output: {"c","a","bb"}
(sort by length)


input: {1,2,3,4,5,6}
output: {1,6,2,5,3,4}
(alternate min/max)



input: {0,1,2,1,2,0}
output: {0,0,1,1,2,2}
(Dutch national flag sorting)
















Category 1: Frequency / HashMap Logic (10 Questions)

input: {1,1,2,2,3,3,3}
output: true

input: {4,4,5,5,5,6,6}
output: false

input: {7,7,7,8,8,9}
output: 7

input: {1,2,3,4,5,5,5}
output: 5

input: {2,2,3,3,4,4,5,5}
output: false

input: {10,10,10,20,20,30}
output: 10

input: {6,7,8,9,10}
output: true

input: {1,1,1,1}
output: true

input: {1,2,2,3,3,3,4,4}
output: false

input: {5,5,6,6,7,7,8}
output: true
















Category 2: Move / Rearranging Elements (10 Questions)

input: {0,0,1,0,2,3}
output: {1,2,3,0,0,0}

input: {1,0,0,2,0,3,4}
output: {1,2,3,4,0,0,0}

input: {-1,2,-3,4,-5,6}
output: {-1,-3,-5,2,4,6}

input: {2,4,1,3,5,6}
output: {2,4,6,1,3,5}

input: {0,1,0,0,2,0,3}
output: {1,2,3,0,0,0,0}

input: {1,0,2,0,0,3}
output: {1,2,3,0,0,0}

input: {5,0,4,0,3,0,2,0,1}
output: {5,4,3,2,1,0,0,0,0}

input: {-2,3,-1,4,0}
output: {-2,-1,3,4,0}

input: {2,0,4,0,6,0,8}
output: {2,4,6,8,0,0,0}

input: {0,1,2,0,3,0,4}
output: {1,2,3,4,0,0,0}















Category 3: Interleaving / Swapping / Zig-Zag (10 Questions)

input: {1,2,3,4,5,6,7}
output: {7,1,6,2,5,3,4}

input: {1,2,3,4,5,6}
output: {2,1,4,3,6,5}

input: {10,20,30,40,50,60}
output: {30,20,10,60,50,40}

input: {1,3,5,2,4,6}
output: {1,5,3,4,2,6}

input: {1,2,3,4,5,6}
output: {1,4,2,5,3,6}

input: {7,1,6,2,5,3,4}
output: {4,7,3,1,2,6,5}

input: {1,2,3,4,5}
output: {1,3,2,5,4}

input: {1,3,2,4,5,6}
output: {1,2,3,4,5,6}

input: {10,20,30,40,50}
output: {50,10,40,20,30}

input: {1,2,3,4,5,6,7,8}
output: {8,1,7,2,6,3,5,4}

Category 4: Two-Pointer / Rotation / Prefix (10 Questions)

input: {1,2,3,4,5}, k=2 (right rotate)
output: {4,5,1,2,3}

input: {1,2,3,4,5}, k=2 (left rotate)
output: {3,4,5,1,2}

input: {1,4,45,6,10,8}, target=16
output: true

input: {2,3,5,7,11}, target=12
output: false

input: {1,2,3,4,5} (prefix sum)
output: {1,3,6,10,15}

input: {1,2,3,4,5} (suffix sum)
output: {15,14,12,9,5}

input: {2,3,4,5,6}, k=3 (right rotate)
output: {4,5,6,2,3}

input: {5,1,2,3,4}, target=6
output: {1,5}

input: {1,2,3,4,5}, k=1 (swap adjacent)
output: {2,1,4,3,5}

input: {1,2,3,4,5,6}, k=2 (swap every k elements)
output: {2,1,4,3,6,5}

Category 5: Product / Mathematical / Transform (5 Questions)

input: {1,2,3,4}
output: {24,12,8,6}

input: {2,3,4,5}
output: {60,40,30,24}

input: {1,2,3,4,5}
output: {1,3,6,10,15}

input: {1,2,3,4} (double even index)
output: {2,2,6,4}

input: {5,10,15,20} (triple odd index)
output: {5,30,15,60}








Category 6: Sorting / Custom / Largest Number (5 Questions)

input: {3,30,34,5,9}
output: 9534330

input: {1,2,3,4,5,6} (alternate min/max)
output: {1,6,2,5,3,4}

input: {0,1,2,1,2,0}
output: {0,0,1,1,2,2}

input: {10,5,20,40}
output: {5,10,20,40}

input: {"a","bb","c"}
output: {"a","c","bb"}