//Math_Functions.cpp
#include "Math_Functions.h"

int Add(int a, int b) {
    return a + b;
}

int Multiply(int a, int b) {
    return a * b;
}


//g++ Sample_Test.cpp Math_Functions.cpp -lgtest -lgtest_main -lpthread -o gTest && ./gTest