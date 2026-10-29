#include "twothreefour.hpp"
#include <array>
#include <print>

int main()
{
	TwoThreeFour<int> t;
	constexpr std::array<int, 12> values{
	10, 20, 30, 40, 50, 60,
	70, 80, 90, 100, 110, 120
	};

	for (const auto value : values) {
		t.insert(value);
		t.print();
	}
	return 0;
}
