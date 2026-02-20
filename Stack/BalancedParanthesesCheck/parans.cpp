#include <iostream>
#include <stdexcept>
#define MAX_SIZE 101

template <typename T> struct Stack {
  int top = -1;
  T symbols[MAX_SIZE] = {};

  Stack() = default;
  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  bool is_empty() const { return (top == -1); }
  bool is_full() const { return (top == (MAX_SIZE - 1)); }

  void Push(T data) {
    if (!is_full()) {
      symbols[++top] = data;
    } else {
      throw std::out_of_range("Attempt To Push On A Filled List");
    }
  }

  void Pop() {
    if (!is_empty()) {
      top--;
    } else {
      throw std::out_of_range(
          "Attempt To Perform Pop Operation On An Empty List");
    }
  }

  void scan_symbols(std::string input_expression) {
    for (char elem : input_expression) {
      // Only Pushes Opening Symbols
      if ((elem == '{') || (elem == '[') || (elem == '(')) {
        Push(elem);
        continue;
      }

      // Checks if a counter part of the symbol was found
      if (!is_empty() && ((symbols[top] == '{' && elem == '}') ||
                          (symbols[top] == '[' && elem == ']') ||
                          (symbols[top] == '(' && elem == ')'))) {
        Pop();
        continue;
      }

      // Guard Against Closing Symbols if there were no opening symbols
      if (elem == '}' || elem == ']' || elem == ')') {
        std::cerr << "Unbalanced Symbols Found" << "\n";
	return;
      }
    }

    if (top < 0) {
      std::cout << "All Symbols Are Balanced" << "\n";
    } else if (top > -1) {
      std::cerr << "Unbalanced Symbols Found" << "\n";
    }
  }
};

int main(void) {
  Stack<char> s;
  std::string input_expression{};

  std::cout << "Enter An Expression : ";
  std::getline(std::cin, input_expression);

  s.scan_symbols(input_expression);

  return 0;
}
