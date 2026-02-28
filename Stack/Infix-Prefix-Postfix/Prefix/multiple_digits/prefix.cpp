#include <iostream>
#include <stdexcept>

struct Stack {
  static constexpr int MAX_SIZE = 101;
  int top = -1;
  int operands[MAX_SIZE];

  Stack() = default;

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  bool is_empty() const { return top == -1; }
  bool is_full() const { return top == (MAX_SIZE - 1); }

  void push(int data) {
    if (!is_full()) {
      operands[++top] = data;
    } else {
      throw std::out_of_range("Attempt To Push On A Filled Stack");
    }
  }

  int pop() {
    if (!is_empty()) {
      return operands[top--];
    } else {
      throw std::out_of_range("Attempt To Pop On An Empty Stack");
    }
  }

  int perform_operation(int operand1, int operand2, int operation) {
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
      std::cout << "Invalid Operand" << "\n";
      break;
    }
    return result;
  }

  void scan_expression(std::string expr) {
    for (int i = expr.length() - 1; i >= 0; i--) {
      if (expr[i] != ' ') {
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' ||
            expr[i] == '/') {
          int operand1 = pop();
          int operand2 = pop();
          push(perform_operation(operand2, operand1, expr[i]));
          continue;
        }
        std::string temp_string{};
        while (i >= 0 && expr[i] != ' ') {
          temp_string = expr[i--] + temp_string;
        }
        push(std::stoi(temp_string));
      }
    }

    if (top == 0) {
      print();
    } else {
      std::cout << "Unbalanced Stack !" << "\n";
    }
  }

  void print() const {
    int i{0};
    std::cout << "Stack : ";
    while (i <= top) {
      std::cout << operands[i++];
    }
    std::cout << "\n";
  }
};

int main(void) {
  Stack s;
  s.scan_expression("- + * 2 3 * 5 4 9");

  return 0;
}
