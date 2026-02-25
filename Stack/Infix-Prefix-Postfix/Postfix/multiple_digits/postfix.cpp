#include <iostream>
#include <stdexcept>

struct Stack {
  static constexpr std::size_t MAX_SIZE = 101;
  int operands[MAX_SIZE];
  int top = -1;

  Stack() = default;

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  bool is_full() const { return top == (MAX_SIZE - 1); }
  bool is_empty() const { return top == -1; }
  void print_result() const { std::cout << operands[top] << "\n"; }

  void push(int operand) {
    if (!is_full()) {
      operands[++top] = operand;
    } else {
      throw std::out_of_range("Attempt To Push On A Filled Stack !");
    }
  }

  int pop() {
    if (!is_empty()) {
      return operands[top--];
    } else {
      throw std::out_of_range("Attempt To Pop An Empty Stack!");
    }
  }

  int perform_operation(int operand1, int operand2, char operation) {
    int result{0};

    switch (operation) {
    case '+':
      result = operand2 + operand1;
      break;
    case '-':
      result = operand2 - operand1;
      break;
    case '*':
      result = operand2 * operand1;
      break;
    case '/':
      result = operand2 / operand1;
      break;
    default:
      std::cout << "Invalid Operation" << "\n";
      break;
    }
    return result;
  }

  void scan_expression(std::string expression) {
    for (std::size_t i{0}; i < expression.length(); i++) {
      if (expression[i] != ' ') {
        if (expression[i] == '+' || expression[i] == '-' ||
            expression[i] == '*' || expression[i] == '/') {
          int operand1 = pop();
          int operand2 = pop();
          push(perform_operation(operand1, operand2, expression[i]));
        } else {
          std::string temp_string{};
          while (i < expression.length() && expression[i] != ' ') {
            temp_string += expression[i++];
          }
          push(std::stoi(temp_string));
          temp_string = "";
        }
      }
    }

    if (top == 0) {
      print_result();
    } else {
      std::cout << "Invalid Number Of Elements In the Stack" << "\n";
    }
  }
};

int main(void) {
  Stack s;
  s.scan_expression("3 2 * 9 +");
  return 0;
}
