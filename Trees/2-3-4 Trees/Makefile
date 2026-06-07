CXX=clang++
CXXFLAGS= -std=c++23 -Wall -Wextra -Wpedantic -fsanitize=address,leak,undefined -fno-omit-frame-pointer -g3

output: main.cpp twothreefour.h
	$(CXX) $(CXXFLAGS) main.cpp -o output
