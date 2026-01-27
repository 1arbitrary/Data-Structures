#include <iostream>

class Stack {
private:
  int top = -1;
  int nums[5]{};
  static constexpr int nums_length = sizeof(nums) / sizeof(nums[0]);

  bool isEmpty() { return top == -1; }
  bool isFull() { return top == nums_length - 1; }

public:
  void push(int data) {
    if (!isFull()) {
      top++;
      nums[top] = data;
    } else {
      std::cerr << "STACK OVERFLOW DETECTED ! CRASH INCOMING\n";
    }
  }

  void pop() {
    if (!isEmpty()) {
      std::cout << "Popping Element : " << nums[top] << "\n";
      top--;
    } else {
      std::cerr << "STACK IS EMPTY ! NOTHING TO POP\n";
    }
  }

  void peek() {
    if (!isEmpty())
      std::cout << "Top Element : " << nums[top] << "\n";
    else
      std::cerr << "STACK IS EMPTY ! NOTHING ON TOP !\n";
  }

  void print() {
    std::cout << "Stack : ";
    for (int i = 0; i <= top; i++) {
      std::cout << nums[i] << "\t";
    }
    std::cout << "\n";
  }
};

int main(void) {
  Stack s;

  s.push(10);
  s.push(20);
  s.push(30);

  s.print();
  s.peek();

  s.pop();
  s.print();

  s.pop();
  s.pop();

  s.pop();
  s.peek();

  s.push(100);
  s.push(200);
  s.push(300);
  s.push(400);
  s.push(500);
  s.push(600);

  s.print();

  return 0;
}
