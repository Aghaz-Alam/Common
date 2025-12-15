Compilation Process in C++
The compilation of a C++ program happens in 4 major phases:
Source Code (.cpp)
     ↓
1. Preprocessing
     ↓
2. Compilation
     ↓
3. Assembly
     ↓
4. Linking
     ↓
Executable (.exe / a.out)

/* --------------------------------------------------------------------------------------------- */
Compilation Steps and Their Tasks
1. Preprocessing
   Task Performed:
    ->Handles preprocessor directives such as:
        -#include - inserts header file contents
            -->Inserts the entire contents of header files into the source.
            -->Allows the compiler to see library function declarations.
        -#define - macro substitution
            -->Performs macro substitution.
            -->Replaces symbolic names with actual values or code snippets.
        -Conditional compilation (#ifdef, #ifndef, #endif, #else)
            -->Includes or excludes parts of code depending on conditions.
            -->Helps create platform-dependent or feature-specific builds.
    ->Removes all comments
        -Both single-line (//) and multi-line (/* */) are removed.
        -Helps create cleaner input for the compiler.
    ->Expands macros functions
        -Example: #define SQR(x) ((x)*(x)) expands wherever it is used.
    ->Converts trigraphs (if any)
        -Rare now, but ??= → #, etc.
    ->Outputs a raw expanded code file
        -No parsing or type checking yet—just textual substitution.
    ->Produces a cleaned and expanded version of the source
   Output: Preprocessed source code (usually a.i file)





/* -------------------------------------------- */
1. Preprocessing (cpp)
   Preprocessor handles:
   -->#include → Copies header files into source code
   -->#define / Macros → Macro expansion
   -->Removing comments
   -->Conditional compilation (#ifdef, #ifndef)
   ✔ Output: Preprocessed source file (.i file)
   
   -->Example:
   #include <iostream>
   #define PI 3.14
   int main() {
     std::cout << PI;
   }
   Preprocessor expands PI → 3.14 and inserts full <iostream> content.

   View only preprocessing
   Command: g++ -E example.cpp -o example.i


/* 
In g++, the option -E stands for:
-E = Preprocess only

What it does
-> Runs only the C++ preprocessor
-> Stops before compilation
-> Produces the source after macro expansion, header inclusion, and conditional compilation
-> No object file, no assembly, no linking — just preprocessing.
*/
/* ============================================================================================= */
✅ 2. Compilation
      Task Performed:
        ->Converts preprocessed code into assembly-level instructions
        ->Includes the following internal phases:
            -Lexical Analysis - breaks code into tokens
                -->Breaks the input text into tokens (keywords, identifiers, literals).            
                -->Removes extra whitespace.
                -->Creates a token stream for the parser.
            -Syntax Analysis - checks grammar and builds parse tree
                -->Checks whether tokens follow the grammar rules of the language.
                -->Builds a parse tree (syntax tree).
                -->Detects missing brackets, invalid statements, etc.
            -Semantic Analysis - type checking, scope checking
                -->Checks the meaning of the syntax:
                    -Variable declarations
                    -Type compatibility (e.g., int vs float)
                    -Function parameter matching
                    -Scope checking (whether identifiers exist)
                -->Uses a symbol table to track all variables, types, etc.
            -Intermediate Code Generation - generates IR (like 3-address code)
                -->Converts AST into a machine-independent form:
                    -3-Address Code (TAC)
                    -Control Flow Graphs (CFG)
                    -Static Single Assignment (SSA)
                -->Makes optimization easier.
            -Optimization - removes dead code, improves speed
                -->Performs various optimizations:
                    -Constant folding: 3 + 5 → 8
                    -Dead code removal: eliminates unreachable or unused code
                    -Loop optimization: moves invariant code outside loops
                    -Strength reduction: replace costly operations (e.g., i*2 → i<<1)
            -Assembly Code Generation - converts IR to target CPU assembly
                -->Converts IR into CPU-specific assembly instructions.
                -->Allocates registers.
                -->Produces .s file.
       Output:Assembly code (usually a.s file)

/* ------------------------------------------------ */
2. Compilation (cc1++)
   The compiler translates the preprocessed code into assembly code.
   ✔ Tasks during compilation:
     Syntax checking
     Semantic analysis
     Optimization
     Convert to assembly
   ✔ Output: .s file (assembly file)
   Example:
     mov eax, 3.14
     call std::cout

   View compilation to assembly
   Command: g++ -S example.i -o example.s
/* ============================================================================================= */
✅ 3. Assembly
      Task Performed:
       ->Takes the assembly code and converts each instruction to binary machine code
           -Converts mnemonics (like MOV, ADD) into opcodes (actual binary digits).
       ->Resolves internal (local) labels
           -Converts labels used inside a file into numeric jump addresses.
       ->Generates an object file containing:
          -Machine code (in binary format)
          -Symbol table (lists functions & variables used/defined)
          -Relocation table (information)- (unresolved addresses)
            --->Marks places where addresses are not known yet (external function calls).
        ->The object file is not executable yet because many addresses are still unknown.
      Output: Object file (usually .o or .obj)
/* -------------------------------------------- */
3. Assembly (as)
   Assembler converts assembly code into machine code (object file).
    ✔ Output: .o file
    This file contains:
      Machine instructions
      Symbol table (functions, global variables)
      Relocation information
    But functions from other files are still unresolved.
    
    Create object file
    g++ -c main.cpp -o main.o

    
/* ============================================================================================= */
✅ 4. Linking
      Task Performed:
       ->Combines multiple object files and libraries-(static & dynamic) (.o, .lib, .a, .so, .dll)
          --Program may have multiple .o files.
          --External libraries (like libc.a, .so, .dll) are also linked.
       ->Resolves external symbols:
          -Example: printf() is not in your file—linker finds it in standard library.
          -Matches function declarations to their actual definitions.
          -Function calls
          -Global variables
       ->Performs relocation:
          -Adjusts memory addresses for all code and data.
          -Ensures every function and variable has a real memory address in the final executable.
       ->Handles static vs dynamic linking:
          -Static linking: library copied into final executable.
          -Dynamic linking: library linked at runtime (.dll / .so).
       ->Fixes memory addresses for all code and data sections
       ->Produces a single final executable(Generates final executable)
          -Adds executable header
          -Sets entry point for execution (usually _start → main())
       Output: Executable file (e.g., a.out, program.exe)

Link object files
g++ main.o math.o -o final_app
Command: g++ example.o -o example
/* -------------------------------------------- */
4. Linking (ld)
   The linker combines:
     All object files (file1.o, file2.o)
     Runtime libraries (libstdc++, system libs)
     Static or dynamic libraries (.a, .so, .lib, .dll)
   ✔ Responsibilities:
       Resolve function calls across files
       Allocate final memory addresses
       Combine code + data into an executable
   ✔ Output: a.out or program.exe
   Example:
      main.cpp → main.o
      math.cpp → math.o
      Linker merges both → final executable
/* ============================================================================================= */
✅ 5. Execution
      Task Performed:
        ->Operating system loads the executable into memory
        ->Program is loaded into memory by the OS loader
        ->Executable sections mapped:
            -Text (code)
            -Data (initialized variables)
            -BSS (uninitialized variables)
            -Stack
            -Heap
            -Global/static memory
        ->Runtime environment is prepared
            -Stack is set up for function calls
            -CPU registers are initialized  
            -Dynamic libraries are loaded (for dynamically linked programs)
        ->Transfers control to the program’s entry point (usually main())
            -Usually to _start
            -Then to main() function
        ->CPU executes machine instructions step-by-step
            -Program interacts with:
                OS system calls (I/O, files)
                    -Memory
                    -Other hardware components
                When program ends:
                    -Memory is freed
                    -Control returns to the OS
      Output: Running program (actual process executing on CPU)
/* -------------------------------------------- */
/* ============================================================================================= */





//C++ Program (example.cpp)
#include <iostream>
#define SQR(x) ((x)*(x))
int main() {
    int a = 5;
    std::cout << "Square = " << SQR(a) << std::endl;
  return 0;
}

🔎 Step-by-Step Compilation Example
We’ll use typical g++ commands to show each stage.

1️⃣ Preprocessing
Command: g++ -E example.cpp -o example.i

What Happens:
#include <iostream> → expanded into large header code.
#define SQR(a) → macro substituted.

Comments removed.
Preprocessed Output (portion):
int main() {
    int a = 5;
    std::cout << "Square = " << ((a)*(a)) << std::endl;
    return 0;
}

Output File:
✔ example.i

2️⃣ Compilation → Assembly Code
Command: g++ -S example.i -o example.s

What Happens:
Tokenization, parsing, semantic checks.
Converts high-level code to assembly for your CPU.

Assembly Output (portion):
movl    $5, -4(%rbp)
movl    -4(%rbp), %eax
imull   %eax, %eax

Output File:
✔ example.s

3️⃣ Assembly → Machine Code (Object File)
Command: g++ -c example.s -o example.o

What Happens:
Assembler converts assembly mnemonics → binary machine code.
Creates symbol and relocation tables.
Output File:
✔ example.o

4️⃣ Linking → Final Executable
Command: g++ example.o -o example

What Happens:
Links your code with the iostream library (libstdc++).

Resolves symbols like:
std::cout
operator<<
std::endl
Produces a runnable executable.

Output File:
✔ example (or example.exe on Windows)

5️⃣ Execution
Command:
./example
Output on Screen:
Square = 25

What Happens Internally:
OS loads program into memory.
Sets up stack/heap.
Calls _start → main().
CPU executes machine instructions.