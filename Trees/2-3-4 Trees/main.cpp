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

    std::array<int, 11> delete_vals = { 63, 64, 62, 61, 60, 65, 66, 67, 68, 69, 70 };

    for (std::size_t i {0} ; i < 1 ; i++) {
        std::println("Deleting Value : {}\n pre-delete : ", delete_vals[i]);
        t.print();
        t.Delete(delete_vals[i]);
	std::println("Post Delete");
	t.print();
    }
    return 0;
}
