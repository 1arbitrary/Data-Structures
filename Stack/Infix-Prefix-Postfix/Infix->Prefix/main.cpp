#include <iostream>
#include <stdexcept>

struct Stack {
  static constexpr int MAX_SIZE = 101;
  std::string prefix{};
  char operators[MAX_SIZE];
  int top = -1;

  Stack() = default;

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  enum precedence {
    addition = 1,
    subtraction = 1,
    multiplication = 2,
    division = 2,
    exponents = 3,
    parantheses = 4
  };

  bool is_full() const { return (top == MAX_SIZE - 1); }
  bool is_empty() const { return top == -1; }

  void push(char operation) {
    if (is_full()) {
      throw std::out_of_range("Attempt To Push On A Filled Stack");
    }
    operators[++top] = operation;
  }

  char pop() {
    if (is_empty()) {
      throw std::out_of_range("Attempt To Pop On An Empty Stack");
    }
    return operators[top--];
  }

  precedence peek() const {
    if (is_empty()) {
      throw std::out_of_range("Attempt To Access An Empty Stack");
    }
    switch (operators[top]) {
    case ')':
      return parantheses;
    case '^':
      return exponents;
    case '+':
      return addition;
    case '-':
      return subtraction;
    case '*':
      return multiplication;
    case '/':
      return division;
    default:
      throw std::invalid_argument("Invalid Operator Found");
    }
  }

  bool has_less_precedence(char operation) const {
    if (is_empty()) {
      return false;
    }
    switch (operation) {
    case ')':
      return false;
    case '^':
      return exponents <= peek();
    case '+':
      return addition < peek();
    case '-':
      return subtraction < peek();
    case '*':
      return multiplication < peek();
    case '/':
      return division < peek();
    default:
      throw std::invalid_argument("Invalid Operator Found");
    }
  }

  void handle_parantheses(char parans) {
    if (parans == ')') {
      push(parans);
    } else {
      if (is_empty() && parans == '(') {
        throw std::invalid_argument("Missing Opening Parantheses");
      }
      while (!is_empty() && operators[top] != ')') {
        prefix = pop() + prefix;
      }
      pop();
    }
  }

  void handle_operators(char operation) {
    while (!is_empty() && peek() != parantheses &&
           has_less_precedence(operation)) {
      prefix = pop() + prefix;
    }
    push(operation);
  }

  void scan_expression(std::string expression) {
    for (int i = expression.length() - 1; i >= 0; i--) {
      if (expression[i] != ' ') {
        if (expression[i] == '(' || expression[i] == ')') {
          handle_parantheses(expression[i]);
          continue;
        }
        if (expression[i] == '+' || expression[i] == '-' ||
            expression[i] == '*' || expression[i] == '/' ||
            expression[i] == '^') {
          handle_operators(expression[i]);
          continue;
        }
        prefix = expression[i] + prefix;
      }
    }

    while (!is_empty()) {
      if (peek() != parantheses) {
        prefix = pop() + prefix;
      } else
        throw std::invalid_argument("Missing Parantheses");
    }

    if (top == -1) {
      print();
    } else {
      throw std::invalid_argument("Unbalanced Stack");
    }
  }

  void print() const { std::cout << prefix << "\n"; }
};

int main(void) {
  Stack s;
  s.scan_expression("A+B*(C^D-E)^(F+G*H)-I");
  return 0;
}
