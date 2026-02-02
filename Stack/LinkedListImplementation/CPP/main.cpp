#include <iostream>

class Node {
public:
  int data;
  Node *next_node;
  Node(int d) : data(d), next_node(nullptr) {}
};

class Stack {
private:
  Node *head_ptr = nullptr;

  void free_allocated_space() {
    while (head_ptr != nullptr) {
      Node *temp = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp;
    }
  }

public:
  // Default constructor : To ensure objects can be initialized
  Stack() = default;

  // Destructor(runs automatically after the class object is out of scope) :
  // deallocates allocated memory
  ~Stack() { free_allocated_space(); }

  // To ensure stack can't be copied : automatically gives an error if someone
  // tries to pass a stack object into the constructor.
  Stack(const Stack &) = delete;

  // To ensure stack objects can't be assigned
  Stack &operator=(const Stack &) = delete;

  bool is_empty() const { return head_ptr == nullptr; }

  void push(int data) {
    Node *current_node = new Node(data);
    current_node->next_node = head_ptr;
    head_ptr = current_node;
  }

  void pop() {
    if (!is_empty()) {
      std::cout << "Popping Element : " << head_ptr->data << "\n";
      Node *temp = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp;
    } else
      std::cerr << "Empty Stack ! Nothing to Pop" << "\n";
  }

  void peek() const {
    if (head_ptr != nullptr) {
      std::cout << "Top Element : " << head_ptr->data << "\n";
    } else
      std::cerr << "Empty Stack ! No Top element exists !" << "\n";
  }

  void print() const {
    Node *current = head_ptr;
    std::cout << "Stack : ";
    while (current != nullptr) {
      std::cout << current->data << "\t";
      current = current->next_node;
    }
    std::cout << "\n";
  }
};

int main(void) {
  Stack stack;
  stack.push(22);
  stack.push(33);
  stack.push(44);
  stack.push(55);

  stack.peek();
  stack.print();

  stack.pop();
  stack.pop();
  stack.pop();
  stack.pop();
  stack.pop();
  stack.pop();  

  stack.push(99);
  stack.print();
  return 0;
}
