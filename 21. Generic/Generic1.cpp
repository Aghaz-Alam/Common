Generic
------------
1. Gtest, coverity
2. Usage of git , gerrit
3. static, dyn libs, executables.
4. Debugging - gdb, using tools like addr2line, nm, readelf etc
5. Given a program identify what UT can be written, what all does it cover ( boundary conditions etc)



✅ 1. GTest & Coverity
GoogleTest (GTest/GMock)
GTest is the standard C++ unit testing framework used in most production codebases.

✔ Key Concepts
a) Test Cases & Fixtures
class MyFixture : public ::testing::Test {
  protected:
    void SetUp() override { counter = 10; }
    int counter;
};
TEST_F(MyFixture, IncrementTest) {
    counter++;
    ASSERT_EQ(counter, 11);
}

b) Mocking with GMock
Useful for interface-based testing & dependency injection.
class DB {
  public:
    virtual int read() = 0;
};
class MockDB : public DB {
  public:
    MOCK_METHOD(int, read, (), (override));
};
TEST(DBTest, TestRead) {
    MockDB db;
    EXPECT_CALL(db, read()).WillOnce(Return(10));
    EXPECT_EQ(db.read(), 10);
}

✔ What GTest Helps Cover
Boundary values
Error/exception paths
API behaviour
Integration between modules using mocks
Multi-threaded behavior (limited)




Coverity (Static Analysis Tool)
Coverity scans C/C++ code for static bugs, without executing it.

✔ Catchable Issues
Null dereference
Use-after-free
Buffer overflow
Double delete
Memory leaks
Uninitialized variables
API misuse
Concurrency races (limited)

✔ Integration
Often plugged into CI (Jenkins/GitHub Actions/Gerrit hooks)
Generates reports
Developers fix “defects” and push patches












/* -------------------------------------------------- */

✅ 2. Git & Gerrit (Code Reviews in C++ Projects)
Git: Used for Version Control

Typical workflow in a C++ product company:

✔ Feature Branch Workflow
git checkout -b feature/logging
git add .
git commit -m “Add logging to FileHandler”
git push origin HEAD:refs/for/master  # For Gerrit

Gerrit: Code Review System
Gerrit integrates tightly with Git for controlled merges.

✔ Workflow
Developer pushes patch → Gerrit
Reviewers review code
Comments added (style, logic, memory management, performance)
Developer rebases, updates patchset
CI runs GTest, coverage, static analysis
After approval (+2) patch gets merged

✔ Why Gerrit?
Enforces code review before merge
Patchsets maintain version of changes
Automated integration with Jenkins, Coverity & testing


/* -------------------------------------------------- */
✅ 3. Static Libraries, Dynamic Libraries, Executables
Static Library .a
Code copied into executable at link-time
Larger binary
Faster load time
No runtime dependency
Used for: low-level utilities, small embedded projects

Build
g++ -c math.cpp
ar rcs libmath.a math.o

Dynamic Library .so / .dll
Loaded at runtime
Smaller executables
Can patch bugs without rebuilding everything
ABI compatibility becomes important

Build
g++ -fPIC -shared math.cpp -o libmath.so

Executable

Built by linking:
object files
static libs
dynamic libs
g++ main.cpp -L. -lmath -o app

✔ How this relates to C++ projects?
Modular architecture
Plugins using .so
Binary size optimization
Faster CI/CD builds


/* ----------------------------------- */
✅ 4. Debugging (gdb, addr2line, nm, readelf)
GDB (Runtime Debugging)
Most widely used debugger for C++.

Basic workflow:
g++ -g main.cpp -o app
gdb ./app
run
bt        # backtrace
frame 2
p variable
break foo.cpp:20
continue

addr2line (Convert Address → Source Line)
Used when you only have a crash log with addresses.
addr2line -e app 0x400abc

Helps debug production crashes.
nm (List Symbols)
nm app | grep MyClass

Shows:
symbol names
mangled C++ names
symbols from static libs
Useful for linking issues.
readelf
Used to inspect ELF binary details.

Examples:
readelf -h app         # header
readelf -s app         # symbol table
readelf -d app         # dynamic section
readelf -r app         # relocations


Essential for debugging:
dynamic loading
symbol resolution
version mismatch of .so files


/* ------------------------------------------ */
✅ 5. Given a C++ Program → Identify Unit Tests
Typical Interview Scenario
You are given a function:

int divide(int a, int b) {
    if (b == 0) throw std::invalid_argument("zero");
    return a / b;
}

✔ What UTs Should Cover?
| Test Type           | Cases                          |
| ------------------- | ------------------------------ |
| **Normal**          | divide(10,2)=5                 |
| **Negative inputs** | divide(-10, 2), divide(10, -2) |
| **Both negative**   | divide(-10,-2)=5               |
| **Boundary**        | INT_MAX/1, INT_MIN/1           |
| **Error path**      | divide(10,0) → throws          |
| **Performance**     | large loops (optional)         |



Example GTest for Above
TEST(DivideTest, Normal) {
    EXPECT_EQ(divide(10,2), 5);
}

TEST(DivideTest, NegativeInputs) {
    EXPECT_EQ(divide(-10,2), -5);
}

TEST(DivideTest, ThrowsOnZero) {
    EXPECT_THROW(divide(10,0), std::invalid_argument);
}

✔ What Interviewers Expect You to Explain
When asked:
“Given this C++ code, what UTs can be written?”

You must cover:
1. Boundary Conditions
INT_MAX
INT_MIN
Zero
Null pointers
Empty strings
Vector empty/non-empty

2. Error/Exception Handling
Throw cases
Invalid parameters
Out-of-range
Memory errors (unique_ptr passed as null)

3. Happy Path
Normal expected behaviour.

4. Integration Paths
When the function depends on:
interfaces
network
DB
→ Use Mocks


/* ------------------------------------ */
5. Internal State & Side Effects
If objects modify state, test it.

✅ Full Summary (Interview Ready)
If they ask:
“Explain all these concepts in C++ in detail.”
You can reply with this structured outline:

🚀 Short, Crisp Answer (For Interviews)
GTest:
Used for unit testing in C++. Supports assertions, fixtures, parameterized tests & mocking with GMock.

Coverity:
Static analysis tool to detect memory errors, UAF, leaks, concurrency issues. Integrated into CI.

Git+Gerrit:
Git for version control; Gerrit for code reviews with patchsets, CI verification, pre-merge validation.

Static/Dynamic Libraries:
Static libs (.a) included at link time; dynamic libs (.so) loaded at runtime. Executables link against these.

Debugging Tools:
gdb → runtime debugging
addr2line → convert crash addresses to file:line
nm → view symbols
readelf → inspect ELF binary, dynamic sections

Unit Testing From Code:
Identify:
boundary cases
error paths
dependencies (mock them)
normal logic
integration behaviour