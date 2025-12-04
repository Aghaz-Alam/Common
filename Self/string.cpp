Category 1: Frequency / HashMap Based (6 Questions)

input: "aabbcc"
output: true
(All character frequencies unique)

/* ------------------------------- */
Program 1 — Input: "aabbcc" → Output: false
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    string s = "aabbcc";
    unordered_map<char, int> freq;

    for (char c : s) freq[c]++;

    for (auto i = freq.begin(); i != freq.end(); ++i) {
        for (auto j = next(i); j != freq.end(); ++j) {
            if (i->second == j->second) {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
}

/* ------------------------------- */
input: "aabbccc"
output: false
(Frequencies: a=2, b=2, c=3 → duplicate)
/* ---------------------------------- */
Program 2 — Input: "aabbccc" → Output: false
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    string s = "aabbccc";
    unordered_map<char, int> freq;

    for (char c : s) freq[c]++;

    for (auto i = freq.begin(); i != freq.end(); ++i) {
        for (auto j = next(i); j != freq.end(); ++j) {
            if (i->second == j->second) {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
}
/* ---------------------------------- */
input: "abcabc"
output: true
(Frequencies: a=2, b=2, c=2 → duplicate → false?) Actually output: false
/* ---------------------------------- */
Program 3 — Input: "abcabc" → Output: false
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    string s = "abcabc";
    unordered_map<char, int> freq;

    for (char c : s) freq[c]++;

    for (auto i = freq.begin(); i != freq.end(); ++i) {
        for (auto j = next(i); j != freq.end(); ++j) {
            if (i->second == j->second) {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
}
/* ---------------------------------- */

input: "aabbc"
output: true
(Frequencies: a=2, b=2, c=1 → all frequencies unique?) → careful: 2 appears twice → false
/* ---------------------------------- */
Program 4 — Input: "aabbc" → Output: false
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    string s = "aabbc";
    unordered_map<char, int> freq;

    for (char c : s) freq[c]++;

    for (auto i = freq.begin(); i != freq.end(); ++i) {
        for (auto j = next(i); j != freq.end(); ++j) {
            if (i->second == j->second) {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
}
/* ---------------------------------- */

input: "abcd"
output: true
(All characters appear once)
/* ---------------------------------- */
Program 5 — Input: "abcd" → Output: false
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    string s = "abcd";
    unordered_map<char, int> freq;

    for (char c : s) freq[c]++;

    for (auto i = freq.begin(); i != freq.end(); ++i) {
        for (auto j = next(i); j != freq.end(); ++j) {
            if (i->second == j->second) {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
}
/* ---------------------------------- */

input: "aabbbcccc"
output: true
(Frequencies: a=2, b=3, c=4 → all unique)
/* ---------------------------------- */
Program 6 — Input: "aabbbcccc" → Output: true
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    string s = "aabbbcccc";
    unordered_map<char, int> freq;

    for (char c : s) freq[c]++;

    for (auto i = freq.begin(); i != freq.end(); ++i) {
        for (auto j = next(i); j != freq.end(); ++j) {
            if (i->second == j->second) {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
}
/* ---------------------------------- */
/* ---------------------------------------------------------------------------------- */
//Using Only One Container
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool hasUniqueFrequencies(const string& s) {
    unordered_map<char, int> freq;   // Only one container used

    // Count frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    // Check if any two frequencies are same
    // We do NOT use another container; instead, we check using nested loops
    for (auto it1 = freq.begin(); it1 != freq.end(); ++it1) {
        for (auto it2 = next(it1); it2 != freq.end(); ++it2) {
            if (it1->second == it2->second) {
                return false;
            }
        }
    }

    return true;
}

int main() {
    string input;
    getline(cin, input);

    cout << (hasUniqueFrequencies(input) ? "true" : "false") << endl;
    return 0;
}
//Output:
| Input         | Frequency Map   | Output    |
| ------------- | --------------- | --------- |
| `"aabbcc"`    | a=2,b=2,c=2     | **false** |
| `"aabbccc"`   | a=2,b=2,c=3     | **false** |
| `"abcabc"`    | a=2,b=2,c=2     | **false** |
| `"aabbc"`     | a=2,b=2,c=1     | **false** |
| `"abcd"`      | a=1,b=1,c=1,d=1 | **false** |
| `"aabbbcccc"` | a=2,b=3,c=4     | **true**  |


/* ---------------------------------------------------------------------------------- */
//C++ PROGRAM (One Container Only)
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool checkFrequencies(const string& s) {

    unordered_map<char, int> freq;    // ONLY container used

    // Count frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    int firstFreq = -1;
    bool allSame = true;
    bool allUnique = true;

    // Convert map to frequency array manually (without containers)
    // We will compare each frequency against all others using nested loops
    int freqArr[256];      // temporary raw array (not a container)
    int k = 0;

    for (auto &p : freq) {
        freqArr[k++] = p.second;
    }

    int n = k;

    // ------------------- Check All Same -------------------
    firstFreq = freqArr[0];
    for (int i = 1; i < n; i++) {
        if (freqArr[i] != firstFreq) {
            allSame = false;
            break;
        }
    }

    if (allSame) return true;

    // ------------------- Check All Unique -------------------
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (freqArr[i] == freqArr[j]) {
                allUnique = false;
                break;
            }
        }
        if (!allUnique) break;
    }

    if (allUnique) return true;

    return false;   // mixed
}

int main() {
    string s;
    cin >> s;

    cout << (checkFrequencies(s) ? "true" : "false");
    return 0;
}

//output:
| Input         | Frequencies | Status   | Output |
| ------------- | ----------- | -------- | ------ |
| `"aabbcc"`    | 2,2,2       | all same | true   |
| `"aabbccc"`   | 2,2,3       | mixed    | false  |
| `"abcabc"`    | 2,2,2       | all same | true   |
| `"aabbc"`     | 2,2,1       | mixed    | false  |
| `"abcd"`      | 1,1,1,1     | all same | true   |
| `"aabbbcccc"` | 2,3,4       | unique   | true   |

/* ---------------------------------------------------------------------------------- */
//Unique Character Frequencies usin unordered_map and set
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;
bool hasUniqueFrequencies(const string& s) {
    unordered_map<char, int> freq;

    // Count frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    unordered_set<int> seen;

    // Check if all frequencies are unique
    for (auto &p : freq) {
        int f = p.second;
        if (seen.count(f)) {
            return false;  // Duplicate frequency found
        }
        seen.insert(f);
    }

    return true;
}

int main() {
    string s = "aabbbcccc";             

    if (hasUniqueFrequencies(s))
        cout << "true";
    else
        cout << "false";

    return 0;
}
//aabbbcccc         (all unique true)
| Input         | Frequencies | Unique?      | Output            |
| ------------- | ----------- | ------------ | ----------------- |
| `"aabbcc"`    | 2,2,2       | ❌ Duplicate  | **false**         |
| `"aabbccc"`   | 2,2,3       | ❌ Duplicate  | **false**         |
| `"abcabc"`    | 2,2,2       | ❌ Duplicate  | **false**         |
| `"aabbc"`     | 2,2,1       | ❌ Duplicate  | **false**         |
| `"abcd"`      | 1,1,1       | ❌ Duplicate  | **false** (all 1) |
| `"aabbbcccc"` | 2,3,4       | ✔ All unique | **true**          |




//Unique Character Frequencies using unordered_map and vector
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

bool hasUniqueFrequencies(const string& s) {
    unordered_map<char, int> freq;

    // Count char frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    vector<int> freqValues;
    freqValues.reserve(freq.size());

    // Collect all frequencies into vector
    for (auto &p : freq) {
        freqValues.push_back(p.second);
    }

    // Check if frequencies are unique using simple comparison
    for (int i = 0; i < freqValues.size(); i++) {
        for (int j = i + 1; j < freqValues.size(); j++) {
            if (freqValues[i] == freqValues[j]) {
                return false;  // Duplicate found
            }
        }
    }

    return true; // All unique
}

int main() {
    string s = "aabbbcccc";

    if (hasUniqueFrequencies(s))
        cout << "true";
    else
        cout << "false";

    return 0;
}

//Output:
| Input         | Frequencies | Unique?     | Output |
| ------------- | ----------- | ----------- | ------ |
| `"aabbcc"`    | 2,2,2       | ❌ Duplicate | false  |
| `"aabbccc"`   | 2,2,3       | ❌ Duplicate | false  |
| `"abcabc"`    | 2,2,2       | ❌ Duplicate | false  |
| `"aabbc"`     | 2,2,1       | ❌ Duplicate | false  |
| `"abcd"`      | 1,1,1,1     | ❌ Duplicate | false  |
| `"aabbbcccc"` | 2,3,4       | ✔ Unique    | true   |




/* ---------------------------------------------------------------------------------- */

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

bool checkFrequencies(const string& s) {
    unordered_map<char, int> freq;

    // Count frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    unordered_set<int> uniqueFreq;

    for (auto &p : freq) {
        uniqueFreq.insert(p.second);
    }

    // Case 1: All frequencies are the same → valid
    if (uniqueFreq.size() == 1)
        return true;

    // Case 2: All frequencies are different → valid
    if (uniqueFreq.size() == freq.size())
        return true;

    // Otherwise invalid
    return false;
}

int main() {
    string s;
    cin >> s;

    cout << (checkFrequencies(s) ? "true" : "false");
    return 0;
}
//Output:

| Input         | Frequencies | Output    |
| ------------- | ----------- | --------- |
| `"aabbcc"`    | 2,2,2       | **true**  |
| `"aabbccc"`   | 2,2,3       | **false** |
| `"abcabc"`    | 2,2,2       | **true**  |
| `"aabbc"`     | 2,2,1       | **false** |
| `"abcd"`      | 1,1,1,1     | **true**  |
| `"aabbbcccc"` | 2,3,4       | **true**  |





#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

bool checkFrequencies(const string& s) {
    unordered_map<char, int> freq;

    // Count frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    vector<int> freqValues;
    for (auto &p : freq) {
        freqValues.push_back(p.second);
    }

    int n = freqValues.size();

    // ---------- Case 1: All frequencies same ----------
    bool allSame = true;
    for (int i = 1; i < n; i++) {
        if (freqValues[i] != freqValues[0]) {
            allSame = false;
            break;
        }
    }
    if (allSame) return true;

    // ---------- Case 2: All frequencies unique ----------
    bool allUnique = true;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (freqValues[i] == freqValues[j]) {
                allUnique = false;
                break;
            }
        }
        if (!allUnique) break;
    }

    if (allUnique) return true;

    // Otherwise invalid
    return false;
}

int main() {
    string s;
    cin >> s;

    cout << (checkFrequencies(s) ? "true" : "false");
    return 0;
}
//Output:
| Input         | Frequencies | Output |
| ------------- | ----------- | ------ |
| `"aabbcc"`    | 2,2,2       | true   |
| `"aabbccc"`   | 2,2,3       | false  |
| `"abcabc"`    | 2,2,2       | true   |
| `"aabbc"`     | 2,2,1       | false  |
| `"abcd"`      | 1,1,1,1     | true   |
| `"aabbbcccc"` | 2,3,4       | true   |

/* ---------------------------------------------------------------------------------- */
//Mixed frequencies
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;

bool checkFrequencies(const string& s) {
    unordered_map<char, int> freq;

    // Count frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    unordered_set<int> uniqueFreq;

    // Insert all distinct frequencies
    for (auto &p : freq) {
        uniqueFreq.insert(p.second);
    }

    // Case 1: All frequencies same → valid
    if (uniqueFreq.size() == 1)
        return true;

    // Case 2: All frequencies are unique → valid
    if (uniqueFreq.size() == freq.size())
        return true;

    // Otherwise invalid
    return false;
}

int main() {
    string s;
    cin >> s;

    cout << (checkFrequencies(s) ? "true" : "false");
    return 0;
}

//output:
| Input         | Frequencies | Status     | Output    |
| ------------- | ----------- | ---------- | --------- |
| `"aabbcc"`    | 2,2,2       | all same   | **true**  |
| `"aabbccc"`   | 2,2,3       | mixed      | **false** |
| `"abcabc"`    | 2,2,2       | all same   | **true**  |
| `"aabbc"`     | 2,2,1       | mixed      | **false** |
| `"abcd"`      | 1,1,1,1     | all same   | **true**  |
| `"aabbbcccc"` | 2,3,4       | all unique | **true**  |



#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

bool checkFrequencies(const string& s) {
    unordered_map<char, int> freq;

    // Count frequency of each character
    for (char ch : s) {
        freq[ch]++;
    }

    // Store all frequencies in a vector
    vector<int> freqValues;
    for (auto &p : freq) {
        freqValues.push_back(p.second);
    }

    int n = freqValues.size();

    // -------------------------
    // Case 1: All frequencies same
    // -------------------------
    bool allSame = true;
    for (int i = 1; i < n; i++) {
        if (freqValues[i] != freqValues[0]) {
            allSame = false;
            break;
        }
    }
    if (allSame) return true;

    // -------------------------
    // Case 2: All frequencies unique
    // -------------------------
    bool allUnique = true;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (freqValues[i] == freqValues[j]) {
                allUnique = false;
                break;
            }
        }
        if (!allUnique) break;
    }
    if (allUnique) return true;

    // Otherwise invalid
    return false;
}

int main() {
    string s;
    cin >> s;

    cout << (checkFrequencies(s) ? "true" : "false");
    return 0;
}

//output:
| Input         | Frequencies | Status     | Output |
| ------------- | ----------- | ---------- | ------ |
| `"aabbcc"`    | 2,2,2       | all same   | true   |
| `"aabbccc"`   | 2,2,3       | mixed      | false  |
| `"abcabc"`    | 2,2,2       | all same   | true   |
| `"aabbc"`     | 2,2,1       | mixed      | false  |
| `"abcd"`      | 1,1,1,1     | all same   | true   |
| `"aabbbcccc"` | 2,3,4       | all unique | true   |

/* ---------------------------------------------------------------------------------- */

//C++ PROGRAM (One Container Only)
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

bool checkFrequencies(const string& s) {

    unordered_map<char, int> freq;    // ONLY container used

    // Count frequencies
    for (char ch : s) {
        freq[ch]++;
    }

    int firstFreq = -1;
    bool allSame = true;
    bool allUnique = true;

    // Convert map to frequency array manually (without containers)
    // We will compare each frequency against all others using nested loops
    int freqArr[256];      // temporary raw array (not a container)
    int k = 0;

    for (auto &p : freq) {
        freqArr[k++] = p.second;
    }

    int n = k;

    // ------------------- Check All Same -------------------
    firstFreq = freqArr[0];
    for (int i = 1; i < n; i++) {
        if (freqArr[i] != firstFreq) {
            allSame = false;
            break;
        }
    }

    if (allSame) return true;

    // ------------------- Check All Unique -------------------
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (freqArr[i] == freqArr[j]) {
                allUnique = false;
                break;
            }
        }
        if (!allUnique) break;
    }

    if (allUnique) return true;

    return false;   // mixed
}

int main() {
    string s;
    cin >> s;

    cout << (checkFrequencies(s) ? "true" : "false");
    return 0;
}

//output:
| Input         | Frequencies | Status   | Output |
| ------------- | ----------- | -------- | ------ |
| `"aabbcc"`    | 2,2,2       | all same | true   |
| `"aabbccc"`   | 2,2,3       | mixed    | false  |
| `"abcabc"`    | 2,2,2       | all same | true   |
| `"aabbc"`     | 2,2,1       | mixed    | false  |
| `"abcd"`      | 1,1,1,1     | all same | true   |
| `"aabbbcccc"` | 2,3,4       | unique   | true   |


/* --------------------------------------------------------------------------------- */





Category 2: Palindrome / Reverse (5 Questions)

input: "racecar"
output: true
/* ------------------------- */
//Program 1 – Check palindrome (“racecar” → true)
#include <iostream>
#include <string>
using namespace std;
bool isPalindrome(const string &s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}
int main() {
    string s = "racecar";
    cout << (isPalindrome(s) ? "true" : "false");
    return 0;
}

/* ------------------------- */
input: "hello"
output: false
/* ------------------------- */
Program 2 – Check palindrome (“hello” → false)
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string &s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    string s = "hello";
    cout << (isPalindrome(s) ? "true" : "false");
    return 0;
}
/* ------------------------- */
input: "abba"
output: true
/* ------------------------- */
Program 3 – Check palindrome (“abba” → true)
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string &s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    string s = "abba";
    cout << (isPalindrome(s) ? "true" : "false");
    return 0;
}
/* ------------------------- */
input: "abcba"
output: true
/* ------------------------- */
Program 4 – Check palindrome (“abcba” → true)
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string &s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    string s = "abcba";
    cout << (isPalindrome(s) ? "true" : "false");
    return 0;
}
/* ------------------------- */
input: "abcd"
output: false
/* ------------------------- */
Program 5 – Check palindrome (“abcd” → false)
#include <iostream>
#include <string>
using namespace std;

bool isPalindrome(const string &s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
        if (s[i] != s[j])
            return false;
        i++;
        j--;
    }
    return true;
}

int main() {
    string s = "abcd";
    cout << (isPalindrome(s) ? "true" : "false");
    return 0;
}
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */













Category 3: Anagram / Permutations (5 Questions)
/* ---------------------------- */
PROGRAM 1
✔ Input: "listen", "silent"
✔ Output: true

#include <iostream>
#include <string>
using namespace std;

bool isAnagram(const string &s1, const string &s2);

int main() {
    string a = "listen", b = "silent";
    cout << (isAnagram(a, b) ? "true" : "false");
    return 0;
}

bool isAnagram(const string &s1, const string &s2) {
    if (s1.length() != s2.length())
        return false;

    int freq[256] = {0};

    for (int i = 0; i < s1.length(); i++)
        freq[(unsigned char)s1[i]]++;

    for (int i = 0; i < s2.length(); i++)
        freq[(unsigned char)s2[i]]--;

    for (int i = 0; i < 256; i++)
        if (freq[i] != 0)
            return false;

    return true;
}
/* ---------------------------- */

PROGRAM 2
✔ Input: "triangle", "integral"
✔ Output: true
#include <iostream>
#include <string>
using namespace std;

bool isAnagram(const string &s1, const string &s2);

int main() {
    string a = "triangle", b = "integral";
    cout << (isAnagram(a, b) ? "true" : "false");
    return 0;
}

bool isAnagram(const string &s1, const string &s2) {
    if (s1.length() != s2.length())
        return false;

    int freq[256] = {0};

    for (int i = 0; i < s1.length(); i++)
        freq[(unsigned char)s1[i]]++;

    for (int i = 0; i < s2.length(); i++)
        freq[(unsigned char)s2[i]]--;

    for (int i = 0; i < 256; i++)
        if (freq[i] != 0)
            return false;

    return true;
}
/* ---------------------------- */
PROGRAM 3
✔ Input: "apple", "papel"
✔ Output: true
#include <iostream>
#include <string>
using namespace std;

bool isAnagram(const string &s1, const string &s2);

int main() {
    string a = "apple", b = "papel";
    cout << (isAnagram(a, b) ? "true" : "false");
    return 0;
}

bool isAnagram(const string &s1, const string &s2) {
    if (s1.length() != s2.length())
        return false;

    int freq[256] = {0};

    for (int i = 0; i < s1.length(); i++)
        freq[(unsigned char)s1[i]]++;

    for (int i = 0; i < s2.length(); i++)
        freq[(unsigned char)s2[i]]--;

    for (int i = 0; i < 256; i++)
        if (freq[i] != 0)
            return false;

    return true;
}

/* ---------------------------- */
PROGRAM 4
✔ Input: "rat", "car"
✔ Output: false
#include <iostream>
#include <string>
using namespace std;

bool isAnagram(const string &s1, const string &s2);

int main() {
    string a = "rat", b = "car";
    cout << (isAnagram(a, b) ? "true" : "false");
    return 0;
}

bool isAnagram(const string &s1, const string &s2) {
    if (s1.length() != s2.length())
        return false;

    int freq[256] = {0};

    for (int i = 0; i < s1.length(); i++)
        freq[(unsigned char)s1[i]]++;

    for (int i = 0; i < s2.length(); i++)
        freq[(unsigned char)s2[i]]--;

    for (int i = 0; i < 256; i++)
        if (freq[i] != 0)
            return false;

    return true;
}
/* ---------------------------- */
PROGRAM 5
✔ Input: "aabb", "bbaa"
✔ Output: true
#include <iostream>
#include <string>
using namespace std;

bool isAnagram(const string &s1, const string &s2);

int main() {
    string a = "aabb", b = "bbaa";
    cout << (isAnagram(a, b) ? "true" : "false");
    return 0;
}

bool isAnagram(const string &s1, const string &s2) {
    if (s1.length() != s2.length())
        return false;

    int freq[256] = {0};

    for (int i = 0; i < s1.length(); i++)
        freq[(unsigned char)s1[i]]++;

    for (int i = 0; i < s2.length(); i++)
        freq[(unsigned char)s2[i]]--;

    for (int i = 0; i < 256; i++)
        if (freq[i] != 0)
            return false;

    return true;
}
/* ---------------------------- */

/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */












Category 4: Rearrange / Pattern / Swap (5 Questions)
/* --------------------------------------------------- */
PROGRAM 1
Input: "aabbcc"
Output: "abcabc"

(Rearrange so no two adjacent characters are the same)

This uses a max-frequency check + arrange alternately.

#include <iostream>
#include <string>
using namespace std;

string rearrangeString(const string &s) {
    int freq[256] = {0};

    for (char ch : s)
        freq[(unsigned char)ch]++;

    int maxFreq = 0;
    char maxChar;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxChar = (char)i;
        }
    }

    if (maxFreq > (s.length() + 1) / 2)
        return "";

    string res(s.length(), ' ');

    int index = 0;

    while (freq[(unsigned char)maxChar] > 0) {
        res[index] = maxChar;
        index += 2;
        freq[(unsigned char)maxChar]--;
    }

    for (int i = 0; i < 256; i++) {
        while (freq[i] > 0) {
            if (index >= res.length()) index = 1;
            res[index] = (char)i;
            index += 2;
            freq[i]--;
        }
    }

    return res;
}

int main() {
    string s = "aabbcc";
    cout << rearrangeString(s);
    return 0;
}

/* --------------------------------------------------- */
PROGRAM 2
input: "aaabb"
output: "ababa"
(Rearranged to avoid adjacent same letters)
/* --------------------------------------------------- */
#include <iostream>
#include <string>
using namespace std;

string rearrangeString(const string &s);

int main() {
    string s = "aaabb";
    cout << rearrangeString(s);
    return 0;
}

string rearrangeString(const string &s) {
    int freq[256] = {0};

    for (char ch : s)
        freq[(unsigned char)ch]++;

    int maxFreq = 0;
    char maxChar;

    for (int i = 0; i < 256; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxChar = (char)i;
        }
    }

    if (maxFreq > (s.length() + 1) / 2)
        return "";

    string res(s.length(), ' ');

    int index = 0;
    while (freq[(unsigned char)maxChar] > 0) {
        res[index] = maxChar;
        index += 2;
        freq[(unsigned char)maxChar]--;
    }

    for (int i = 0; i < 256; i++) {
        while (freq[i] > 0) {
            if (index >= res.length()) index = 1;
            res[index] = (char)i;
            index += 2;
            freq[i]--;
        }
    }

    return res;
}

/* --------------------------------------------------- */
input: "aaab"
output: ""
(Impossible to rearrange)
/* --------------------------------------------------- */
PROGRAM 3
Input: "aaab"
Output: ""

(Impossible to rearrange)

#include <iostream>
#include <string>
using namespace std;

string rearrangeString(const string &s);

int main() {
    string s = "aaab";
    cout << rearrangeString(s);
    return 0;
}

string rearrangeString(const string &s) {
    int freq[256] = {0};

    for (char ch : s)
        freq[(unsigned char)ch]++;

    int maxFreq = 0;
    for (int i = 0; i < 256; i++)
        if (freq[i] > maxFreq)
            maxFreq = freq[i];

    if (maxFreq > (s.length() + 1) / 2)
        return "";

    return "Possible case but might vary";  
}


(Here, for "aaab" maxFreq = 3 > (4+1)/2 = 2 → return empty string)
/* --------------------------------------------------- */
input: "abcde"
output: "edcba"
(Reverse string)
/* --------------------------------------------------- */
PROGRAM 4
Input: "abcde"
Output: "edcba"

(Reverse entire string)

#include <iostream>
#include <string>
using namespace std;

string reverseString(string s) {
    int i = 0, j = s.length() - 1;
    while (i < j) {
        char temp = s[i];
        s[i] = s[j];
        s[j] = temp;
        i++;
        j--;
    }
    return s;
}

int main() {
    string s = "abcde";
    cout << reverseString(s);
    return 0;
}
/* --------------------------------------------------- */
input: "hello world"
output: "world hello"
(Reverse words in sentence)
/* --------------------------------------------------- */
PROGRAM 5
Input: "hello world"
Output: "world hello"

(Reverse words)

#include <iostream>
#include <string>
using namespace std;

string reverseWords(const string &s) {
    string result = "";
    string word = "";

    for (int i = 0; i <= s.length(); i++) {
        if (i == s.length() || s[i] == ' ') {

            if (result.length() == 0)
                result = word;
            else
                result = word + " " + result;

            word = "";
        } else {
            word += s[i];
        }
    }
    return result;
}

int main() {
    string s = "hello world";
    cout << reverseWords(s);
    return 0;
}

/* --------------------------------------------------- */

















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


/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */









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


/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */















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

/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */
/* ---------------------------------------------------------------------------------- */