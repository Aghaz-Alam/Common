//Strategy Pattern (Replace Behavior at Runtime)
/* 
Used when:
You need to switch algorithm dynamically.
Example: Sorting strategies, payment strategies, compression strategies.
*/
//Code:
#include <iostream>
using namespace std;
class Strategy {
  public:
    virtual void execute() = 0;
    virtual ~Strategy() {}
};
class Aggressive : public Strategy {
  public:
    void execute() override { cout << "Aggressive Attack\n"; }
};
class Defensive : public Strategy {
  public:
    void execute() override { cout << "Defensive Position\n"; }
};
// Context using DI
class Player {
    Strategy* strategy;
  public:
    Player(Strategy* s) : strategy(s) {}
    void setStrategy(Strategy* s) { strategy = s; }
    void action() { strategy->execute(); }
};
int main() {
    Aggressive ag;
    Defensive df;

    Player p(&ag);
    p.action();

    p.setStrategy(&df);
    p.action();
  return 0;
}
/*
Output:
Aggressive Attack
Defensive Position
*/