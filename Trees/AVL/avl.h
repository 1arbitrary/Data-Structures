#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <queue>

template <typename T> struct Node {
    std::size_t height;
    T value;
    Node<T>* left;
    Node<T>* right;
    Node(T v) : value(v), left(nullptr), right(nullptr), height(0) {}
};

template <typename T> struct AVLTree {
    Node<T>* root_node = nullptr;

    AVLTree() = default;
    ~AVLTree() {
        free_allocated_memory();
    }

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;

    void free_allocated_memory_helper(Node<T>* current_node) {
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

    Node<T>** search(Node<T>** current_node, T value) {
        if (!(*current_node)) {
            return current_node;
        }

        if ((*current_node)->value == value) {
            return current_node;
        }

        if ((*current_node)->value > value) {
            return search(&(*current_node)->left, value);
        }
        return search(&(*current_node)->right, value);
    }

    void insert(T value) {
        Node<T>** insert_at_node = search(&root_node, value);
        if (!(*insert_at_node)) {
            *insert_at_node = new Node<T>(value);
        }
    }

    void print() const {
        std::cout << "AVL Tree : ";
        if (!root_node) {
            std::cerr << "Empty AVL Tree" << '\n';
            return;
        }

        std::queue<Node<T>*> printingQueue;
        printingQueue.push(root_node);
        std::cout << '\n';

        while (!printingQueue.empty()) {
            std::size_t pops = printingQueue.size();
            while (pops > 0) {
                Node<T>* front_node = printingQueue.front();
                if (front_node->left) {
                    printingQueue.push(front_node->left);
                }
                if (front_node->right) {
                    printingQueue.push(front_node->right);
                }
                std::cout << front_node->value << '\t';
                printingQueue.pop();
                pops--;
            }
            std::cout << '\n';
        }
    }
};

#endif
