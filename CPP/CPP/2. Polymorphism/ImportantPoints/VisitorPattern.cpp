//Visitor Pattern (Add new behavior without modifying classes)
/* 
Used when:
You have many classes
You want to add new operations on them
Without modifying original classes (Open-closed principle)
*/
//Code:
#include <iostream>
using namespace std;
class Circle;
class Square;

class Visitor {
  public:
    virtual void visit(Circle*) = 0;
    virtual void visit(Square*) = 0;
};
class Shape {
  public:
    virtual void accept(Visitor* v) = 0;
};
class Circle : public Shape {
  public:
    void accept(Visitor* v) override { v->visit(this); }
};
class Square : public Shape {
  public:
    void accept(Visitor* v) override { v->visit(this); }
};
class DrawVisitor : public Visitor {
  public:
    void visit(Circle*) override { cout << "Drawing Circle\n"; }
    void visit(Square*) override { cout << "Drawing Square\n"; }
};
int main() {
    Circle c;
    Square s;
    DrawVisitor dv;

    c.accept(&dv);
    s.accept(&dv);
  return 0;
}
/*
Output
Drawing Circle
Drawing Square
*/