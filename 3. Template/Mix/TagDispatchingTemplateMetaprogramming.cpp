✅ Tag Dispatching in C++ Template Metaprogramming
Tag dispatching is a technique where you call different function implementations based on a type tag, resolved at compile time, not runtime.
It is used to select an implementation using types, instead of using if or switch.

⭐ 1. Why Tag Dispatching?
Compile-time dispatch (zero runtime cost)
Choose a function implementation depending on types, traits, or integral constants
Avoids if constexpr when function overloading is more suitable

Used heavily in STL algorithms
(std::advance, std::distance, std::copy, std::fill…)

⭐ 2. Basic Idea
You determine a "tag type" using a trait.
Pass that tag to overloaded functions.
Compiler picks correct function using overload resolution.

⭐ 3. Simple Example
Step 1: Define tag types
struct fast_tag {};
struct slow_tag {};

Step 2: Trait to detect property
template<typename T>
struct is_fast : std::false_type {};

template<>
struct is_fast<int> : std::true_type {};

Step 3: Overloaded implementations
template<typename T>
void process_impl(T, fast_tag) {
    std::cout << "Fast implementation\n";
}

template<typename T>
void process_impl(T, slow_tag) {
    std::cout << "Slow implementation\n";
}

Step 4: Public API that dispatches
template<typename T>
void process(T x) {
    using tag = std::conditional_t<is_fast<T>::value, fast_tag, slow_tag>;
    process_impl(x, tag{});
}

Usage:
process(10);    // Fast implementation
process('A');   // Slow implementation

⭐ 4. Tag Dispatching in the STL
The STL uses tag dispatching to optimize algorithms based on iterator categories.
Example: std::advance
std::bidirectional_iterator_tag
std::random_access_iterator_tag
std::input_iterator_tag

The general public function:
template<class Iterator, class Distance>
void advance(Iterator& it, Distance n) {
    advance_impl(it, n, typename std::iterator_traits<Iterator>::iterator_category{});
}

The tag-dispatched implementations:
// Input iterator: only ++ allowed
template<class Iterator, class Distance>
void advance_impl(Iterator& it, Distance n, std::input_iterator_tag) {
    while(n-- > 0) ++it;
}

// Random-access iterator: can jump in O(1)
template<class Iterator, class Distance>
void advance_impl(Iterator& it, Distance n, std::random_access_iterator_tag) {
    it += n;
}

This makes std::advance both correct and optimal based on iterator type.

⭐ 5. How It Works Internally (Compile-Time Dispatch)
Tag is an empty struct, used only for overloading.
typename std::iterator_traits<Iterator>::iterator_category{}

Produces one of:
std::input_iterator_tag
std::bidirectional_iterator_tag
std::random_access_iterator_tag
The compiler selects the correct advance_impl overload.

⭐ 6. Tag Dispatch vs if constexpr
tag dispatch
Better for separating implementations cleanly
Used by the STL to avoid bloating APIs
Allows overload resolution to decide
if constexpr
Newer (C++17)
Simpler in many cases
Less template boilerplate

Example using if constexpr:
template<typename T>
void process(T x) {
    if constexpr (is_fast<T>::value)
        std::cout << "Fast\n";
    else
        std::cout << "Slow\n";
}

So why still use tag dispatching?
Necessary when you want a function to call itself recursively with different strategies.
Required when you want overload resolution not branching.
Used when working with type categories like iterators (STL).

⭐ 7. Dispatching on Integral Constants
You can dispatch on values too:

template<int N>
struct int_tag {};


Example:

template<int N>
void foo_impl(int_tag<0>) { 
    std::cout << "Base case\n"; 
}

template<int N>
void foo_impl(int_tag<N>) {
    foo_impl<N-1>(int_tag<N-1>{});
}


This compiles into pure static recursion.

⭐ 8. Real Example — Overload Based on Buffer Size
template<typename T>
void copy_impl(T* dst, const T* src, std::size_t n, std::true_type) {
    std::memcpy(dst, src, n * sizeof(T));
}

template<typename T>
void copy_impl(T* dst, const T* src, std::size_t n, std::false_type) {
    for (std::size_t i = 0; i < n; ++i)
        dst[i] = src[i];
}

template<typename T>
void dispatch_copy(T* dst, const T* src, std::size_t n) {
    using contiguous = std::is_trivially_copyable<T>;
    copy_impl(dst, src, n, contiguous{});
}

⭐ 9. Advantages of Tag Dispatching
| Feature                | Benefit                                |
| ---------------------- | -------------------------------------- |
| Compile-time selection | Zero runtime overhead                  |
| Clear separation       | Different logic in different functions |
| SFINAE friendly        | Works with partial specializations     |
| STL-friendly           | Matches `iterator_category` pattern    |




⭐ 10. When Should You Use Tag Dispatching?
Use it when:
Your API must have a uniform entry point but multiple strategies
Types naturally map to categories (tags)
You need overload resolution based on traits
You are designing STL-like generic code
You want to avoid mixing logic inside a big if constexpr