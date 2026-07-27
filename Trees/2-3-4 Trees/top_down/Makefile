CXX=g++
CXXFLAGS= -std=c++23 -Wall -Wextra -Wpedantic -fsanitize=address,leak,undefined -fno-omit-frame-pointer -O0 -g3 -ggdb

output: main.cpp twothreefour.hpp
	$(CXX) $(CXXFLAGS) main.cpp -o output
