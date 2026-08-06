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
  std::array<T, 4> keys { };
  std::array<Node<T>*, 5> children { };
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

  Node<T>* InsertIntoSubtree(Node<T>* node, const T& value)
  {
    assert(node);
    // I think i mainly have to insert and repair if needed .
    // The first step is to find the suitable place for insertion
    // make sure to enforce the no duplicates policy
  }

  Node<T>* DeleteFromSubtree(Node<T>* node, const T& value)
  {
    // find the value then do your thing with the edge cases
  }

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
      std::println("Nothing to Delete");
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

    while (!printing_queue.empty()) { }
  }
};

#endif
