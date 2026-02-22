#include <iostream>
#include <stdexcept>

struct Stack {
  int top = -1;
  static constexpr int MAX_SIZE = 101;
  int operands[MAX_SIZE];

  Stack() = default;
  ~Stack() { print_result(); }

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  bool is_empty() const { return top == -1; }
  bool is_full() const { return top == (MAX_SIZE - 1); }
  void print_result() const { std::cout << operands[top] << "\n"; }

  void push(int operand) {
    if (!is_full()) {
      operands[++top] = operand;
      return;
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
      std::cout << "Invalid Operator, SKIPPING !";
      break;
    }
    return result;
  }

  void scan_expression(std::string expression) {
    for (char element : expression) {
      if (element == '+' || element == '-' || element == '*' ||
          element == '/') {
        int op1 = pop();
        int op2 = pop();
        push(perform_operation(op1, op2, element));
      } else if (element != ' ') {
        push(element - '0');
        continue;
      }
    }
  }
};

int main(void) {
  Stack s;
  s.scan_expression("95*8+");
  return 0;
}
