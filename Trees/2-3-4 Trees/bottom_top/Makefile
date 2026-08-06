CXX=g++
CXXFLAGS=-std=c++23 -Wall -Wextra -Wpedantic -fsanitize=address,leak,undefined -fno-omit-frame-pointer -g3 -ggdb -O0

output: main.cpp twothreefour.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o output
