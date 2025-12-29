✅ Why use = default for ctor and dtor?
1. It tells the compiler to generate the default implementation
Instead of writing:
Vehicle() noexcept { }
~Vehicle() noexcept { }

you explicitly ask the compiler to generate them:
Vehicle() noexcept = default;
virtual ~Vehicle() noexcept = default;
It is cleaner, shorter, and avoids accidental mistakes.



✅ 2. It keeps the type trivially constructible / trivially destructible
If you manually write an empty constructor/destructor:
Vehicle() noexcept {}
~Vehicle() noexcept {}

→ They are not trivial anymore.
This affects performance and allows certain optimizations.

Using = default keeps triviality when possible:
Vehicle() noexcept = default;   // trivial if all members are trivial

Trivial constructors/destructors allow:
faster runtime
zero-cost initialization
POD-like behavior
better optimization by the compiler



✅ 3. It communicates clear intent
Using = default means:
“I intentionally want the default behavior.”
Writing an empty body may confuse future developers:
“Was this intentionally empty or a mistake?”




✅ 4. For virtual destructors: avoids unnecessary vtable code
If you write:
virtual ~Vehicle() noexcept {}

This forces the compiler to generate a non-trivial destructor,
even if the class has nothing to destroy.

Using:
virtual ~Vehicle() noexcept = default;
keeps the destructor trivial (if possible) → more efficient.