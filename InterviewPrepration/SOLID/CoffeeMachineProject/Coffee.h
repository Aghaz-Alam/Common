//File 1: Coffee.h
//Demonstrates SRP, OCP, LSP
#pragma once
#include <string>
// Abstract base class (OCP, LSP)
class Coffee {
  public:
    virtual std::string name() const = 0;
    virtual double price() const = 0;
    virtual ~Coffee() = default;
};
// Concrete coffee types (Open for extension)
class Espresso : public Coffee {
  public:
    std::string name() const override { return "Espresso"; }
    double price() const override { return 2.50; }
};
class Cappuccino : public Coffee {
  public:
    std::string name() const override { return "Cappuccino"; }
    double price() const override { return 3.50; }
};

/* 
✔ SRP: Coffee classes only define coffee data
✔ OCP: Add new coffee by creating a new class
✔ LSP: All coffees substitute Coffee safely
*/