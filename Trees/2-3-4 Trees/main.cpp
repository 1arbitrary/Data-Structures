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

    std::array<int, 18> delete_vals
        = { 175, 150, 125, 100, 75, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 50, 25 };

    for (std::size_t i { 0 }; i < 18; i++) {
        std::println("Deleting Value : {}\n pre-delete : ", delete_vals[i]);
        t.print();
        t.Delete(delete_vals[i]);
        std::println("Post Delete");
        t.print();
    }
    return 0;
}
