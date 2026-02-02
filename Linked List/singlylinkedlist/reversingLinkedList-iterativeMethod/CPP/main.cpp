#include <iostream>

template <typename T> class Node {
public:
  T data;
  Node<T> *next_node;
  Node(T d) : data(d), next_node(nullptr) {}
};

template <typename T> class LinkedList {
private:
  Node<T> *head_ptr = nullptr;
  bool is_empty() const { return head_ptr == nullptr; }

  void free_allocated_memory() {
    std::cout << "Freeing Allocated Memory ...." << "\n";

    Node<T> *temp_node = nullptr;
    while (head_ptr != nullptr) {
      temp_node = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp_node;
    }
  }

  Node<T> *check_position(std::size_t desired_position) const {
    if (desired_position == 1)
      return head_ptr;

    Node<T> *current_node = head_ptr;
    size_t i{1};
    while (i < (desired_position - 1)) {
      if (current_node != nullptr) {
        current_node = current_node->next_node;
        i++;
      } else
        break;
    }
    return current_node;
  }

public:
  LinkedList() = default;
  ~LinkedList() { free_allocated_memory(); }

  LinkedList(const LinkedList &) = delete;
  LinkedList &operator=(const LinkedList &) = delete;

  void add_node(T data) {
    Node<T> *new_node = new Node<T>(data);
    new_node->next_node = head_ptr;
    head_ptr = new_node;
  }

  void delete_node() {
    if (!is_empty()) {
      Node<T> *temp_node = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp_node;
    } else {
      std::cerr << "Nothing to delete ! List is Empty" << "\n";
    }
  }

  void top_node() const {
    if (!is_empty()) {
      std::cout << "Head Node : " << head_ptr->data << "\n";
    } else
      std::cerr << "Nothing at top ! Head Node is Empty !" << "\n";
  }

  void insert_at_specific_position(T data, std::size_t insert_position) {
    if (insert_position == 0) {
      std::cerr << insert_position << " is an invalid position to insert."
                << "\n";
      return;
    }

    Node<T> *current_node = check_position(insert_position);
    if (current_node == nullptr && insert_position != 1) {
      std::cerr << "Trying to insert on an invalid position : "
                << insert_position << "\n";
      return;
    }

    if (!is_empty()) {
      Node<T> *new_node = new Node<T>(data);
      if (insert_position > 1 && current_node->next_node != nullptr) {
        new_node->next_node = current_node->next_node;
        current_node->next_node = new_node;
      } else if (insert_position > 1 && current_node->next_node == nullptr) {
        current_node->next_node = new_node;
        new_node->next_node = nullptr;
      } else if (insert_position == 1) {
        new_node->next_node = head_ptr;
        head_ptr = new_node;
      }
    } else if (insert_position == 1) {
      Node<T> *new_node = new Node<T>(data);
      new_node->next_node = head_ptr;
      head_ptr = new_node;
    } else {
      std::cerr << "Insertion in to an Empty List" << "\n";
    }
  }

  void delete_at_specific_position(std::size_t delete_position) {
    if (delete_position == 0) {
      std::cerr << delete_position << " is an invalid position to delete."
                << "\n";
      return;
    }

    if (!is_empty()) {
      Node<T> *current_node = check_position(delete_position);
      Node<T> *temp_node = nullptr;

      if ((current_node == nullptr || current_node->next_node == nullptr) &&
          delete_position > 1) {
        std::cerr << "The Position " << delete_position
                  << " doesn't exists on the list" << "\n";
        return;
      }

      if (delete_position > 1) {
        temp_node = current_node->next_node;
        current_node->next_node = current_node->next_node->next_node;
        delete temp_node;
      } else if (delete_position == 1 && current_node != nullptr) {
        temp_node = head_ptr;
        head_ptr = head_ptr->next_node;
        delete temp_node;
      }
    } else {
      std::cerr << "List is empty Nothing to delete !" << "\n";
    }

    return;
  }

  void reverse_list() {
    if (!is_empty()) {
      Node<T> *current_node = head_ptr;
      Node<T> *prev_node = nullptr;
      Node<T> *node_ahead = nullptr;

      while (current_node != nullptr) {
        node_ahead = current_node->next_node;
        current_node->next_node = prev_node;
        prev_node = current_node;
        current_node = node_ahead;
      }
      head_ptr = prev_node;
    } else {
      std::cerr << "List is Empty ! Nothing to reverse !" << "\n";
    }
  }

  void print_list() const {
    if (!is_empty()) {
      Node<T> *current_node = head_ptr;
      std::cout << "List : ";
      while (current_node != nullptr) {
        std::cout << current_node->data << "\t";
        current_node = current_node->next_node;
      }
      std::cout << "\n";
    } else
      std::cerr << "List is Empty ! Nothing to Print" << "\n";
  }
};

int main(void) {
  LinkedList<int> list;
  list.add_node(24);
  list.add_node(34);
  list.add_node(64);
  list.print_list();
  list.reverse_list();
  list.print_list();
  return 0;
}
