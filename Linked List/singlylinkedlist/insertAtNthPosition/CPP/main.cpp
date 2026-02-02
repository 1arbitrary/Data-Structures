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
  bool is_empty() const { return head_ptr == nullptr; }

  void free_allocated_memory() {
    std::cout << "Freeing All The Allocated Memory " << "\n";
    while (head_ptr != nullptr) {
      Node *temp_node = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp_node;
    }
  }

  Node *check_position(int desired_position) const {
    Node *current_node = head_ptr;
    if (desired_position == 1)
      return current_node;

    int i{1};
    while (i < (desired_position - 1)) {
      if (current_node != nullptr && current_node->next_node != nullptr) {
        current_node = current_node->next_node;
        i++;
      } else
        break;
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

  void delete_node() {
    if (!is_empty()) {
      Node *temp_node = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp_node;
    } else
      std::cerr << "Nothing to delete, head_ptr is Null";
  }

  void insert_at_specific_node(int data, int insert_position) {
    if (insert_position == 0 || insert_position < 0) {
      std::cout << "Invalid Position " << insert_position << "\n";
      return;
    }

    if (!is_empty()) {
      Node *current_node = check_position(insert_position);
      if (current_node == nullptr) {
        std::cout << "The Position " << insert_position
                  << " doesn't exists on the list. Invalid Insertion" << "\n";
        return;
      }

      Node *new_node = new Node(data);
      if (insert_position > 1) {
        new_node->next_node = current_node->next_node;
        current_node->next_node = new_node;
      } else if (insert_position == 1) {
        new_node->next_node = head_ptr;
        head_ptr = new_node;
      }
    } else {
      std::cout << "Inserting at the first index as list is empty ...." << "\n";
      Node *new_node = new Node(data);
      new_node->next_node = head_ptr;
      head_ptr = new_node;
    }
  }

  void delete_specific_node(int delete_position) {
    if (delete_position == 0 || delete_position < 0)
      return;

    if (!is_empty()) {
      Node *current_node = check_position(delete_position);
      if (current_node == nullptr) {
        std::cerr << "Position " << delete_position
                  << " doesn't exists on the list. Invalid Deletion" << "\n";
        return;
      }

      Node *temp_node = nullptr;
      if (delete_position > 1) {
        temp_node = current_node->next_node;
        current_node->next_node = current_node->next_node->next_node;
        delete temp_node;
      } else if (delete_position == 1) {
        temp_node = current_node;
        head_ptr = current_node->next_node;
        delete temp_node;
      }
    } else
      std::cerr << "Nothing to delete ! Head Node is Non-Existent" << "\n";
  }

  void top_node() const {
    if (!is_empty()) {
      std::cout << "Head Node : " << head_ptr->data << "\n";
    } else
      std::cerr << "Head Node doesn't exist, Nothing to Display !\n";
  }

  void print() const {
    Node *current_node = head_ptr;
    std::cout << "Linked List  : ";
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
  list.add_node(23);
  list.add_node(53);
  list.insert_at_specific_node(88,2);
  list.print();
  list.delete_specific_node(15);
  list.delete_node();

  list.top_node();
  list.insert_at_specific_node(99, 34);
  list.add_node(88);
  list.add_node(99);
  list.top_node();
  list.print();
  list.delete_specific_node(2);
  list.delete_specific_node(3);
  list.print();
  return 0;
}
