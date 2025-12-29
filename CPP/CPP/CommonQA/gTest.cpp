/* ---------------------------------------------- */
✔ Difference between EXPECT_* and ASSERT_*
✔ When to use fixtures vs parameterized tests
✔ Why death tests fork processes
✔ Should private functions be tested
✔ Why test order must not matter
/* -----------------OR---------------------------- */
✔ EXPECT vs ASSERT → continue vs stop
✔ Fixture → shared setup
✔ Parameterized → same logic, many inputs
✔ Death tests → fork to isolate crashes
✔ Private functions → test via public interface
✔ Test order → must never matter

/* --------------------------------------------- */

1️⃣ EXPECT_* vs ASSERT_*
🔹 Core Difference
| Aspect     | EXPECT_*               | ASSERT_*                       |
| ---------- | ---------------------- | ------------------------------ |
| On failure | Test continues         | Test **stops immediately**     |
| Use when   | Failure is recoverable | Failure makes rest meaningless |
| Severity   | Non-fatal              | Fatal                          |

✅ Example: EXPECT_* (non-fatal)
TEST(MathTest, ExpectExample) {
    int x = 10;
    int y = 0;

    EXPECT_EQ(x, 10);     // failure continues test
    EXPECT_NE(y, 1);      // still runs
    EXPECT_EQ(x / 2, 5);  // executes
}
✔ Even if one EXPECT fails, remaining checks execute.

❌ Example: ASSERT_* (fatal)
TEST(MathTest, AssertExample) {
    int* ptr = nullptr;

    ASSERT_NE(ptr, nullptr);  // if fails → STOP test
    *ptr = 10;                // would crash if ASSERT not used
}
✔ Prevents undefined behavior.

🎯 Interview Rule
ASSERT_ for prerequisites, EXPECT_ for validations**






2️⃣ Fixtures vs Parameterized Tests
🔹 Test Fixtures (TEST_F)
When to use
✔ Shared setup / teardown
✔ Complex object lifecycle
✔ Resource management (files, DB, sockets)

Example: Fixture
class VectorFixture : public ::testing::Test {
  protected:
    std::vector<int> v;

    void SetUp() override {
        v = {1, 2, 3};
    }
};

TEST_F(VectorFixture, SizeTest) {
    EXPECT_EQ(v.size(), 3);
}

TEST_F(VectorFixture, PushBackTest) {
    v.push_back(4);
    EXPECT_EQ(v.size(), 4);
}
✔ Same setup reused automatically.

🔹 Parameterized Tests (TEST_P)
When to use
✔ Same logic
✔ Different inputs
✔ Data-driven testing

Example: Parameterized Test
class EvenTest : public ::testing::TestWithParam<int> {};

TEST_P(EvenTest, IsEven) {
    int value = GetParam();
    EXPECT_EQ(value % 2, 0);
}

INSTANTIATE_TEST_SUITE_P(
    EvenNumbers,
    EvenTest,
    ::testing::Values(2, 4, 6, 8)
);
✔ One test, many inputs.

🎯 Interview Rule
| Use           | When                    |
| ------------- | ----------------------- |
| Fixture       | Shared state / setup    |
| Parameterized | Same logic, many values |




3️⃣ Why Death Tests Fork Processes
🔥 What is a Death Test?
Tests that verify a program terminates intentionally.
EXPECT_DEATH(code, "message");

Example
void crash() {
    int* p = nullptr;
    *p = 10;   // segfault
}

TEST(DeathTest, Segfault) {
    EXPECT_DEATH(crash(), "");
}

❓ Why fork?
✔ Because:
Segmentation faults
abort()
exit()
would kill the test runner itself

🧠 Mechanism
Parent Process
   |
   +-- fork() → Child executes crash
                   |
                   +-- dies
   |
Parent checks exit signal

✔ Test framework survives
✔ Crash is isolated

🎯 Interview Answer
Death tests fork to isolate crashes and protect the test runner.







4️⃣ Should Private Functions Be Tested?
❌ Short Answer
No, not directly.
✔ Correct Approach
Test public behavior, not private implementation.

❌ Bad Practice
class Calculator {
  private:
    int add(int a, int b) { return a + b; }
};

❌ Exposing or friending tests just to test add().
✅ Correct Practice
class Calculator {
  public:
    int compute() {
        return add(2, 3);
    }
  private:
    int add(int a, int b) {
        return a + b;
    }
};

TEST(CalcTest, Compute) {
    Calculator c;
    EXPECT_EQ(c.compute(), 5);
}
✔ Private logic tested indirectly.

⚠ Exception (Rare)
Highly complex algorithms
Legacy systems
Use FRIEND_TEST cautiously

class A {
    FRIEND_TEST(ATest, PrivateTest);
  private:
    int secret() { return 42; }
};

🎯 Interview Rule
Test what the user sees, not how it works internally.





5️⃣ Why Test Order Must Not Matter
❗ Problem
int counter = 0;

TEST(OrderTest, First) {
    counter++;
    EXPECT_EQ(counter, 1);
}

TEST(OrderTest, Second) {
    EXPECT_EQ(counter, 0);  // ❌ fails if First runs first
}

🔥 Why this is bad
Tests may run in any order
Parallel execution
Flaky tests
CI failures

✅ Correct Way (Isolation)
TEST(OrderTest, First) {
    int counter = 0;
    counter++;
    EXPECT_EQ(counter, 1);
}

TEST(OrderTest, Second) {
    int counter = 0;
    EXPECT_EQ(counter, 0);
}

🧠 GoogleTest Guarantees
❌ Order not guaranteed
✔ Each test must be independent

🎯 Interview One-Liner
Tests must be independent, repeatable, and order-agnostic.







INTERVIEW GOLDEN ANSWER
Private members should not be tested directly.
They should be validated via public interfaces.
If private logic is complex, refactor it into a separate class and test it independently.










/* ========================================================================================= */
//g++ test.cpp add.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest

Why order of -lgtest -lgtest_main matters
Static vs shared gTest linking
How CMake avoids this error automatically
Common gTest linker interview traps




1️⃣ Why the order of -lgtest -lgtest_main matters
🔑 Core rule (C/C++ linker rule)
The linker processes libraries from LEFT → RIGHT, only once.
It does NOT go back to earlier libraries to resolve symbols.

🧠 What symbols are involved?
libgtest.a
→ contains testing framework code

libgtest_main.a
→ contains main(), which depends on gtest symbols

So:
gtest_main  --->  gtest
   (uses)         (defines)

❌ WRONG ORDER (classic bug)
g++ test.cpp calc.cpp -lgtest_main -lgtest -lpthread

What happens internally
->Linker sees -lgtest_main:
  .Needs symbols from gtest
->gtest not yet seen → unresolved
->Linker does NOT retry later ❌

💥 Results in:
undefined reference to testing::InitGoogleTest

✅ CORRECT ORDER
g++ test.cpp calc.cpp -lgtest -lgtest_main -lpthread

Why this works
-lgtest loaded first → symbols available
-lgtest_main loaded next → main() resolved

🎯 Interview one-liner
Library order matters because the linker resolves symbols in a single left-to-right pass.




2️⃣ Static vs Shared gTest linking
🔹 Static linking (.a)
-lgtest -lgtest_main
(Usually /usr/lib/libgtest.a)

Characteristics
✅ Everything copied into executable
✅ No runtime dependency
❌ Larger binary
❌ Must link -lpthread manually

Common errors
Missing symbols
Wrong order
Multiple definitions if linked twice


🔹 Shared linking (.so)
-lgtest -lgtest_main
(But system uses /usr/lib/libgtest.so)

Characteristics
✅ Smaller binary
✅ Faster link time
✅ Runtime loader resolves dependencies
❌ Requires library at runtime

🧠 Why static causes MORE linker errors?
Static linker:
Resolves everything at build time
Order matters strictly
Missing symbols = failure

Shared linker:
Can defer symbol resolution to runtime
More forgiving

🎯 Interview answer
Static linking is stricter and more sensitive to library order, while shared linking defers symbol resolution to runtime.








3️⃣ How CMake avoids this error automatically
This is where CMake shines.
❌ Manual g++ (error-prone)
g++ test.cpp calc.cpp -lgtest -lgtest_main -lpthread

You must:
Know order
Know pthread
Know include paths

✅ CMake way (modern)
find_package(GTest REQUIRED)

add_executable(my_tests
    calculator_test.cpp
    calculator.cpp
)

target_link_libraries(my_tests
    GTest::gtest_main
)

🧠 What CMake does for you
✔ Correct library order
✔ Adds pthread automatically
✔ Adds include paths
✔ Handles static/shared internally

Internally it expands to something like:
-lgtest -lgtest_main -lpthread
(in the correct order)

🎯 Interview one-liner
CMake uses imported targets like GTest::gtest_main which encapsulate correct dependencies and link order.






4️⃣ Common gTest linker interview traps (VERY IMPORTANT)
🔥 Trap 1: Missing main()
-lgtest   ❌

Error:
undefined reference to main

✅ Fix:
-lgtest_main

OR provide your own main()



🔥 Trap 2: Double main() definition
// test_main.cpp
int main() { ... }

-lgtest_main

💥 Error:
multiple definition of main

✅ Fix:
Either custom main
Or gtest_main, not both




🔥 Trap 3: Forgetting -lpthread
-lgtest -lgtest_main

💥 Error:
undefined reference to pthread_create

✅ Fix:
-lpthread

(CMake does this automatically)



🔥 Trap 4: Wrong library order
-lgtest_main -lgtest   ❌

💥 Unresolved gtest symbols
🔥 Trap 5: Mixing static & shared
Linking:
static libgtest.a
shared libpthread.so

Can cause:
ABI issues
duplicate symbols


🔥 Trap 6: Header found, library missing
fatal error: gtest/gtest.h: No such file

or

cannot find -lgtest

Cause:
Headers installed
Libraries not installed

🧠 MASTER INTERVIEW SUMMARY (MEMORIZE)
Library order matters because the linker resolves symbols left-to-right
gtest_main depends on gtest, so -lgtest must come first
Static linking is stricter than shared
CMake avoids these issues using imported targets
Most gTest linker errors come from missing main(), wrong order, or missing pthread