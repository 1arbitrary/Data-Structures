#include <iostream>
#include <stack>

int main(void) {
  std::stack<int> s;
  s.push(298);
  s.push(892);
  s.push(659);
  s.push(323);
  s.push(454);
  
  if (!s.empty()) {
    s.pop();
  } else {
    std::cout << "Empty Stack";
  }
  
  std::cout << "Size of Stack : " << s.size() << "\n";
  std::cout << "Top Element : " << s.top() << "\n";

  return 0;
}
