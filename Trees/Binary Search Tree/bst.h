#ifndef BST_H
#define BST_H

#include <iostream>
#include <queue>

template <typename T> struct Node {
    T value;
    Node<T>* left;
    Node<T>* right;
    Node(T v) : value(v), left(nullptr), right(nullptr) {}
};

template <typename T> struct BinarySearchTree {
    Node<T>* root_node = nullptr;

    BinarySearchTree() = default;
    ~BinarySearchTree() {
        free_allocated_memory();
    }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    bool is_empty() const {
        return root_node == nullptr;
    }

    void free_allocated_memory_helper(Node<T>* node) {
        if (node == nullptr) {
            return;
        }

        free_allocated_memory_helper(node->left);
        free_allocated_memory_helper(node->right);

        delete node;
    }

    void free_allocated_memory() {
        if (is_empty()) {
            return;
        }

        free_allocated_memory_helper(root_node);
        root_node = nullptr;
    }

    bool search_helper(Node<T>* current_node, T value) const {
        if (current_node == nullptr) {
            return false;
        }

        if (current_node->value == value) {
            return true;
        }

        if (current_node->value > value) {
            return search_helper(current_node->left, value);
        }
        return search_helper(current_node->right, value);
    }

    bool search(T value) const {
        if (is_empty()) {
            return false;
        }
        return search_helper(root_node, value);
    }

    void insert_helper(Node<T>* current_node, Node<T>* new_node) {
        if (current_node->value > new_node->value) {
            if (current_node->left == nullptr) {
                current_node->left = new_node;
                return;
            }
            insert_helper(current_node->left, new_node);
            return;
        }

        if (current_node->right == nullptr) {
            current_node->right = new_node;
            return;
        }

        insert_helper(current_node->right, new_node);
    }

    void insert(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (is_empty()) {
            root_node = new_node;
            return;
        }
        insert_helper(root_node, new_node);
    }

    void print() const {
        std::cout << "Binary Search Tree : ";
        if (is_empty()) {
            std::cout << "Empty Binary Search Tree !" << '\n';
            return;
        }

        std::queue<Node<T>*> printingQueue;
        printingQueue.push(root_node);
        std::cout << '\n' << "    ";
        while (!printingQueue.empty()) {
            std::size_t pops = printingQueue.size();
            while (pops > 0) {
                Node<T>* front = printingQueue.front();
                if (front->left != nullptr)
                    printingQueue.push(front->left);
                if (front->right != nullptr)
                    printingQueue.push(front->right);

                std::cout << front->value << '\t';
                printingQueue.pop();
                pops--;
            }
            std::cout << '\n';
        }
    }
};

#endif
