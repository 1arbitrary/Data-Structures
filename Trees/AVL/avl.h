#ifndef AVL_H
#define AVL_H

#include <print>
#include <queue>

template <typename T>
struct Node {
    T value;
    int height;
    int balance_factor;
    Node<T> *left;
    Node<T> *right;
    Node(T v) : value(v), height(0), balance_factor(0), left(nullptr), right(nullptr) {}
};

template <typename T>
struct AVLTree {
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

    Node<T> *rotate_left(Node<T> *current_node) {
        Node<T> *temp = current_node->right;
        current_node->right = temp->left;
        temp->left = update(current_node);
	return update(temp);
    }

    Node<T> *rotate_right(Node<T> *current_node) {
        Node<T> *temp = current_node->left;
        current_node->left = temp->right;
        temp->right = update(current_node);
	return update(temp);
    }

    Node<T> *balance(Node<T> *current_node) {
        if ((-1 <= current_node->balance_factor) && current_node->balance_factor <= 1) {
            return current_node;
        }

        if (current_node->balance_factor > 1) {
            if (current_node->left->balance_factor < 0) {
                current_node->left = rotate_left(current_node->left);
            }
            return rotate_right(current_node);
        }
        if (current_node->right->balance_factor > 0) {
            current_node->right = rotate_right(current_node->right);
        }
        return rotate_left(current_node);
    }

    int get_height(Node<T> *current_node) const {
        return (current_node) ? current_node->height : -1;
    }

    Node<T> *update(Node<T> *current_node) {
        if (!current_node) {
            return current_node;
        }
        int left_height = get_height(current_node->left);
        int right_height = get_height(current_node->right);
        current_node->height = 1 + std::max(left_height, right_height);
        current_node->balance_factor = left_height - right_height;

        return current_node;
    }

    Node<T> *insert_helper(Node<T> *current_node, T value) {
        if (!current_node) {
            return new Node<T>(value);
        } else if (value == current_node->value) {
            return current_node;
        }

        if (value < current_node->value) {
            current_node->left = insert_helper(current_node->left, value);
            return balance(update(current_node));
        }
        current_node->right = insert_helper(current_node->right, value);
        return balance(update(current_node));
    }

    void insert(T value) { root_node = insert_helper(root_node, value); }

    void print() const {
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
