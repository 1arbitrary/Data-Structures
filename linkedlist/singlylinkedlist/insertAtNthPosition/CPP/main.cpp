#include <iostream>

class Node {
public:
  int data;
  Node *next_node;
  Node(int d) : data(d), next_node(nullptr) {}
};

class LinkedList {
private:
  Node *head_ptr = nullptr;
  void free_allocated_memory() {
    while (head_ptr != nullptr) {
      Node *temp_node = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp_node;
    }
  }

  bool is_empty() const { return head_ptr == nullptr; }

  Node *check_position(int desired_position) {
    Node *current_node = head_ptr;
    if (desired_position == 1)
      return current_node;

    int i{1};
    while (i < (desired_position - 1) && current_node != nullptr) {
      current_node = current_node->next_node;
      i++;
    }
    return (current_node != nullptr && current_node->next_node != nullptr)
               ? current_node
               : nullptr;
  }

public:
  LinkedList() = default;
  ~LinkedList() { free_allocated_memory(); }

  LinkedList(const LinkedList &) = delete;
  LinkedList &operator=(const LinkedList &) = delete;

  void add_node(int data) {
    Node *new_node = new Node(data);
    new_node->next_node = head_ptr;
    head_ptr = new_node;
  }

  void delete_node(int delete_position) {
    if (!is_empty()) {
      if (delete_position == 0 || delete_position < 0)
        return;

      Node *current_node = check_position(delete_position);
      Node *temp_node = nullptr;

      if (current_node != nullptr && delete_position > 1) {
        temp_node = current_node->next_node;
        current_node->next_node = current_node->next_node->next_node;

        std::cout << "Deleting Node : " << temp_node->data << " at position " << delete_position << "\n";
        delete temp_node;

      } else if (delete_position == 1 && current_node != nullptr) {
        temp_node = current_node;
        head_ptr = current_node->next_node;

        std::cout << "Deleting Node : " << temp_node->data << " at position " << delete_position << "\n";
        delete temp_node;

      } else if (current_node == nullptr) {
        std::cerr << "The Position : " << delete_position
                  << "doesn't exists on the list." << "\n";
      }

    } else {
      std::cerr << "Head Node is Non-existent ! Nothing to Delete" << "\n";
    }
  }

  void top_node() const {
    if (head_ptr != nullptr) {
      std::cout << "Head Node : " << head_ptr->data << "\n";
    } else
      std::cerr << "Head Node is Non-Existent ! Nothing to Display" << "\n";
  }

  void print() const {
    Node *current_node = head_ptr;
    std::cout << "Linked List : ";
    while (current_node != nullptr) {
      std::cout << current_node->data << "\t";
      current_node = current_node->next_node;
    }
    std::cout << "\n";
  }
};

int main(void) {
  LinkedList list;

  list.add_node(22);
  list.add_node(44);
  list.add_node(66);
  list.add_node(88);

  list.print();
  list.top_node();

  list.delete_node(3);
  list.delete_node(1);
  list.print();

  list.add_node(99);
  list.add_node(111);
  list.print();
  list.delete_node(3);
  list.print();
  return 0;
}
