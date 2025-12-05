1) Function template (generic) — C++11+

#include <iostream>
template<typename T>
void print(T x) { 
    std::cout << x << '\n'; 
}
int main() {
    print(1);
    print(3.14);
    print("hi");
}
/* 
Output
1
3.14
hi
*/



2) Class template (generic)

#include <iostream>
template<typename T>
class Box {
    T v;
  public:
    Box(T x): v(x) {}
    void show() const { std::cout << v << '\n'; }
};
int main() {
    Box<int> b{5};
    Box<const char*> s{"hello"};
    b.show(); s.show();
}
/* 
Output
5
hello
*/

3) Variable template — C++14+

#include <iostream>
template<typename T> constexpr T pi = T(3.14159265358979323846);
int main() {
    std::cout << pi<double> << '\n';
}
/* 
Output
3.14159...  (full double precision printed by your runtime)
*/


4) Template parameter pack (variadic templates) — C++11+

#include <iostream>
template<typename... Args>
void showAll(Args... args){
    (void)std::initializer_list<int>{(std::cout << args << ' ', 0)...};
    std::cout << '\n';
}
int main(){
    showAll(1, 2, "three", 4.5);
}
/* 
Output
1 2 three 4.5 
*/


5) Non-type template parameter

#include <iostream>
template<int N>
void repeat() {
    for (int i=0;i<N;++i) std::cout << i << ' ';
    std::cout << '\n';
}
int main() {
    repeat<3>();
}
/* 
Output
0 1 2 
*/


6) Template alias (using) — convenience

#include <vector>
#include <iostream>
template<typename T> using Vec = std::vector<T>;
int main(){
    Vec<int> v{1,2,3};
    for(auto x:v) std::cout<<x<<' ';
    std::cout<<'\n';
}
/* 
Output
1 2 3 
*/


7) Full specialization (function template)

#include <iostream>
template<typename T>
void f(T){ 
    std::cout << "generic\n"; 
}
template<>
void f<int>(int){ 
    std::cout << "int specialization\n"; 
}
int main(){
    f(1);
    f(3.14);
}
/* 
Output
int specialization
generic
*/



8) Class template partial specialization (pointer)

#include <iostream>
template<typename T>
struct Wrap {
    static void info() { std::cout << "generic\n"; }
};
template<typename T>
struct Wrap<T*> {
    static void info() { std::cout << "pointer\n"; }
};
int main(){
    Wrap<int>::info();
    Wrap<int*>::info();
}
/* 
Output
generic
pointer
*/

9) SFINAE (enable_if) — select only integral overloads — C++11+

#include <type_traits>
#include <iostream>
template<typename T>
typename std::enable_if<std::is_integral<T>::value>::type process(T){
    std::cout << "integral\n";
}
int main(){
    process(10);
    // process(3.14); // would be a substitution failure -> overload removed
}
/* 
Output
integral
*/


10) Concepts (requires) — C++20

// compile with -std=c++20
#include <concepts>
#include <iostream>
template<std::integral T>
void show(T x){ 
    std::cout << "integral: " << x << '\n'; 
}
int main(){
    show(5);
}
/* 
Output
integral: 5
*/


11) CRTP (static polymorphism)

#include <iostream>
template<typename Derived>
class Base {
  public:
    void call() { static_cast<Derived*>(this)->impl(); }
};
class A : public Base<A> { public: void impl() { std::cout << "A\n"; } };
class B : public Base<B> { public: void impl() { std::cout << "B\n"; } };
int main(){
    A a; B b;
    a.call();
    b.call();
}
/* 
Output
A
B
*/


12) std::variant + std::visit (type-safe sum type) — C++17+

#include <variant>
#include <iostream>
struct C { void draw(){ std::cout << "Circle\n"; } };
struct S { void draw(){ std::cout << "Square\n"; } };
int main(){
    std::variant<C,S> shape = C{};
    std::visit([](auto& s){ s.draw(); }, shape);
    shape = S{};
    std::visit([](auto& s){ s.draw(); }, shape);
}
/* 
Output
Circle
Square
*/

13) Virtual functions (dynamic polymorphism)

#include <iostream>
class Shape {
  public:
    virtual void draw() const = 0;
    virtual ~Shape() = default;
};
class Circle : public Shape { public: void draw() const override { std::cout << "Circle\n"; } };
class Square : public Shape { public: void draw() const override { std::cout << "Square\n"; } };
int main(){
    Shape* s1 = new Circle();
    Shape* s2 = new Square();
    s1->draw();
    s2->draw();
    delete s1; delete s2;
}
/* 
Output
Circle
Square
*/


14) Covariant return types (clone pattern)

#include <iostream>
class Base {
  public:
    virtual Base* clone() const { return new Base(*this); }
    virtual void who(){ std::cout << "Base\n"; }
    virtual ~Base() = default;
};
class Derived : public Base {
  public:
    Derived* clone() const override { return new Derived(*this); } // covariant
    void who() override { std::cout << "Derived\n"; }
};
int main(){
    Base* b = new Derived();
    Base* copy = b->clone();
    copy->who();
    delete b; delete copy;
}
/* 
Output
Derived
*/


15) Type erasure with std::function

#include <functional>
#include <iostream>
int main(){
    std::function<void()> f;
    f = [](){ std::cout << "Lambda 1\n"; };
    f();
    f = [](){ std::cout << "Lambda 2\n"; };
    f();
}
/* 
Output
Lambda 1
Lambda 2
*/


16) RAII — File wrapper (resource management)

#include <cstdio>
#include <iostream>
class File {
    FILE* f;
  public:
    File(const char* n) : f(std::fopen(n,"w")) {}
    ~File(){ if(f) std::fclose(f); }
    void write(const char* s){ if(f) std::fputs(s, f); }
};
int main(){
    File F("tmp.txt");
    F.write("hello\n");
    std::cout << "wrote to tmp.txt\n";
}
/* 
Output
wrote to tmp.txt
(file tmp.txt contains "hello")
*/



17) Smart pointers — unique_ptr, shared_ptr
#include <memory>
#include <iostream>
int main(){
    auto up = std::make_unique<int>(42);
    std::shared_ptr<int> sp = std::make_shared<int>(7);
    std::weak_ptr<int> wp = sp;
    std::cout << *up << ' ' << *sp << '\n';
}
/* 
Output
42 7
*/



18) Move constructor (move semantics)

#include <iostream>
#include <utility>
#include <vector>
struct S {
    std::vector<int> data;
    S(){ data = {1,2,3}; }
    S(S&& o) noexcept : data(std::move(o.data)) { std::cout << "moved\n"; }
};
int main(){
    S a;
    S b = std::move(a); // move ctor
    for(int x:b.data) std::cout<<x<<' ';
    std::cout<<'\n';
}
/* 
Output
moved
1 2 3 
*/



19) Perfect forwarding

#include <utility>
#include <iostream>
void foo(int&){ 
    std::cout << "lvalue\n"; 
}
void foo(int&&){ 
    std::cout << "rvalue\n"; 
}
template<typename T>
void call(T&& x) { 
    foo(std::forward<T>(x)); 
}
int main(){
    int a=0;
    call(a);        // lvalue
    call(5);        // rvalue
}
/* 
Output
lvalue
rvalue
*/


20) std::thread + std::mutex

#include <thread>
#include <mutex>
#include <iostream>
std::mutex m;
int counter = 0;
void inc(){
    for(int i=0;i<1000;i++){
        std::lock_guard<std::mutex> lk(m);
        ++counter;
    }
}
int main(){
    std::thread t1(inc), t2(inc);
    t1.join(); t2.join();
    std::cout << counter << '\n';
}
/* 
Output
2000
*/

21) std::atomic

#include <atomic>
#include <thread>
#include <iostream>
std::atomic<int> cnt{0};
void inc(){ 
    for(int i=0;i<1000;i++) ++cnt; 
}
int main(){
    std::thread a(inc), b(inc);
    a.join(); b.join();
    std::cout << cnt << '\n';
}
/* 
Output
2000
*/


22) std::async / future

#include <future>
#include <iostream>
int main(){
    auto f = std::async(std::launch::async, [](){ return 7; });
    std::cout << f.get() << '\n';
}
/* 
Output
7
*/


23) constexpr compute & static_assert — compile-time

#include <iostream>
constexpr int fib(int n){ 
    return n<2 ? n : fib(n-1)+fib(n-2); 
}
static_assert(fib(5)==5, "fib wrong");
int main(){ 
    std::cout << fib(6) << '\n'; 
}
/* 
Output
8
*/

24) std::span (view into sequence) — C++20

// compile with -std=c++20
#include <span>
#include <vector>
#include <iostream>
void print(std::span<int> s){
    for(int x:s) std::cout<<x<<' ';
    std::cout<<'\n';
}
int main(){
    std::vector<int> v{1,2,3,4};
    print(v);
}
/* 
Output
1 2 3 4 
*/



25) std::filesystem — path and listing — C++17+

// compile with -std=c++17
#include <filesystem>
#include <iostream>
int main(){
    std::cout << "Current path: " << std::filesystem::current_path() << '\n';
}
/* 
Output (example)
Current path: /home/user/project
*/
