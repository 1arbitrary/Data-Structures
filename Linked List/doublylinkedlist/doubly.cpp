#include <iostream>
#include <stdexcept>

template <typename T> struct Node {
  T data;
  Node<T> *next_node;
  Node<T> *prev_node;
  Node(T d) : data(d), next_node(nullptr), prev_node(nullptr) {}
};

template <typename T> struct LinkedList {
  Node<T> *head_ptr = nullptr;

  LinkedList() = default;
  ~LinkedList() { free_allocated_memory(); }

  LinkedList(const LinkedList &) = delete;
  LinkedList &operator=(const LinkedList &) = delete;

  bool is_empty() const { return head_ptr == nullptr; }

  void free_allocated_memory() {
    while (!is_empty()) {
      Node<T> *temp_node = head_ptr;
      head_ptr = head_ptr->next_node;
      delete temp_node;
    }
  }

  void add_node(T data) {
    Node<T> *new_node = new Node<T>(data);
    if (is_empty()) {
      head_ptr = new_node;
      return;
    }

    new_node->next_node = head_ptr;
    head_ptr->prev_node = new_node;
    head_ptr = new_node;
  }

  void remove_head() {
    if (is_empty()) {
      throw std::out_of_range("Attempt To Delete An Empty List");
    }

    Node<T> *temp_node = head_ptr;
    head_ptr = head_ptr->next_node;
    if (head_ptr != nullptr) {
      head_ptr->prev_node = nullptr;
    }
    delete temp_node;
  }

  Node<T> *validate_or_throw(std::size_t position) {
    if (position == 0) {
      throw std::out_of_range("Attempt To Validate Invalid Address");
    }

    if (position == 1 && is_empty()) {
      throw std::out_of_range("Attempt To Validate Empty Head Node");
    } else if (position == 1 && !is_empty()) {
      return head_ptr;
    }

    if (position > 1) {
      std::size_t i{1};
      Node<T> *current_node = head_ptr;
      while (i < position && current_node != nullptr) {
        current_node = current_node->next_node;
        i++;
      }

      if (current_node == nullptr) {
        throw std::out_of_range(
            "Attempt To Return Node At An Invalid Position");
      } else {
        return current_node;
      }
    }
    throw std::out_of_range("Exception");
  }

  void insert_at_pos(std::size_t position, T data) {
    if (position == 1 && is_empty()) {
      Node<T> *new_node = new Node<T>(data);
      head_ptr = new_node;
      return;
    } else if (position == 1 && !is_empty()) {
      Node<T> *new_node = new Node<T>(data);
      new_node->next_node = head_ptr;
      head_ptr->prev_node = new_node;
      head_ptr = new_node;
      return;
    }

    if (position > 1) {
      Node<T> *validated_node = validate_or_throw(position);
      Node<T> *new_node = new Node<T>(data);

      new_node->next_node = validated_node;
      validated_node->prev_node->next_node = new_node;
      new_node->prev_node = validated_node->prev_node;
      validated_node->prev_node = new_node;
      return;
    }
  }

  void delete_at_position(std::size_t position) {
    Node<T> *validated_node = validate_or_throw(position);
    if (position == 1) {
      Node<T> *temp_node = validated_node;
      head_ptr = validated_node->next_node;
      if (head_ptr != nullptr) {
        head_ptr->prev_node = nullptr;
      }
      delete temp_node;
      return;
    }

    if (position > 1) {
      Node<T> *temp_node = validated_node;

      if (validated_node->next_node != nullptr) {
        validated_node->next_node->prev_node = validated_node->prev_node;
      }

      if (validated_node->prev_node != nullptr) {
        validated_node->prev_node->next_node = validated_node->next_node;
      }
      delete temp_node;
    }
  }

  void print() const {
    Node<T> *current_node = head_ptr;
    Node<T> *last_node = nullptr;

    std::cout << "List According To Next : ";
    while (current_node != nullptr) {
      std::cout << current_node->data << "\t";
      last_node = current_node;
      current_node = current_node->next_node;
    }

    std::cout << "\nList According To Tail : ";
    while (last_node != nullptr) {
      std::cout << last_node->data << "\t";
      last_node = last_node->prev_node;
    }
    std::cout << "\n";
  }
};

int main(void) {
  LinkedList<int> list;

  list.add_node(22);
  list.add_node(33);
  list.add_node(44);
  list.add_node(55);
  list.print();

  list.insert_at_pos(2, 999);
  list.print();

  list.delete_at_position(3);
  list.print();

  list.delete_at_position(4);
  list.print();

  list.delete_at_position(1);
  list.print();

  list.delete_at_position(1);
  list.print();

  list.delete_at_position(1);
  list.print();

  list.delete_at_position(1);
  list.print();

  return 0;
}
