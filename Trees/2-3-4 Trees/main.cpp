#include "twothreefour.h"

int main() {
    TwoThreeFour<int> t;
    t.insert(10);
    t.insert(5);
    t.insert(15);
    t.insert(20);
    t.insert(30);
    t.insert(40);
    t.insert(50);
    t.print();
    t.insert(60);
    t.print();
    t.insert(70);
    t.insert(25);
    t.insert(1);
    t.insert(2);
    t.insert(3);
    t.insert(4);
    t.insert(80);
    t.insert(90);
    t.print();
  return 0;
}
