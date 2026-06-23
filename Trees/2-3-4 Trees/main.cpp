#include "twothreefour.h"
#include <array>
#include <print>

int main()
{
    using namespace std;
    TwoThreeFour<int> t;

    std::array<int, 18> vals { 100, 50, 150, 25, 75, 125, 175, 60, 65, 70, 61, 62, 63, 64, 66, 67,
        68, 69 };

    for (int x : vals) {
        t.insert(x);
    }
    t.print();
    return 0;
}
