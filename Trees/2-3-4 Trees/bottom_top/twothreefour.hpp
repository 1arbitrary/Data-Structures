#include <array>
#include <cassert>
#include <concepts>
#include <print>
#include <queue>

#ifndef TWOTHREEFOUR_H
#define TWOTHREEFOUR_H

template <typename T>
  requires std::totally_ordered<T>
struct Node {
  public:
  std::size_t key_count { 0 };
  std::array<T, 4> keys {};
  std::array<Node<T>*, 4> children {};
};

template <typename T>
  requires std::totally_ordered<T>
struct TwoThreeFour {
  private:
  Node<T>* root_node = nullptr;

  void FreeAllocatedMemory()
  {
    if (!root_node) {
      return;
    }

    std::queue<Node<T>*> deletion_queue;
    deletion_queue.push(root_node);

    while (!deletion_queue.empty()) {
      std::size_t children_left { deletion_queue.size() };
      while (children_left != 0) {
        Node<T>* front_node = deletion_queue.front();
        for (std::size_t i { 0 }; i <= front_node->key_count; i++) {
          if (front_node->children[i]) {
            deletion_queue.push(front_node->children[i]);
          }
        }
        deletion_queue.pop();
        delete front_node;
        children_left--;
      }
    }
    root_node = nullptr;
  }

  void ShiftKeysArrForward(std::array<T, 4>& arr, std::size_t start, std::size_t end)
  {
    for (std::size_t i { end }; i > start; i--) {
      arr[i] = arr[i - 1];
    }
  }

  void ShiftChildArrForward(std::array<Node<T>*, 4>& arr, std::size_t start, std::size_t end)
  {
    for (std::size_t i { end }; i > 0; i--) {
      arr[i] = arr[i - 1];
    }
  }

  Node<T>* repair_node(Node<T>* node)
  {
    std::size_t mid { 1 };

    Node<T>* new_subroot = new Node<T>();
    Node<T>* right_child = new Node<T>();

    new_subroot->keys[new_subroot->key_count++] = node->keys[mid];

    right_child->keys[0] = node->keys[mid + 1];
    right_child->keys[1] = node->keys[mid + 2];

    right_child->key_count = 2;
    node->key_count = 1;

    new_subroot->children[0] = node;
    new_subroot->children[1] = right_child;

    return new_subroot;
  }

  Node<T>* InsertIntoSubtree(Node<T>* node, const T& value)
  {
    assert(node && (node->key_count <= 3));
    std::size_t i { 0 };
    while (i <= node->key_count) {
      if (value == node->keys[i]) {
        return node;
      }
      if (value < node->keys[i]) {
        if (node->children[i]) {
          node->children[i] = InsertIntoSubtree(node->children[i], value);
          return node;
        }
        ShiftKeysArrForward(node->keys, i, node->key_count);
        ShiftChildArrForward(node->children, i, node->key_count);
        node->keys[i] = value;
        node->key_count++;
        // return (node->key_count == 4) ? repair_node(node) : node;
        //  maybe i can use breaks to manage it
        break;
      }
      if (value > node->keys[i]) {
        if (i == node->key_count) {
          if (node->children[i]) {
            node->children[i] = InsertIntoSubtree(node->children[i], value);
            return node;
          } else {
            node->keys[node->key_count++] = value;
          }
          // return (node->key_count == 4) ? repair_node(node) : node;
          // one break here too maybe
          break;
        }
        i++;
      }
    }
    // loop ends here check here
    if (node->key_count == 4) {
      Node<T>* repaired_node = repair_node(node);
      std::println("test print : {}", node->keys[i]);
      node->keys[i] = repaired_node->keys[0];
      // children transfer
      node->children[i] = repaired_node->children[0];
      node->children[i+1] = repaired_node->children[1];
    }
    return node;
  }

  // Node<T>* DeleteFromSubtree(Node<T>* node, const T& value);

  public:
  TwoThreeFour() = default;
  ~TwoThreeFour() { FreeAllocatedMemory(); }

  TwoThreeFour(const TwoThreeFour&) = delete;
  TwoThreeFour& operator=(const TwoThreeFour&) = delete;

  TwoThreeFour(TwoThreeFour&&) = delete;
  TwoThreeFour& operator=(TwoThreeFour&&) = delete;

  void delete_fn(const T& value)
  {
    if (!root_node) {
      std::println("Nothing to Delete !");
      return;
    }
    root_node = DeleteFromSubtree(root_node, value);
  }

  void insert(const T& value)
  {
    if (!root_node) {
      root_node = new Node<T>();
      root_node->keys[root_node->key_count++] = value;
      return;
    }
    root_node = InsertIntoSubtree(root_node, value);
  }

  void print() const
  {
    std::println("2-3-4 Tree : ");
    if (!root_node) {
      std::print("Empty Tree");
      return;
    }

    std::queue<Node<T>*> printing_queue;
    printing_queue.push(root_node);

    std::size_t i { 0 };
    while (!printing_queue.empty()) {
      Node<T>* front_node = printing_queue.front();
      std::size_t active_window = printing_queue.size();
      std::size_t current_window { 0 };
      while (true) {
        if (front_node->children[i]) {
          printing_queue.push(front_node->children[i]);
        }

        if (i >= front_node->key_count) {
          if (current_window == active_window) {
            std::println("\t");
          }
          i = 0;
          printing_queue.pop();
          current_window++;

          if (current_window == active_window) {
            std::println();
          }
          if (printing_queue.size() > 0) {
            front_node = printing_queue.front();
          }
          break;
        }
        std::print("{} ", front_node->keys[i]);
        i++;
      }
      current_window = 0;
    }
  }
};

#endif
