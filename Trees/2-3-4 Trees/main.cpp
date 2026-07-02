
#include "twothreefour.hpp"
#include <array>
#include <print>

int main()
{
    TwoThreeFour<int> t;

    std::array<int, 18> vals { 100, 50, 150, 25, 75, 125, 175, 60, 65, 70, 61, 62, 63, 64, 66, 67,
        68, 69 };

    for (int x : vals) {
        t.insert(x);
    }

    t.Delete(63);
    t.Delete(64);
    t.Delete(62);
    t.Delete(61);
    t.Delete(60);
    t.Delete(65);
    t.print();
    t.Delete(66);
    t.print();
    t.Delete(67);
    t.print();
    // t.Delete(68);
    // t.print();

    // t.Delete(69);
    // t.print();

    // t.Delete(70);
    // t.print();

    return 0;
}
