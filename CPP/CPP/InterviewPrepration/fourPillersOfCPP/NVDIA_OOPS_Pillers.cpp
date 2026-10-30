The 4 OOP Pillars in the NDAS C++ Project
NDAS is built almost entirely on these pillars — the CGF node model, the active-safety simulators, the planner checks, 
and the prediction predictors all lean on them. 

Real examples you'll find in the repo:
Pillar	                Real NDAS example
Encapsulation           Impact, SpeedLimiter-style classes, PIMPL nodes (m_ private members)
Abstraction             SharedObjectSimulationInterface, TrajectoryCheckBase, CGF Node base
Inheritance             SharedObjectSimulation final : public SharedObjectSimulationInterface, MockTrajectoryCheck : public TrajectoryCheckBase
Polymorphism            virtual process() on CGF nodes, prediction predictors, TrajectoryCheckBase virtual methods



1. Encapsulation — Data Bundling & Hiding
Definition: bundle data + the functions that operate on it into one class, and hide the internal state behind a controlled public interface. 
In NDAS this is enforced even by the coding standard: private members must use the m_ prefix (from .clang-tidy: PrivateMemberPrefix: m_).

How NDAS uses it: the active-safety Ego class hides steering/motion state and exposes only safe operations; the Impact class hides collision internals. 
State is never public — you go through methods.

// EgoState.hpp — encapsulation, NDAS style
class EgoState
{
public:
    void updateSpeed(float measured)
    {
        // controlled mutation: clamp to physical limits (invariant protected)
        m_speed = std::clamp(measured, 0.0f, MAX_SPEED);
    }

    float speed() const { return m_speed; }   // read-only accessor

private:
    static constexpr float MAX_SPEED = 70.0f;  // hidden constant
    float m_speed{0.0f};                        // hidden state (m_ prefix required)
    float m_yawRate{0.0f};
};

Why it matters in NDAS: external code can't set m_speed to an illegal value (e.g., negative or 200 m/s) — the invariant lives inside the class. 
This is critical for ASIL safety: state integrity is guaranteed at the boundary.


2. Abstraction — Complexity Hiding
Definition: expose what a component does, hide how. Achieved with abstract base classes / interfaces (pure virtual methods). 
The caller programs against the interface, not the implementation.

How NDAS uses it: the CGF Node base class defines a generic API (process(), passes, ports) so the runtime can drive any node without knowing its internals. 
Similarly SharedObjectSimulationInterface (real code) declares the simulation contract with a pure virtual interface:

class SharedObjectSimulation final : public SharedObjectSimulationInterface<ObjectSimulation>

An abstraction in NDAS style:
// IPredictor.hpp — an ABSTRACTION (interface)
class IPredictor
{
public:
    virtual ~IPredictor() = default;

    // WHAT it does — not HOW. Callers depend only on this.
    virtual Trajectory predict(const Agent& agent, float horizonSec) = 0;
};


The planner asks "give me a predicted trajectory" without caring whether it's a DNN, a dominant-lane heuristic, or a constant-velocity model. 
The complexity of each predictor is hidden behind IPredictor.




3. Inheritance — Code Reusability
Definition: a derived class reuses and extends a base class. NDAS uses this heavily for (a) sharing common machinery and (b) enabling mocks.

Real NDAS examples:

Simulators: a base simulator → kinematic → kinematic-point / vehicle simulator (from the active-safety common README).
Test doubles: MockTrajectoryCheck : public TrajectoryCheckBase — the mock inherits the real interface so it's substitutable.

// Base with shared behavior
class BaseSimulator
{
public:
    explicit BaseSimulator(float t0) : m_time(t0) {}
    float time() const { return m_time; }      // reused by all subclasses

protected:
    void advanceTime(float dt) { m_time += dt; }
    float m_time;
};

// Derived reuses BaseSimulator, adds a kinematic point model
class KinematicPointSimulator : public BaseSimulator
{
public:
    KinematicPointSimulator(float t0, float speed)
        : BaseSimulator(t0), m_speed(speed) {}

    void step(float dt)
    {
        m_position += m_speed * dt;   // new behavior
        advanceTime(dt);             // REUSED base functionality
    }
    float position() const { return m_position; }

private:
    float m_speed;
    float m_position{0.0f};
};

Why it matters in NDAS: the time-tracking, state interface, and bookkeeping are written once in the base and reused by every simulator 
(kinematic point, bicycle/vehicle model) used by AEB, AES, and BSM.



4. Polymorphism — Many Forms
Definition: the same call behaves differently depending on the actual object type. Achieved via virtual functions (runtime) and templates (compile-time). NDAS uses both.

How NDAS uses it:
Runtime polymorphism: the CGF runtime calls node->process() and each node type runs its own logic (prediction node vs planner node vs channel node). 
The Node Factory instantiates nodes by string name and returns them as Node*.

Prediction: the same predict() call dispatches to DNN, dominant-lane, or linear predictors (Multi-Predictor Fusion).



// Two predictors implementing the same interface differently
class DnnPredictor : public IPredictor
{
public:
    Trajectory predict(const Agent& a, float h) override
    {
        return runNeuralNet(a, h);       // learned, multi-modal
    }
};

class DominantLanePredictor : public IPredictor
{
public:
    Trajectory predict(const Agent& a, float h) override
    {
        return followLaneCenter(a, h);   // heuristic
    }
};

// Caller is polymorphic — one line, many forms:
void planAgainst(IPredictor& predictor, const Agent& agent)
{
    Trajectory t = predictor.predict(agent, 3.0f);  // dispatches to actual type
    // ... plan using t
}



The same predictor.predict(...) line runs the DNN or the heuristic depending on which object was passed — that's polymorphism, 
and it's exactly how Multi-Predictor Fusion swaps predictors per agent.


All 4 Pillars Together — one combined NDAS-style program
This mini "active-safety collision monitor" uses encapsulation, abstraction, inheritance, and polymorphism at once. 
It mirrors how NDAS structures AEB/AES with pluggable object simulators behind an interface.



#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>

// ---------------------------------------------------------------
// (2) ABSTRACTION: an interface defines WHAT a simulator provides,
//     not HOW. Callers depend only on this contract.
// ---------------------------------------------------------------
class IObjectSimulator
{
public:
    virtual ~IObjectSimulator() = default;
    virtual float distanceAfter(float dt) const = 0;   // predicted gap after dt seconds
    virtual const char* kind() const = 0;
};

// ---------------------------------------------------------------
// (3) INHERITANCE + (1) ENCAPSULATION:
//     BaseSimulator holds hidden state (m_) and shares helpers.
// ---------------------------------------------------------------
class BaseSimulator : public IObjectSimulator
{
public:
    BaseSimulator(float initialGap, float closingSpeed)
        : m_gap(initialGap), m_closingSpeed(closingSpeed) {}

protected:
    float projectGap(float dt) const           // reused by subclasses
    {
        return m_gap - m_closingSpeed * dt;    // simple projection
    }
    float m_gap;           // ENCAPSULATED state (hidden, m_ prefix)
    float m_closingSpeed;
};

// Constant-velocity model reuses BaseSimulator
class ConstVelSimulator : public BaseSimulator
{
public:
    using BaseSimulator::BaseSimulator;
    // (4) POLYMORPHISM: overrides the virtual contract
    float distanceAfter(float dt) const override { return projectGap(dt); }
    const char* kind() const override { return "ConstVel"; }
};

// Braking-object model reuses BaseSimulator but behaves differently
class BrakingSimulator : public BaseSimulator
{
public:
    BrakingSimulator(float gap, float closing, float decel)
        : BaseSimulator(gap, closing), m_decel(decel) {}

    // (4) POLYMORPHISM: same signature, different physics
    float distanceAfter(float dt) const override
    {
        // closing speed decreases as the object brakes
        float effectiveClosing = std::max(0.0f, m_closingSpeed - m_decel * dt);
        return m_gap - effectiveClosing * dt;
    }
    const char* kind() const override { return "Braking"; }

private:
    float m_decel;   // ENCAPSULATED extra state
};

// ---------------------------------------------------------------
// The monitor works purely through the ABSTRACTION (IObjectSimulator).
// It never knows the concrete type — POLYMORPHISM handles that.
// ---------------------------------------------------------------
class CollisionMonitor
{
public:
    explicit CollisionMonitor(float thresholdMeters) : m_threshold(thresholdMeters) {}

    bool willCollide(const IObjectSimulator& sim, float horizon) const
    {
        for (float t = 0.0f; t <= horizon; t += 0.5f)
        {
            if (sim.distanceAfter(t) < m_threshold)   // polymorphic dispatch
            {
                std::cout << "[" << sim.kind() << "] collision risk at t=" << t << "s\n";
                return true;
            }
        }
        return false;
    }

private:
    float m_threshold;   // ENCAPSULATED
};

int main()
{
    CollisionMonitor monitor(2.0f);   // brake if gap < 2 m

    // Store different concrete types behind the SAME interface pointer:
    std::vector<std::unique_ptr<IObjectSimulator>> objects;
    objects.push_back(std::make_unique<ConstVelSimulator>(20.0f, 8.0f));   // 20 m, 8 m/s closing
    objects.push_back(std::make_unique<BrakingSimulator>(20.0f, 8.0f, 3.0f)); // same, but braking

    for (const auto& obj : objects)
    {
        bool risk = monitor.willCollide(*obj, 4.0f);   // one call, many forms
        std::cout << obj->kind() << " -> "
                  << (risk ? "BRAKE" : "safe") << "\n\n";
    }
    return 0;
}




How each pillar shows up in that program
Pillar	                Where	                                                        What it achieves
Encapsulation           m_gap, m_closingSpeed, m_decel, m_threshold are private;        Internal state protected; invariants safe
                        accessed only via methods

Abstraction             IObjectSimulator defines distanceAfter() / kind() — the what    CollisionMonitor depends only on the interface, not implementations

Inheritance             ConstVelSimulator / BrakingSimulator derive from                Shared machinery written once
                        BaseSimulator and reuse projectGap()

Polymorphism            sim.distanceAfter(t) dispatches to the actual type;             Same code drives many object models — exactly like NDAS predictors/simulators
                        a vector<unique_ptr<IObjectSimulator>> holds mixed types



Expected output (conceptually):
ConstVel closes at a steady 8 m/s → hits the 2 m threshold → BRAKE.
Braking object decelerates, so the gap shrinks slower → may stay safe.
Same monitor.willCollide(...) call, different behavior per object = the payoff of combining all four pillars.


Summary
Encapsulation — bundle state + behavior, hide internals behind methods; NDAS enforces it down to the m_ naming rule (e.g., EgoState, Impact).
Abstraction — depend on interfaces (IPredictor, SharedObjectSimulationInterface, CGF Node) that expose what, not how.
Inheritance — reuse base machinery in derived classes (simulator hierarchy, MockTrajectoryCheck : public TrajectoryCheckBase).
Polymorphism — one call, many forms via virtual dispatch (CGF process(), prediction predictors, collision simulators) and templates.
The combined program shows a CollisionMonitor driving multiple simulator types through one interface — the same architecture NDAS uses for active safety and prediction.





vtable & vptr in C++ (with NDAS context)
The problem they solve
When you call a virtual function through a base pointer, C++ must decide at runtime which override to run:

IPredictor* p = getPredictor();   // could be DnnPredictor or DominantLanePredictor
p->predict(agent, 3.0f);          // which predict() runs? decided at RUNTIME
The compiler can't know the concrete type at compile time. The mechanism that resolves this is the vtable + vptr pair. This is called dynamic dispatch.

Definitions
vtable (virtual table): a per-class, compiler-generated, static array of function pointers — one entry per virtual function, pointing to the final override for that class. There is one vtable per polymorphic class (not per object).
vptr (virtual pointer): a per-object hidden pointer that the compiler injects as the first member of every polymorphic object. It points to its class's vtable.




How a virtual call actually works (step by step)
For p->predict(agent, 3.0f) the compiler generates roughly:

Read the vptr from the object p points to (it's at a fixed offset — usually offset 0).
Index into the vtable at the slot for predict (a fixed compile-time index, say slot 0).
Load the function pointer stored there.
Call it, passing p as the hidden this.
In pseudo-C it's like:

// p->predict(agent, 3.0f);  becomes:
(*(p->vptr[0]))(p, agent, 3.0f);

So a virtual call = one extra memory indirection (read vptr → read slot → call) compared to a normal direct call. That's the runtime cost of polymorphism.


Key facts (interview-ready)             
Question	                            Answer
One vtable per class or per object?     Per class
One vptr per class or per object?       Per object
When is the vptr set?                   In the constructor (base ctor sets it to base vtable, then derived ctor overwrites to derived vtable)
Where is the vptr stored?               Hidden member, typically first in the object → object size grows by one pointer
What creates a vtable?                  A class having at least one virtual function (incl. virtual destructor)
Compile-time or runtime binding?        Virtual = runtime (dynamic); non-virtual = compile-time (static)
Cost                                    One extra indirection per call + one pointer per object; usually prevents inlining


Why it matters in NDAS specifically
CGF Node dispatch: the runtime holds Node* pointers and calls process() / passes virtually — the vtable routes each call to the correct node type (prediction node, planner node, channel node). The Node Factory creates objects by string name and returns Node*; vtables make them behave correctly.
Pluggable algorithms: prediction predictors, active-safety simulators (SharedObjectSimulationInterface), planner checks (TrajectoryCheckBase) all use virtual dispatch.
gmock relies on it: MockTrajectoryCheck : public TrajectoryCheckBase works only because those methods are virtual — gmock swaps the vtable entries to its fakes.
Safety trade-off: virtual dispatch adds indirection and blocks inlining, and it needs the vptr to be correctly set — so in the hottest ASIL real-time loops NDAS sometimes prefers templates (compile-time polymorphism) instead. AUTOSAR C++14 also has rules about virtual functions (e.g., a base class with virtual functions must have a virtual destructor — you saw virtual ~...() = default; everywhere in the NDAS interfaces for exactly this reason).



Suitable program (NDAS-style: predictors behind a base class)
#include <iostream>
#include <memory>
#include <vector>

// Base polymorphic class -> gets a VTABLE because it has virtual functions.
class IPredictor
{
public:
    virtual ~IPredictor() = default;                 // virtual dtor -> vtable slot 0
    virtual float predict(float speed, float dt) = 0; // pure virtual -> vtable slot 1
    virtual const char* name() const = 0;
};

// Each derived class gets its OWN vtable with its overrides.
class DnnPredictor : public IPredictor
{
public:
    float predict(float speed, float dt) override
    {
        return speed * dt * 1.1f;   // pretend DNN adds a learned correction
    }
    const char* name() const override { return "DnnPredictor"; }
};

class LinearPredictor : public IPredictor
{
public:
    float predict(float speed, float dt) override
    {
        return speed * dt;          // constant-velocity
    }
    const char* name() const override { return "LinearPredictor"; }
};

int main()
{
    // Each object silently carries a vptr pointing to its class vtable.
    std::vector<std::unique_ptr<IPredictor>> predictors;
    predictors.push_back(std::make_unique<DnnPredictor>());
    predictors.push_back(std::make_unique<LinearPredictor>());

    for (const auto& p : predictors)
    {
        // Virtual call: read vptr -> vtable[predict slot] -> correct override.
        float dist = p->predict(20.0f, 3.0f);
        std::cout << p->name() << " predicted " << dist << " m\n";
    }

    // Proof of object growth from the vptr:
    std::cout << "sizeof(DnnPredictor) = " << sizeof(DnnPredictor) << " bytes "
              << "(includes the hidden vptr)\n";
    return 0;
}


What happens at runtime for p->predict(20.0f, 3.0f):

When the loop holds a DnnPredictor, its vptr points to the DnnPredictor vtable, whose predict slot points to DnnPredictor::predict → returns 66.0.
Next iteration holds a LinearPredictor, vptr → LinearPredictor vtable → LinearPredictor::predict → returns 60.0.
Same line of code, two different functions — resolved purely through vptr→vtable. That's dynamic dispatch.
sizeof(DnnPredictor) will be at least sizeof(void*) (8 bytes on a 64-bit build) even though it has no data members — that's the injected vptr.

Static (non-virtual) vs dynamic (virtual) — the contrast
struct A { void f() {} };          // no virtual -> NO vtable, NO vptr, sizeof == 1
struct B { virtual void f() {} };  // virtual   -> vtable created, vptr added, sizeof == 8

A::f() is bound at compile time (direct call, inlinable, zero overhead).
B::f() is bound at runtime via vtable (flexible, but one indirection).
This is exactly the trade-off NDAS weighs: virtual for extensible framework/plugin points (nodes, predictors, mocks), 
templates/non-virtual in the tightest safety-critical inner loops to avoid the indirection.

Summary
vtable = per-class table of function pointers to the correct virtual overrides; created when a class has ≥1 virtual function.
vptr = per-object hidden pointer (set in constructors) that points to its class's vtable; makes each object grow by one pointer.
How it works: a virtual call reads the object's vptr → indexes the vtable slot for that function → calls the stored pointer with this. One extra indirection = the cost of runtime polymorphism.
Role in NDAS: enables CGF Node dispatch, the Node Factory, pluggable predictors/simulators/planner-checks, and gmock mocks — all of which depend on virtual functions (and thus virtual destructors, per AUTOSAR). Where the indirection cost is unacceptable, NDAS uses compile-time polymorphism (templates) instead.


Advanced OOP in the NDAS C++ Project
flowchart TD
  P["4 Pillars (foundation)"] --> A["Abstract classes & pure-virtual interfaces"]
  A --> V["Virtual destructors & object lifetime"]
  V --> R["RAII & ownership (unique_ptr)"]
  R --> PI["PIMPL (compile firewall)"]
  PI --> RULE["Rule of 0/3/5 + move semantics"]
  RULE --> CC["Composition over inheritance"]
  CC --> STAT["Static polymorphism: templates & CRTP"]
  STAT --> PAT["Design patterns: Factory, Strategy, Singleton, NVI"]
  PAT --> SOLID["SOLID principles"]


1. Abstract Classes & Pure-Virtual Interfaces (the contract)
An abstract class has at least one pure virtual function (= 0) and cannot be instantiated. It defines a contract. 
NDAS uses these everywhere: SharedObjectSimulationInterface, TrajectoryCheckBase, IPredictor-style interfaces, CGF Node.

A real NDAS example even uses a pure virtual destructor (the strongest form of "you must derive from me"):
    virtual ~SharedObjectSimulationInterface() = 0;

// A pure interface (abstract). Note: a pure virtual dtor STILL needs a body.
class ISafetyCheck
{
public:
    virtual ~ISafetyCheck() = 0;                 // pure virtual dtor
    virtual bool check(const Trajectory& t) = 0; // contract: every check must implement this
};
inline ISafetyCheck::~ISafetyCheck() = default;  // required out-of-line definition

Why NDAS does this: it forces a stable, testable boundary. The planner monitor depends on ISafetyCheck, not on any concrete checker, 
so checks can be added/swapped/mocked without touching the caller.



2. Virtual Destructors & Object Lifetime (a safety must)
Rule: if you delete a derived object through a base pointer and the base destructor is not virtual, you get undefined behavior (the derived destructor never runs → resource leak). 
That's why every NDAS interface declares virtual ~X() = default; — you saw it in MockTrajectoryCheck, IObjectSimulator, etc. AUTOSAR C++14 mandates it.

class Node
{
public:
    virtual ~Node() = default;   // CRUCIAL: enables correct polymorphic deletion
    virtual void process() = 0;
};

class PredictionNode : public Node
{
public:
    ~PredictionNode() override { /* free GPU buffers, etc. */ }
    void process() override { /* ... */ }
};

void run()
{
    std::unique_ptr<Node> n = std::make_unique<PredictionNode>();
    n->process();
    // when n goes out of scope: ~PredictionNode() runs FIRST (because ~Node is virtual),
    // then ~Node(). Without virtual, only ~Node() would run -> leak.
}


3. RAII & Ownership — the backbone of NDAS resource safety
RAII (Resource Acquisition Is Initialization): tie a resource's lifetime to an object's scope. Acquire in the constructor, release in the destructor. No manual free/delete in safety code (which also satisfies the "no naked new/delete/malloc" coding rules you saw in .clang-tidy).

// RAII wrapper around a DriveWorks-style handle
class ScopedContext
{
public:
    ScopedContext() { dwInitialize(&m_handle); }   // acquire
    ~ScopedContext() { dwRelease(m_handle); }       // release automatically

    // ownership is unique: forbid copy (Rule of 5, see below)
    ScopedContext(const ScopedContext&) = delete;
    ScopedContext& operator=(const ScopedContext&) = delete;

    dwContextHandle_t get() const { return m_handle; }
private:
    dwContextHandle_t m_handle{};
};

void use()
{
    ScopedContext ctx;          // initialized here
    doWork(ctx.get());
}                               // released here automatically, even if doWork throws


Ownership with smart pointers (the NDAS norm): std::unique_ptr for exclusive ownership (you saw std::unique_ptr<IObjectSimulator> and mockedRailSelector), shared_ptr only when ownership is genuinely shared. Raw pointers/references are for non-owning access.


4. PIMPL Idiom (Pointer to IMPLementation)
NDAS CGF nodes use PIMPL (e.g., ExceptionSafeProcessNode) to hide implementation details behind a pointer. Benefits: compile firewall (change the impl without recompiling clients), stable ABI, and cleaner exception boundaries.

// Widget.hpp — the public header clients include
class Widget
{
public:
    Widget();
    ~Widget();                     // must be defined in .cpp (Impl is incomplete here)
    void doThing(int x);
private:
    class Impl;                    // forward declaration only
    std::unique_ptr<Impl> m_impl; // pointer to hidden implementation
};


// Widget.cpp — the hidden implementation
class Widget::Impl
{
public:
    void doThing(int x) { m_state += x; /* real logic + private members */ }
private:
    int m_state{0};
};

Widget::Widget() : m_impl(std::make_unique<Impl>()) {}
Widget::~Widget() = default;                        // here Impl is complete
void Widget::doThing(int x) { m_impl->doThing(x); }

Why NDAS cares: headers stay lightweight, private headers/types don't leak, and rebuild times drop across the monorepo. It also cleanly separates the exception-safe wrapper from the raw node logic.



5. Rule of 0 / 3 / 5 & Move Semantics
Rule of 3: if you define a destructor, copy ctor, or copy assignment, you probably need all three.
Rule of 5: in modern C++, add the move ctor and move assignment.
Rule of 0 (preferred in NDAS): design so you need none of them — let members (smart pointers, containers) manage themselves.

// Rule of 5: a class managing a unique resource
class Buffer
{
public:
    explicit Buffer(size_t n) : m_data(new float[n]), m_size(n) {}
    ~Buffer() { delete[] m_data; }                          // 1 dtor

    Buffer(const Buffer&) = delete;                          // 2 copy ctor (forbidden)
    Buffer& operator=(const Buffer&) = delete;               // 3 copy assign (forbidden)

    Buffer(Buffer&& o) noexcept                              // 4 move ctor
        : m_data(o.m_data), m_size(o.m_size) { o.m_data = nullptr; o.m_size = 0; }

    Buffer& operator=(Buffer&& o) noexcept                   // 5 move assign
    {
        if (this != &o) { delete[] m_data; m_data = o.m_data; m_size = o.m_size;
                          o.m_data = nullptr; o.m_size = 0; }
        return *this;
    }
private:
    float* m_data;
    size_t m_size;
};

// Rule of 0 (the NDAS-preferred version): no special members needed at all
class BufferR0
{
public:
    explicit BufferR0(size_t n) : m_data(n) {}
private:
    std::vector<float> m_data;   // vector already implements all 5 correctly
};

Move semantics matter in NDAS because per-frame data (trajectories, packets) should be moved, not copied, to hit real-time budgets. std::move transfers ownership cheaply.


6. Composition over Inheritance
Inheritance models "is-a"; composition models "has-a." NDAS prefers composition for reuse (inheritance is reserved for genuine interface/behavioral substitution). Deep inheritance trees are discouraged.

// Inheritance would be WRONG here: a Planner is not a Predictor.
// Composition is right: a Planner HAS-A predictor.
class BehaviorPlanner
{
public:
    explicit BehaviorPlanner(std::unique_ptr<IPredictor> predictor)
        : m_predictor(std::move(predictor)) {}

    Maneuver decide(const Scene& s)
    {
        auto futures = m_predictor->predict(s.leadAgent(), 3.0f);  // delegate
        return chooseManeuver(s, futures);
    }
private:
    std::unique_ptr<IPredictor> m_predictor;   // HAS-A (composition + abstraction)
};


This also gives you dependency injection: pass a real predictor in production, a mock in tests.

7. Static Polymorphism — Templates & CRTP
Virtual dispatch (vtable) costs an indirection. In hot ASIL loops NDAS often uses compile-time polymorphism via templates and CRTP (Curiously Recurring Template Pattern) — the CGF SimpleNodeT<Derived> and NodeConcept static introspection are examples.

// CRTP: base is templated on the derived type -> dispatch resolved at COMPILE time
template <typename Derived>
class NodeBase
{
public:
    void run()                       // no 'virtual' -> no vtable, inlinable
    {
        static_cast<Derived*>(this)->process();  // calls Derived::process directly
    }
};

class FastNode : public NodeBase<FastNode>
{
public:
    void process() { /* tight, inlined, zero indirection */ }
};

// Usage:
FastNode n;
n.run();   // compiles to a direct call to FastNode::process — no vptr lookup


	            Dynamic (virtual)	            Static (template/CRTP)
Binding         Runtime (vtable/vptr)           Compile time
Cost            Indirection, no inline          Zero overhead, inlinable
Flexibility     Swap types at runtime, mockable Fixed at compile time
NDAS use        Node Factory, predictors, mocks SimpleNodeT, NodeConcept, math kernels


8. Design Patterns used in NDAS
Factory (creational) — the CGF Node Factory
Creates objects by a runtime key (string name) and returns them via the base interface — pure polymorphism.

class NodeFactory
{
public:
    using Creator = std::function<std::unique_ptr<Node>()>;

    void registerNode(const std::string& name, Creator c) { m_creators[name] = std::move(c); }

    std::unique_ptr<Node> create(const std::string& name)   // returns Node* (polymorphic)
    {
        return m_creators.at(name)();
    }
private:
    std::map<std::string, Creator> m_creators;
};

// Registration (NDAS registers node types this way):
factory.registerNode("PredictionNode", []{ return std::make_unique<PredictionNode>(); });
auto node = factory.create("PredictionNode");   // built from a JSON descriptor string

This is exactly how CGF instantiates a graph described in .node.json/.graphlet.json files.

Strategy (behavioral) — pluggable predictors / checks
Encapsulate interchangeable algorithms behind an interface; select at runtime. That's IPredictor (DNN vs dominant-lane) and the planner's ISafetyCheck list — Multi-Predictor Fusion is essentially strategy selection per agent.



Singleton — the logger
NDAS uses a logger singleton (dwLogger, referenced across the active-safety README). One global access point, created once.

class Logger
{
public:
    static Logger& instance() { static Logger s; return s; }  // thread-safe since C++11
    void log(const char* msg) { /* ... */ }
private:
    Logger() = default;
};
// Logger::instance().log("AEB engaged");



Non-Virtual Interface (NVI)
Public non-virtual method wraps a private virtual "hook" — the base controls the algorithm skeleton; derived classes customize steps (Template Method flavor). Useful when the base must enforce pre/post checks around the customization point.

class Check
{
public:
    bool run(const Trajectory& t)      // public, NON-virtual: fixed skeleton
    {
        preValidate(t);
        bool r = doRun(t);             // the customizable step
        return postValidate(r);
    }
private:
    virtual bool doRun(const Trajectory&) = 0;   // derived customizes ONLY this
    void preValidate(const Trajectory&) {}
    bool postValidate(bool r) { return r; }
};


9. SOLID Principles (how NDAS structure reflects them)
Principle	            Meaning	                                    NDAS reflection
Single Responsibility   One class, one reason to change             Each software unit = one element (Prediction, Planner, AEB)
Open/Closed             Open to extension, closed to modification   Add a new IPredictor/Node without editing the runtime
Liskov Substitution     Subtypes must be substitutable for base     Any Node/IPredictor works wherever the base is expected (mocks too)
Interface Segregation   Small focused interfaces                    TrajectoryCheckBase has few, cohesive virtual methods
Dependency Inversion    Depend on abstractions, not concretions     Planner depends on IPredictor, not DnnPredictor



Capstone Program — putting the advanced concepts together
A small "planner pipeline" using abstraction, RAII, composition, strategy, factory, move semantics, virtual destructors, and dependency injection — the shape of real NDAS code.

#include <iostream>
#include <map>
#include <memory>
#include <functional>
#include <vector>
#include <string>

// ---------- Abstraction: strategy interface (with virtual dtor) ----------
struct Trajectory { float risk; };

class IPredictor
{
public:
    virtual ~IPredictor() = default;                  // virtual dtor: safe polymorphic delete
    virtual Trajectory predict(float speed) const = 0; // strategy contract
    virtual const char* name() const = 0;
};

// ---------- Two concrete strategies ----------
class DnnPredictor : public IPredictor
{
public:
    Trajectory predict(float speed) const override { return { speed * 0.05f }; }
    const char* name() const override { return "Dnn"; }
};
class LinearPredictor : public IPredictor
{
public:
    Trajectory predict(float speed) const override { return { speed * 0.02f }; }
    const char* name() const override { return "Linear"; }
};

// ---------- Factory: build strategies by name (like the CGF Node Factory) ----------
class PredictorFactory
{
public:
    using Creator = std::function<std::unique_ptr<IPredictor>()>;
    void reg(const std::string& key, Creator c) { m_map[key] = std::move(c); }
    std::unique_ptr<IPredictor> create(const std::string& key) const { return m_map.at(key)(); }
private:
    std::map<std::string, Creator> m_map;
};

// ---------- Composition + Dependency Injection: planner HAS-A predictor ----------
class Planner
{
public:
    explicit Planner(std::unique_ptr<IPredictor> p) : m_predictor(std::move(p)) {} // move ownership

    std::string decide(float egoSpeed) const
    {
        const Trajectory t = m_predictor->predict(egoSpeed);   // polymorphic call
        const bool brake = t.risk > 1.0f;
        return std::string(m_predictor->name()) + " -> " + (brake ? "BRAKE" : "GO");
    }
private:
    std::unique_ptr<IPredictor> m_predictor;   // RAII: auto-released; Rule of 0
};

int main()
{
    PredictorFactory factory;
    factory.reg("Dnn",    []{ return std::make_unique<DnnPredictor>(); });
    factory.reg("Linear", []{ return std::make_unique<LinearPredictor>(); });

    // Build planners with different injected strategies (Open/Closed + DI):
    std::vector<Planner> planners;
    planners.emplace_back(factory.create("Dnn"));
    planners.emplace_back(factory.create("Linear"));

    for (const auto& planner : planners)
    {
        std::cout << planner.decide(30.0f) << "\n";
    }
    // All unique_ptrs auto-release here (RAII); ~IPredictor virtual -> correct dtor runs.
    return 0;
}


Concepts exercised in that one program:

Concept	                        Where
Abstraction / pure virtual      IPredictor
Virtual destructor              virtual ~IPredictor() = default;
Polymorphism                    m_predictor->predict(...), name()
Strategy pattern                interchangeable DnnPredictor / LinearPredictor
Factory pattern                 PredictorFactory::create("Dnn")
Composition + DI                Planner holds an injected IPredictor
RAII + ownership                unique_ptr members auto-release
Move semantics                  std::move(p), emplace_back
Rule of 0                       Planner/predictors need no manual special members
Open/Closed + LSP               add a new predictor without touching Planner

Summary  
-> Beyond the four pillars, NDAS-grade C++ leans on: abstract interfaces (with virtual destructors), RAII + smart-pointer ownership (no naked new/delete), PIMPL compile firewalls, Rule of 0/3/5 + move semantics, composition over inheritance, and static polymorphism (templates/CRTP) where the vtable cost is unacceptable.
-> The recurring design patterns are Factory (CGF Node Factory), Strategy (predictors/checks), Singleton (logger), and NVI, all organized around SOLID.
-> The capstone program shows how these combine into the same extensible, testable, real-time-safe structure NDAS uses for its node/predictor/planner architecture.
