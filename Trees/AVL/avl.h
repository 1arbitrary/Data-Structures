#ifndef AVL_H
#define AVL_H

#include <algorithm>
#include <print>
#include <queue>

template <typename T> struct Node {
  T value;
  int height;
  int balance_factor;
  Node<T> *left;
  Node<T> *right;
  Node(T v)
      : value(v), height(0), balance_factor(0), left(nullptr), right(nullptr) {}
};

template <typename T> struct AVLTree {
  Node<T> *root_node = nullptr;

  AVLTree() = default;
  ~AVLTree() { free_allocated_memory(); }

  AVLTree(const AVLTree &) = delete;
  AVLTree &operator=(const AVLTree &) = delete;

  void free_allocated_memory_helper(Node<T> *current_node) {
    if (!current_node) {
      return;
    }

    free_allocated_memory_helper(current_node->left);
    free_allocated_memory_helper(current_node->right);

    delete current_node;
  }

  void free_allocated_memory() {
    if (!root_node) {
      return;
    }
    free_allocated_memory_helper(root_node);
    root_node = nullptr;
  }

  void insert_helper(Node<T> **current_node, T value) {
    if (!(*current_node)) {
      *current_node = new Node<T>(value);
      return;
    }

    if ((*current_node)->value == value) {
      std::println("Value Already Exists");
      return;
    }

    if ((*current_node)->value > value) {
      insert_helper(&(*current_node)->left, value);
      return;
    }
    insert_helper(&(*current_node)->right, value);
  }

  void insert(T value) {
    if (!root_node) {
      root_node = new Node<T>(value);
      return;
    }
    insert_helper(&root_node, value);
  }

  void print() const {
    std::println("Height of tree : {}", root_node->height);
    std::println("Balance Factor of tree : {}", root_node->balance_factor);
    std::println("AVL Tree : ");

    if (!root_node) {
      std::print("Empty AVL Tree");
      return;
    }

    std::queue<Node<T> *> printingQueue;
    printingQueue.push(root_node);

    while (!printingQueue.empty()) {
      std::size_t pops = printingQueue.size();
      while (pops > 0) {
        Node<T> *front_node = printingQueue.front();
        if (front_node->left) {
          printingQueue.push(front_node->left);
        }
        if (front_node->right) {
          printingQueue.push(front_node->right);
        }
        std::print("{}\t", front_node->value);
        printingQueue.pop();
        pops--;
      }
      std::println();
    }
  }
};

#endif
