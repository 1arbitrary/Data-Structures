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

    void free_allocated_memory_helper(Node<T>** current_node) {
        if (!*current_node) {
            return;
        }

        free_allocated_memory_helper(&(*current_node)->left);
        free_allocated_memory_helper(&(*current_node)->right);

        delete *current_node;
        *current_node = nullptr;
    }

    void free_allocated_memory() {
        if (!root_node) {
            return;
        }
        free_allocated_memory_helper(&root_node);
        root_node = nullptr;
    }

    Node<T>** search_helper(Node<T>** current_node, T value) {
        if (!*current_node) {
            return current_node;
        }

        if ((*current_node)->value == value) {
            return current_node;
        }

        if ((*current_node)->value > value) {
            return search_helper(&(*current_node)->left, value);
        }
        return search_helper(&(*current_node)->right, value);
    }

    Node<T>** search(Node<T>** starting_node, T value) {
        if (!starting_node) {
            return nullptr;
        }
        return search_helper(starting_node, value);
    }

    Node<T>** find_min(Node<T>** starting_node) {
        if (!starting_node || !*starting_node) {
            return starting_node;
        }

        while ((*starting_node)->left) {
            starting_node = &(*starting_node)->left;
        }

        return starting_node;
    }

    void insert(T value) {
        Node<T>** insert_node = search(&root_node, value);
        if (!*insert_node) {
            *insert_node = new Node<T>(value);
        }
    }

    void delete_func(T value) {
        Node<T>** node_tbd = search(&root_node, value);
        if (!node_tbd || !*node_tbd) {
            return;
        }

        if (!(*node_tbd)->left && !(*node_tbd)->right) {
            delete *node_tbd;
            *node_tbd = nullptr;
            return;
        }

        if ((*node_tbd)->left && !(*node_tbd)->right) {
            Node<T>* temp = *node_tbd;
            *node_tbd = (*node_tbd)->left;
            delete temp;
            return;
        }

        if (!(*node_tbd)->left && (*node_tbd)->right) {
            Node<T>* temp = *node_tbd;
            *node_tbd = (*node_tbd)->right;
            delete temp;
            return;
        }

        if ((*node_tbd)->left && (*node_tbd)->right) {
            Node<T>** min = find_min(&(*node_tbd)->right);
            Node<T>* temp = *min;
            (*node_tbd)->value = (*min)->value;
            (*min) = (*min)->right;
            delete temp;
        }
    }

    void print() const {
        std::cout << "Binary Search Tree : ";
        if (!root_node) {
            std::cout << "Empty" << '\n';
            return;
        }

        std::queue<Node<T>*> printingQueue;
        printingQueue.push(root_node);

        while (!printingQueue.empty()) {
	  std::size_t pops_available = printingQueue.size();
            while (pops_available > 0) {
                Node<T>* front_node = printingQueue.front();
                if (front_node->left) {
                    printingQueue.push(front_node->left);
                }

                if (front_node->right) {
                    printingQueue.push(front_node->right);
                }
                std::cout << front_node->value << "  ";
		printingQueue.pop();
                pops_available--;
            }
            std::cout << '\n';
        }
    }
};

#endif
