/* 
Question 24 : Event Dispatcher (Callbacks, function pointers, lambdas)

Problem: Implement an EventDispatcher class that allows registering callbacks for named events.

Requirements / Features:
Support registering callbacks: free functions, lambdas, std::function<void(const std::string& payload)>.
Allow multiple callbacks per event name.
emit(eventName, payload) calls all callbacks in order. Ensure exception in one callback does not stop others (catch and continue).
Provide unsubscribe by callback id.
Extra: Show example using std::bind to bind member functions.

Sample: Register two callbacks for "onData", emit "onData","hello". Both should run.
*/


//EventDispatcher Implementation
#include <iostream>
#include <unordered_map>
#include <vector>
#include <functional>
#include <string>
#include <stdexcept>

class EventDispatcher {
public:
    using Callback = std::function<void(const std::string&)>;

private:
    struct CallbackEntry {
        int id;
        Callback func;
    };

    std::unordered_map<std::string, std::vector<CallbackEntry>> listeners;
    int nextId = 1;

public:
    // Register a callback, returns an ID for later unsubscription
    int subscribe(const std::string& eventName, Callback cb) {
        int id = nextId++;
        listeners[eventName].push_back({id, cb});
        return id;
    }

    // Unsubscribe a callback by ID
    bool unsubscribe(const std::string& eventName, int id) {
        auto& vec = listeners[eventName];
        for (auto it = vec.begin(); it != vec.end(); ++it) {
            if (it->id == id) {
                vec.erase(it);
                return true;
            }
        }
        return false;
    }

    // Emit an event: call all callbacks for that event
    void emit(const std::string& eventName, const std::string& payload) {
        if (!listeners.count(eventName)) return;

        for (auto& entry : listeners[eventName]) {
            try {
                entry.func(payload);
            }
            catch (const std::exception& e) {
                std::cerr << "Callback exception: " << e.what() << "\n";
            }
            catch (...) {
                std::cerr << "Unknown exception in callback\n";
            }
        }
    }
};
//Demonstration
// Free function callback
void freeFunctionCallback(const std::string& msg) {
    std::cout << "[Free Function] Received: " << msg << "\n";
}

// Class for member function callback
class Handler {
public:
    void memberCallback(const std::string& msg) {
        std::cout << "[Member Function] Message: " << msg << "\n";
    }
};

int main() {
    EventDispatcher dispatcher;

    Handler h;

    // Register free function
    int id1 = dispatcher.subscribe("onData", freeFunctionCallback);

    // Register lambda
    int id2 = dispatcher.subscribe("onData",
        [](const std::string& msg){
            std::cout << "[Lambda] Got: " << msg << "\n";
        }
    );

    // Register member function using std::bind
    int id3 = dispatcher.subscribe("onData",
        std::bind(&Handler::memberCallback, &h, std::placeholders::_1)
    );

    std::cout << "--- Emit 'onData' with payload 'hello' ---\n";
    dispatcher.emit("onData", "hello");

    // Unsubscribe the lambda
    dispatcher.unsubscribe("onData", id2);

    std::cout << "--- Emit 'onData' again with payload 'world' ---\n";
    dispatcher.emit("onData", "world");

    return 0;
}
/* 
Sample Output:
--- Emit 'onData' with payload 'hello' ---
[Free Function] Received: hello
[Lambda] Got: hello
[Member Function] Message: hello
--- Emit 'onData' again with payload 'world' ---
[Free Function] Received: world
[Member Function] Message: world
*/