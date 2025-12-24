//File 8: main.cpp
//Clean usage of the entire SOLID system
#include <memory>
#include "CoffeeMachine.h"
#include "ConsoleLogger.h"
#include "CreditCardPayment.h"
#include "Coffee.h"

int main() {
    ConsoleLogger logger;
    CreditCardPayment payment;

    CoffeeMachine machine(logger, payment);

    Espresso espresso;
    Cappuccino cappuccino;

    machine.prepareCoffee(espresso);
    machine.prepareCoffee(cappuccino);

  return 0;
}
/* 
Output:
[Console] Preparing Espresso
Paid $2.5 with Credit Card
[Console] Espresso is ready!
[Console] Preparing Cappuccino
Paid $3.5 with Credit Card
[Console] Cappuccino is ready!




Why this is the output?
1. machine.prepareCoffee(espresso);
Logs:
[Console] Preparing Espresso

Payment:
Paid $2.5 with Credit Card

Final log:
[Console] Espresso is ready!

2. machine.prepareCoffee(cappuccino);
Logs:
[Console] Preparing Cappuccino

Payment:
Paid $3.5 with Credit Card

Final log:
[Console] Cappuccino is ready!
*/




//g++ -std=c++17 main.cpp -o solid