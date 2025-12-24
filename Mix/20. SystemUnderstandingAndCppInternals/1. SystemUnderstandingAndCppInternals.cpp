1. What is heap ?
2. What is stack trace ? what element / pointer used to represent stack.
3. what concepts in c++ can be used for better memeory management
4. explain std move. how std move is implemented underneath.
5. design patterns and anti design patterns
6. design principles, SOLID
7. advanatages of using smart pointers



1. What is a Heap?
The heap is a region of a computer’s memory that is used for dynamic memory allocation. 
It is where objects or data are allocated and deallocated during runtime, and it operates differently than the stack.

Memory Allocation: In the heap, memory is allocated dynamically at runtime using operations like malloc (in C) or new (in C++). 
Unlike the stack, which has a predetermined size, the heap can grow and shrink as needed.

Access: The heap allows more flexible memory allocation compared to the stack. 
Objects in the heap can be accessed directly, and their lifetime is managed by the programmer (through explicit allocation and deallocation) 
or automatically by garbage collection (in languages like Java and Python).


Characteristics of Heap Memory:
It is slower than the stack because memory allocation and deallocation in the heap require more complex bookkeeping.

The lifetime of data in the heap is determined by when it is explicitly freed by the programmer (in languages like C/C++) or by the garbage collector.

The heap can be fragmented over time, leading to inefficient memory usage if memory is not managed properly.



Heap vs Stack:
The stack is used for storing local variables and function call information, and its memory is automatically managed.

The heap, on the other hand, stores data that needs to persist across function calls and can be managed more manually, 
offering more flexibility but requiring careful memory management.





















5. design patterns and anti design patterns
Common Anti-Design Patterns in C++

Here are some well-known anti-design patterns in C++ that you should avoid:
/* --------------------------------------------------------------------------------------------- */
1. God Object (God Class)

Problem: A God Object is a class that knows too much or does too many things. 
It becomes a "catch-all" for multiple functionalities that should be spread across different objects.

Symptoms:
Large, monolithic classes with many responsibilities.
Low cohesion and high coupling between various parts of the class.
Difficult to understand, test, or maintain.

Example:
class GodObject {
  public:
    void manageUser() { /* User management */ }
    void manageOrder() { /* Order management */ }
    void sendEmail() { /* Email sending logic */ }
    void processPayment() { /* Payment processing */ }
    void generateReport() { /* Report generation */ }
};

Why it is bad: The class is responsible for too many things, making it hard to maintain and understand. 
Any change in the system might require a modification in this class.

Solution: Break the functionality into smaller, more specialized classes following the Single Responsibility Principle.
/* --------------------------------------------------------------------------------------------- */
2. Spaghetti Code

Problem: Spaghetti code is a tangled, unstructured codebase where the flow of control is difficult to follow due to excessive interdependencies and a lack of modularity. This usually happens when code lacks proper structure and organization.

Symptoms:
Lack of modularization.
Excessive use of global variables.
No separation of concerns.
Hard to maintain or extend.

Example:
// Example of Spaghetti Code
void process() {
    if (userLoggedIn) {
        processUserDetails();
        sendEmail();
    } else {
        showError();
    }
}
void processUserDetails() {
    // code here
}
void sendEmail() {
    // code here
}
void showError() {
    // code here
}


Why it is bad: The lack of clea/* --------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------- */
/* --------------------------------------------------------------------------------------------- */r structure means that making changes to one part of the system can break other parts, 
leading to bugs, and the code becomes difficult to maintain and debug.

Solution: Use modularization, separation of concerns, and clear function boundaries. 
Make use of functions and classes that logically group related operations together.

/* --------------------------------------------------------------------------------------------- */

3. Duplicated Code

Problem: Duplicated code occurs when the same or similar code is copied in multiple places within the codebase, 
violating the Do not Repeat Yourself (DRY) principle.

Symptoms:
Multiple functions or methods with identical or nearly identical logic.
Maintaining the same logic in many places, which increases the risk of inconsistencies and bugs.

Example:
// Example of Duplicated Code
void processOrder1() {
    if (orderTotal > 100) {
        discount = orderTotal * 0.1;
    }
    // ... Other code
}

void processOrder2() {
    if (orderTotal > 100) {
        discount = orderTotal * 0.1;
    }
    // ... Other code
}

Why it is bad: Every time you need to change the discount logic, you have to modify multiple places in the code, 
increasing the chance of errors and inconsistencies.

Solution: Refactor the common logic into a single function or method that can be reused across the codebase. 
This improves maintainability and reduces the chances of bugs.

/* --------------------------------------------------------------------------------------------- */
4. Tight Coupling

Problem: Tight coupling occurs when classes, functions, or components are too dependent on each other. 
Changes in one class may require changes in many other classes, making the codebase harder to maintain and extend.

Symptoms:
Classes that are heavily dependent on one another, making it difficult to change one without breaking others.
Difficulty in testing and maintaining the system.

class User {
  public:
    void setAddress(Address address) {
        // directly works with Address object
        this->address = address;
    }
  private:
    Address address;
};
class Address {
  public:
    std::string city;
    std::string street;
    // More address properties
};


Why it us bad: The User class is tightly coupled to the Address class. 
If the structure of Address changes, the User class might need to change as well, leading to a lot of interdependencies and a fragile codebase.

Solution: Use dependency injection, interfaces, or abstract classes to decouple components. 
This makes the system more flexible and easier to maintain.
/* --------------------------------------------------------------------------------------------- */
5. Large Functions/Methods

Problem: Large functions or methods perform too many operations, making them hard to understand and maintain. 
They violate the Single Responsibility Principle (SRP).

Symptoms:
Functions that do too many things, making them difficult to debug and test.
Lack of clarity in what the function actually does.

Example:
// Large Function Anti-pattern
void processTransaction() {
    // Step 1: Validate the transaction
    // Step 2: Deduct the amount from the account
    // Step 3: Generate the receipt
    // Step 4: Send an email to the user
    // Step 5: Log the transaction
}


Why it is bad: The function does too much and is likely to be modified in multiple places if any part of it changes. 
It is difficult to understand, test, or modify.

Solution: Break the function into smaller, more focused functions that each do one thing. This improves readability and maintainability.


/* --------------------------------------------------------------------------------------------- */

6. Global Variables
Problem: Global variables are accessible from anywhere in the code, leading to dependencies that are hard to track. 
Overuse of global variables creates tight coupling and makes the program state difficult to manage.

Symptoms:
Variables that are accessible from many parts of the program, making it difficult to understand where they are modified.
Hard-to-debug errors due to unexpected modifications of global state.

Example:
// Example of using Global Variable
int globalCounter = 0;
void incrementCounter() {
    globalCounter++;
}
void resetCounter() {
    globalCounter = 0;
}


Why it is bad: Since the global variable is accessible from anywhere, any function can modify it, 
leading to unpredictable behaviors and bugs. This makes the system fragile and hard to test.

Solution: Minimize the use of global variables. If necessary, encapsulate them within classes or pass them as parameters.

/* --------------------------------------------------------------------------------------------- */
Summary of Anti-Design Patterns in C++:
| **Anti-Pattern**     | **Problem**                                                                  | **Solution**                                                    |
| -------------------- | ---------------------------------------------------------------------------- | --------------------------------------------------------------- |
| **God Object**       | A class that handles too many responsibilities.                              | Break down the class into smaller, specialized classes.         |
| **Spaghetti Code**   | Unstructured, tangled code with poor modularization.                         | Modularize and follow principles like separation of concerns.   |
| **Duplicated Code**  | Repetitive code spread across the project.                                   | Refactor common logic into reusable functions or classes.       |
| **Tight Coupling**   | Strong dependencies between classes making changes hard to implement.        | Use dependency injection, interfaces, and abstraction.          |
| **Large Functions**  | Functions that do too many things, reducing readability and maintainability. | Split large functions into smaller, single-responsibility ones. |
| **Global Variables** | Variables that can be accessed and modified from anywhere.                   | Minimize use of global variables, encapsulate them.             |
| **Lazy Programmer**  | Ignoring edge cases and writing shortcuts that lead to bugs.                 | Always handle edge cases and write proper, comprehensive code.  |

/* --------------------------------------------------------------------------------------------- */



