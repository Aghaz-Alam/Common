/* ---------------------------------------------- */
✔ Difference between EXPECT_* and ASSERT_*
✔ When to use fixtures vs parameterized tests
✔ Why death tests fork processes
✔ Should private functions be tested
✔ Why test order must not matter
/* --------------------------------------------- */
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