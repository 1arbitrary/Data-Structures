#include "twothreefour.h"
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

    // Sequence 1
    t.Delete(63);
    t.print();

    t.Delete(64);
    t.print();

    t.Delete(62);
    t.print();

    t.Delete(61);
    t.print();

    t.Delete(60);
    t.print();

    t.Delete(65);
    t.print();

    // t.Delete(66);
    // t.print();

    // t.Delete(67);
    // t.print();

    // t.Delete(68);
    // t.print();

    // t.Delete(69);
    // t.print();

    // t.Delete(70);
    // t.print();

    return 0;
}
