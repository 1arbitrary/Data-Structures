#include <iostream>

class Node {
public:
  int data;
  Node *next_node;
  Node(int d) : data(d), next_node(nullptr) {}
};

class LinkedList {
private:
  Node *ptr_head = nullptr;
  void free_allocated_memory() {
    while (ptr_head != nullptr) {
      Node *temp_node = ptr_head;
      ptr_head = ptr_head->next_node;
      delete temp_node;
    }
  }

public:
  LinkedList() = default;
  ~LinkedList() { free_allocated_memory(); }
  // Copy constructor : deleting any linkedlist reference passed to it
  LinkedList(const LinkedList &) = delete;
  // For disabling assignment of a linked list to another linked list
  LinkedList &operator=(const LinkedList &) = delete;

  bool is_empty() const { return ptr_head == nullptr; }

  void addNode(int data) {
    Node *current_node = new Node(data);
    current_node->next_node = ptr_head;
    ptr_head = current_node;
  }

  void deleteNode() {
    if (!is_empty()) {
      std::cout << "Deleting Top Node : " << ptr_head->data << "\n";
      Node *temp_node = ptr_head;
      ptr_head = ptr_head->next_node;
      delete temp_node;
    } else
      std::cerr << "List is Empty ! head_ptr is null" << "\n";
  }

  void topNode() const {
    if (!is_empty()) {
      std::cout << "Top Node : " << ptr_head->data << "\n";
    } else {
      std::cerr << "List is Empty ! head_ptr is null" << "\n";
    }
  }

  void printList() const {
    Node *current = ptr_head;
    std::cout << "List : ";
    while (current != nullptr) {
      std::cout << current->data << "\t";
      current = current->next_node;
    }
    std::cout << "\n";
  }
};

int main(void) {
  LinkedList list;
  list.addNode(22);
  list.addNode(33);
  list.addNode(44);
  list.addNode(55);
  list.printList();
  list.topNode();
  list.deleteNode();
  list.deleteNode();
  list.topNode();
  list.deleteNode();
  list.deleteNode();
  list.addNode(99);
  list.printList();
  return 0;
}
