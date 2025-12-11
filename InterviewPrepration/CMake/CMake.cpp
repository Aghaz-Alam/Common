What is CMake?
CMake is a build system generator.
It does not compile your code directly — instead, it generates build files for actual build tools like:
-->Make (Linux)
-->Ninja
-->Visual Studio solutions
-->Xcode projects
Then those tools compile your C++ code.
Think of CMake as the “config file” that tells your compiler how to build your project.


Why do we need CMake?
Because C++ projects can become complex:
-->Many source files
-->Libraries
-->Include paths
-->Compiler flags
-->Linking rules
-->Debug vs Release build
-->Cross-platform builds

Writing all that manually is painful.
CMake makes it easy.



What is a Target in CMake?
A target is something CMake knows how to build.

Examples of targets:
✔️ Executable
add_executable(my_app main.cpp)

✔️ Library
add_library(my_lib mylib.cpp mylib.hpp)

✔️ Interface library (header-only)
add_library(my_header_lib INTERFACE)

✔️ Imported library (external pre-built)
add_library(ext_lib STATIC IMPORTED)

✔️ Object library
add_library(objlib OBJECT file.cpp)



Why are Targets Important?
-->Targets allow you to attach properties:
-->Include directories
-->Compiler options
-->Linked libraries
-->Version
-->Dependencies
-->Build type

Example:
-->target_include_directories(my_app PRIVATE include/)
-->target_link_libraries(my_app PRIVATE my_lib)
-->target_compile_features(my_app PRIVATE cxx_std_20)
Targets give structured control of your build.


How to Use CMake in C++ (Simple Example)
Project Structure
project/
 ├── CMakeLists.txt
 ├── main.cpp
 └── math.cpp




 CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyProject)
add_executable(my_app
    main.cpp
    math.cpp
)



Build steps (Linux/Mac)
mkdir build
cd build
cmake ..
make
./my_app





Example with Separate Library Target
Directory:
project/
 ├── CMakeLists.txt
 ├── main.cpp
 └── math/
      ├── CMakeLists.txt
      ├── math.cpp
      └── math.hpp



      Top-level CMakeLists.txt
cmake_minimum_required(VERSION 3.10)
project(MyProject)

add_subdirectory(math)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE math_lib)




math/CMakeLists.txt
-->add_library(math_lib math.cpp)
-->target_include_directories(math_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})



Why use Targets instead of Manually Writing Flags?
Bad way (old style):
-->include_directories(include/)
-->add_executable(app main.cpp)


Better way (modern CMake):
-->add_executable(app main.cpp)
-->target_include_directories(app PRIVATE include/)
-->target_compile_features(app PRIVATE cxx_std_20)
Modern way is target-specific and avoids global settings.


Simple Unit Test Example (GoogleTest)
-->add_executable(test_app test.cpp)
-->target_link_libraries(test_app PRIVATE gtest_main my_lib)




Summary
✔️ CMake
A tool that generates build instructions.

✔️ Target
A build entity (executable, library, interface).

✔️ Why use targets?
Structured, modern, clean way of building C++ projects.

✔️ How to use it?
Create CMakeLists.txt, define targets, link them, build.





1. What is a Makefile in CMake?
Makefile is not written by you when using CMake.
CMake automatically generates the Makefile for you.

✔️ What is a Makefile?
A Makefile is a script used by the make build tool.
It tells Make:
Which files to compile
How to compile them (commands, flags)
How to link them
Dependencies
Rules for clean, install, etc.

Example of a simple Makefile (just for understanding):
main.o: main.cpp
    g++ -c main.cpp

app: main.o
    g++ main.o -o app

But with CMake, you don’t create this manually — CMake generates it.



2. What is a Build File?
A build file is the output file created by CMake.
Depending on your generator, CMake creates different build files:
| Platform / Generator    | Build File Type        |
| ----------------------- | ---------------------- |
| Linux (default)         | **Makefile**           |
| Ninja                   | **build.ninja**        |
| Windows (Visual Studio) | **.sln**, **.vcxproj** |
| Xcode (Mac)             | **.xcodeproj**         |
Build files are what the compiler actually uses to build your program.




3. Why do we need Makefile or Build Files?
Because a real C++ project may contain:
-->Many .cpp files
-->Multiple libraries
-->Target dependencies
-->Compiler flags
-->Include paths
-->Multiple build configurations (Debug, Release)
Manually compiling becomes impossible.
Makefiles or build files automate the entire build process.
CMake → generates build files → Make/Ninja/MSVC → compiles your code.





4. How Are Makefiles and Build Files Created in CMake?
💡 You do NOT write the Makefile.
You only write:
📄 CMakeLists.txt

For example:
cmake_minimum_required(VERSION 3.10)
project(MyProject)
add_executable(my_app main.cpp)




5. Steps to Generate Build Files
Step 1 — Create a Build Directory
mkdir build
cd build

Step 2 — Run CMake
cmake ..

✔️ What happens now?

CMake reads CMakeLists.txt and generates:
Makefile (for Make)
CMakeCache.txt
cmake_install.cmake
CMakeFiles/ directory



6. Step 3 — Build Using Make
make

This uses the generated Makefile to:
Compile your .cpp files
Link the object files
Produce final executable (e.g., my_app)



7. Visual Summary
Your Code (.cpp, .h)
        ↓
CMakeLists.txt (written by you)
        ↓   cmake ..
CMake Generator
        ↓
Makefile / build.ninja / .sln / xcodeproj
        ↓   make / ninja / MSBuild
Actual Compilation




8. Key Differences: Makefile vs CMake
| CMake                    | Makefile                           |
| ------------------------ | ---------------------------------- |
| You write CMakeLists.txt | You do NOT write Makefile manually |
| Generates build files    | Used by compiler to build code     |
| Cross-platform           | Platform-specific                  |
| Modern                   | Old but powerful                   |
| High-level               | Low-level detailed rules           |


9. What Happens Inside Build Directory
build/
 ├── Makefile
 ├── CMakeCache.txt
 ├── cmake_install.cmake
 ├── CMakeFiles/
 └── my_app (executable)

Your source folder is kept clean.


10. Example with Commands
Project structure
project/
├── CMakeLists.txt
└── main.cpp

Commands
mkdir build
cd build
cmake ..
make
./my_app





Summary (Simple and Clear)
✔️ CMake
A tool that generates build files.

✔️ Makefile
A file generated by CMake (or manually) that tells make how to build your project.

✔️ Build Files
Actual files CMake creates so compilers know what to do (Makefile, ninja, sln, xcodeproj).

✔️ How they are created
By running:
cmake ..

✔️ How they are used
You run:
make
