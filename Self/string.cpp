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
using namespace std;✅ Valid Examples (should return true):
{}

{{}}

{{}{}}

❌ Invalid Examples (should return false):
}{

{{}

{}}{

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


1. Reverse a string

Input: "hello"
Output: "olleh"

Approach: Two-pointer swap / built-in reverse.

2. Check if a string is a palindrome

Input: "madam" → True
Input: "hello" → False

3. First non-repeating character

Input: "aabbcddee"
Output: c

Use frequency array (O(n)).

4. Check if two strings are anagrams

Input: "listen", "silent" → True
Sort or use count[26].

5. Remove duplicate characters

Input: "banana"
Output: "ban"

6. Count vowels & consonants

Input: "Interview"
Output: vowels = 4, consonants = 5

7. Longest substring without repeating characters

Input: "abcabcbb"
Output: 3 ("abc")

Sliding window + hash map.

8. Longest common prefix (LCP)

Input: {"flower", "flow", "flight"}
Output: "fl"

9. Longest palindromic substring

Input: "babad"
Output: "bab" or "aba"

Expand from center.

10. Valid parentheses

Input: "({[]})" → Valid
Use stack.

11. String compression

Input: "aaabbc"
Output: "a3b2c"

12. Check rotation

Input: "waterbottle", "erbottlewat" → True
Check if s2 is substring of s1+s1.

13. Count number of words

Input: "I love programming"
Output: 3

14. Remove all spaces

Input: "a b c"
Output: "abc"

15. Frequency of characters

Input: "mississippi"
Output: {m:1,i:4,s:4,p:2}



/* ---------------------------------------------- */
//advance
🔥 1. Longest Palindromic Substring — O(n) Manacher’s Algorithm

Classic DP solution is O(n²). Interviewers ask for O(n).

🔥 2. Longest Palindromic Subsequence — DP + Memoization

LPS ≠ LPSUBSTRING.

🔥 3. Longest Duplicate Substring — Suffix Array + LCP / Rolling Hash + Binary Search

LeetCode Hard.
Find longest repeating substring.

🔥 4. Count Distinct Substrings — Suffix Automaton (SAM)

Count all substrings efficiently in O(n).

🔥 5. Smallest Window Substring (Minimum Window Substring)

Given S and T, find smallest substring of S containing all chars of T.
Uses sliding window with freq map.

🔥 6. Z-Algorithm problems

Examples:

Search pattern in string

Count number of pattern occurrences

Find longest prefix which is also a suffix

🔥 7. KMP Pattern Search + Prefix Function Applications

Advanced usage:

Find periodicity

Remove all pattern occurrences

Longest border of a string

🔥 8. String to Integer with Edge Cases — Automata Based

This is the DFA approach to atoi.

🔥 9. Edit Distance / Levenshtein Distance (DP)

Insert/delete/replace.

🔥 10. Word Break with dictionary — DP + Trie optimized

Hard variant: return all possible segmentations.

🔥 11. Longest Common Substring — DP or Rolling Hash

O(n²) or O(n log n) with binary search + hash.

🔥 12. Wildcard Matching / Regex Matching — DP

Supports ? and *.

🔥 13. Find all anagram indices in a string

Sliding window + hash map.

🔥 14. Build smallest lexicographic string by removing characters (Greedy + Stack)

Same as removing k digits.

🔥 15. Group strings by isomorphic structure

Hard:
foo, app → same pattern (0,1,1)

🔥 16. Substring queries using Suffix Array

Given multiple queries, check if a substring exists in O(log n).

🔥 17. Rabin-Karp with rolling hash (single or double hash)

Used for:

Duplicate substring detection

Substring matching

Hash-based compression

🔥 18. Minimum characters to add in front to make palindrome

Use KMP on S + '#' + reverse(S).

🔥 19. Lexicographically smallest rotation — Booth’s Algorithm

Find min rotation in O(n).

🔥 20. Compare version numbers (advanced rules)

v1 = “1.01.00013”, v2 = “1.1.13” → equal.

🔥 21. Find K-th character in recursively defined string

Some companies ask:

S1 = "a"
Sn = Sn-1 + chr(n + 'a' - 1) + Sn-1


Find K-th char in huge string (without building).

🔥 22. Longest substring where each char appears at least k times

Divide & conquer approach.

🔥 23. Serialize & Deserialize list of strings

Design problem in distributed systems.

🔥 24. Minimum Palindrome Cuts (Palindrome Partitioning)

DP:
O(n²) preprocessing + O(n²) DP.

🔥 25. Find repeated DNA sequences

Length = 10, sliding window + rolling hash.




//Intermediate
1. Reverse words in a string
Input: "the sky is blue"
Output: "blue is sky the"
/* ============================================== */
2. Check if two strings are anagrams (case insensitive)
Example: "Dormitory" and "Dirty room"
/* ============================================== */
3. Remove all adjacent duplicate characters
Input: "abbaca"
Output: "ca"
Use stack logic.
/* ============================================== */
4. Find the first non-repeating character in a string
Input: "swiss" → 'w'
/* ============================================== */
5. Longest common prefix (LCP) among array of strings
Input: ["flower","flow","flight"] → "fl"
/* ============================================== */
6. Check if string is rotation of another
Input: s1 = "abcde", s2 = "cdeab" → True
Use s1 + s1 trick.
/* ============================================== */
7. Implement strStr() (find substring)
Like C++ find()
Input: "hello", "ll" → 2
Can use brute-force or KMP.
/* ============================================== */
8. Maximum occurring character
Input: "bbacccddddee" → 'd'
/* ============================================== */
9. Count number of words
Input: "Hello world this is cpp" → Output: 5
/* ============================================== */
10. Capitalize first letter of every word
Input: "hello world"
Output: "Hello World"
/* ============================================== */
11. Valid palindrome with punctuation removed
Input: "A man, a plan, a canal: Panama" → True
Ignore case & special chars.
/* ============================================== */
12. Remove characters from first string present in second
Input: s1 = "battle", s2 = "ae"
Output: "bttl"
/* ============================================== */
13. Check if one string is an anagram of substring of another
Input: s1 = "ab", s2 = "eidbaooo" → True
Sliding window.
/* ============================================== */
14. Find all permutations of a string
Input: "abc" → abc, acb, bac, bca, cab, cba
Backtracking.
/* ============================================== */
15. Compress string (basic run-length encoding)
Input: "aaabbc" → "a3b2c1"
/* ============================================== */
16. Word break (simple version)
Check if string can be segmented using dictionary words.
/* ============================================== */
17. Length of longest substring with unique characters
Input: "pwwkew" → 3 ("wke")
Sliding window.
/* ============================================== */
18. Reverse only vowels in a string
Input: "hello" → "holle"
Two-pointer.
/* ============================================== */
19. Check if strings follow same pattern
Pattern: "abba", String: "dog cat cat dog" → True

/* ============================================== */
20. Remove duplicates without using extra space
Input: "banana" → "ban"
(O(n²) solution expected)
/* ============================================== */




/* ------------------------------------------------------------- */
input: "aabbccc"
output: false
(Frequencies: a=2, b=2, c=3 → duplicate)
as occurence are mixed
 

/* ============================================== */

Input: nums = [12,10,10,30,12,12]
Output: true

Input: nums = [12,10, 12, 10]
Output: false
 
if occurance are unique print true else false
 
/* ============================================== */

Input: nums = [0,10,0,30,12]
Output: [10,30,12,0,0]
move zeros at the end and non-zeros as it is
 
/* ============================================== */

✔ Input: "triangle", "integral"
✔ Output: true 
check anagram
 

/* ============================================== */
✅ Input:
   prices = {1, 2, 5, 9, 11};
 
✅ Expected Output:
   Max Profit: 10
(Buy at 1 on Day 1, sell at 11 on Day 5 → Profit = 11 - 1 = 10)
 

/* ============================================== */

✅ Valid Examples (should return true):
{}
{{}}
{{}{}}

❌ Invalid Examples (should return false):
}{
{{}
{}}{
 


// Method 1
#include <iostream>
using namespace std;
bool isValid(const string &s) {
    int count = 0;

    for(char c : s) {
        if(c == '{') {
            count++;
        } else if(c == '}') {
            // A closing bracket cannot appear before an opening one
            if(count == 0) return false;
            count--;
        }
    }

    // All opened brackets must be closed
    return count == 0;
}

int main() {
    string s;
    cin >> s;

    cout << (isValid(s) ? "true" : "false") << endl;
    return 0;
}



//Method 2
#include <iostream>
#include <stack>
using namespace std;

bool isValid(const string &s) {
    stack<char> st;

    for (char c : s) {
        if (c == '{') {
            st.push(c);
        } 
        else if (c == '}') {
            // Cannot close when nothing is open
            if (st.empty()) return false;
            st.pop();
        }
    }

    // All opened brackets should be matched
    return st.empty();
}

int main() {
    string s;
    cin >> s;

    cout << (isValid(s) ? "true" : "false") << endl;
    return 0;
}


//Balance Bracket
#include <iostream>
#include <stack>
#include <string>
using namespace std;
// Function to check if brackets are balanced
bool isBalanced(const string &s) {
    stack<char> st;
    for (char ch : s) {
        // If opening bracket, push to stack
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        }
        // If closing bracket, check for matching opening bracket
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (st.empty()) return false; // No matching opening
            char top = st.top();
            st.pop();
            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
              return false;
            }
        }
    }
    // Stack should be empty if balanced
    return st.empty();
}
int main() {
    string expr;
    cout << "Enter expression: ";
    cin >> expr;
    if (isBalanced(expr))
        cout << "Balanced\n";
    else
        cout << "Not Balanced\n";

    return 0;
}
/*
Enter expression: (){}[]
Balanced
*/


























/* ============================================== */

input: "abcabc"
output: "acbacb"
(Reorder string in alternate pattern)


/* ============================================== */

Reverse words in a string
Input: "the sky is blue"
Output: "blue is sky the"
 
//Method 1 — Using stringstream (simple and clear)
#include <bits/stdc++.h>
using namespace std;

string reverseWords(string s) {
    stringstream ss(s);
    vector<string> words;
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    reverse(words.begin(), words.end());

    string result;
    for (int i = 0; i < words.size(); i++) {
        if (i > 0) result += " ";
        result += words[i];
    }
    return result;
}

int main() {
    string s = "the sky is blue";
    cout << reverseWords(s) << endl;
}



//Method 2 — In-place reverse (optimal, no extra vector)
#include <bits/stdc++.h>
using namespace std;

string reverseWords(string s) {
    // remove extra spaces
    int n = s.size(), i = 0;
    while (i < n && s[i] == ' ') i++;
    string t;

    while (i < n) {
        if (s[i] != ' ') {
            t += s[i++];
        } else {
            t += ' ';
            while (i < n && s[i] == ' ') i++; // skip extra spaces
        }
    }

    // trim trailing space
    if (!t.empty() && t.back() == ' ') t.pop_back();

    // reverse entire string
    reverse(t.begin(), t.end());

    // reverse each word
    int start = 0;
    for (int j = 0; j <= t.size(); j++) {
        if (j == t.size() || t[j] == ' ') {
            reverse(t.begin() + start, t.begin() + j);
            start = j + 1;
        }
    }
    return t;
}

int main() {
    string s = "the sky is blue";
    cout << reverseWords(s) << endl;
}



//Method 3:
#include <iostream>
#include <string>
using namespace std;

string reverseWords(const string &s) {
    string result = "";
    int n = s.size();
    int i = n - 1;

    while (i >= 0) {
        // Skip spaces
        while (i >= 0 && s[i] == ' ')
            i--;
        if (i < 0) break;

        // Find the end of the word
        int j = i;
        while (j >= 0 && s[j] != ' ')
            j--;

        // Append the word to result
        if (!result.empty())
            result += " ";
        for (int k = j + 1; k <= i; k++)
            result += s[k];

        i = j - 1;
    }

    return result;
}

int main() {
    string input = "the sky is blue";
    cout << reverseWords(input) << endl;
    return 0;
}

























/* ============================================== */
input: "aaabb"
output: "ababa"
(Rearranged to avoid adjacent same letters or Rearrange so no two adjacent characters are the same
 

//Method: 1
#include <bits/stdc++.h>
using namespace std;
string rearrangeString(string s) {
    unordered_map<char, int> freq;
    for (char c : s) freq[c]++;

    // Max heap storing pair(freq, char)
    priority_queue<pair<int, char>> pq;

    for (auto &p : freq) 
        pq.push({p.second, p.first});

    string result = "";
    pair<int, char> prev = {-1, '#'}; // previous used char

    while (!pq.empty()) {
        auto curr = pq.top(); 
        pq.pop();

        result += curr.second;
        curr.first--;

        // push previous back if still left
        if (prev.first > 0)
            pq.push(prev);

        // update prev to current
        prev = curr;
    }

    // If result length is not same, it's not possible
    if (result.size() != s.size())
        return "Not Possible";

    return result;
}

int main() {
    string s = "aaabb";
    cout << rearrangeString(s) << endl;
    return 0;
}



//Method 2:
#include <bits/stdc++.h>
using namespace std;

string rearrangeString(string s) {
    unordered_map<char,int> f;
    for(char c : s) f[c]++;

    priority_queue<pair<int,char>> pq;
    for(auto &p : f) pq.push({p.second, p.first});

    string res = "";
    auto prev = make_pair(0, '#');

    while(!pq.empty()) {
        auto [cnt, ch] = pq.top(); pq.pop();
        res += ch;
        cnt--;

        if(prev.first > 0) pq.push(prev);
        prev = {cnt, ch};
    }
    return res.size() == s.size() ? res : "Not Possible";
}

int main() {
    cout << rearrangeString("aaabb");
}



//Method 3: 
#include <bits/stdc++.h>
using namespace std;

string rearrangeString(string s) {
    vector<int> freq(26, 0);
    for(char c : s) freq[c - 'a']++;

    int n = s.size();
    int maxFreq = *max_element(freq.begin(), freq.end());
    
    // Impossible if a char appears more than (n+1)/2 times
    if(maxFreq > (n + 1) / 2) return "Not Possible";

    string res(n, ' ');
    int idx = 0;

    // 1. Fill even indices first with the most frequent chars
    for(int i = 0; i < 26; i++) {
        while(freq[i] > 0 && idx < n) {
            res[idx] = char(i + 'a');
            freq[i]--;
            idx += 2;
        }
    }

    // 2. Fill odd indices
    idx = 1;
    for(int i = 0; i < 26; i++) {
        while(freq[i] > 0 && idx < n) {
            res[idx] = char(i + 'a');
            freq[i]--;
            idx += 2;
        }
    }

    return res;
}

int main() {
    cout << rearrangeString("aaabb") << endl;
}



//Method 4:
#include <bits/stdc++.h>
using namespace std;

string rearrangeString(string s) {
    unordered_map<char,int> freq;
    for(char c : s) freq[c]++;

    int n = s.size();

    // check max frequency
    int maxFreq = 0;
    for(auto &p : freq) maxFreq = max(maxFreq, p.second);

    if(maxFreq > (n + 1) / 2) return "Not Possible";

    // result vector
    vector<char> res(n, ' ');

    // place characters
    int idx = 0;

    // fill even positions first
    for(auto &p : freq) {
        char ch = p.first;
        int count = p.second;

        while(count > 0 && idx < n) {
            res[idx] = ch;
            idx += 2;
            count--;
        }
        freq[ch] = count; // update leftover count
    }

    // fill odd positions
    idx = 1;
    for(auto &p : freq) {
        char ch = p.first;
        int count = p.second;

        while(count > 0 && idx < n) {
            res[idx] = ch;
            idx += 2;
            count--;
        }
        freq[ch] = count;
    }

    // convert vector to string
    return string(res.begin(), res.end());
}

int main() {
    cout << rearrangeString("aaabb") << endl;
}

/* ------------------------------------------------------------- */