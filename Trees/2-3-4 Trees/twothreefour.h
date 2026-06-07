#include <array>
#include <concepts>
#include <print>

#ifndef TWOTHREEFOUR_H
template <typename T>
    requires std::totally_ordered<T>
struct Node {
private:
    static constexpr std::size_t keys_arr_size = 3;

public:
    std::size_t key_count = 0;
    std::array<T, keys_arr_size> keys { };
    std::array<Node<T> *, keys_arr_size + 1> children { };
};

template <typename T>
    requires std::totally_ordered<T>
struct TwoThreeFour {
private:
    Node<T> *root_node = nullptr;
    void free_allocated_memory_helper();

    void free_allocated_memory()
    {
        free_allocated_memory_helper(root_node);
        root_node = nullptr;
    }

    void delete_fn_helper(Node<T> *current_node, const T &value);

    Node<T> *insert_helper(Node<T> *current_node, const T &value)
    {
        if (!current_node) {
            current_node = new Node<T>();
            current_node->keys[current_node->key_count++] = value;
            return current_node;
        }

        if (current_node->key_count < 3) {
            std::size_t i { 0 };
            while (i < current_node->key_count) {
                // if greater
                if (value > current_node->keys[i]) {
                    if (current_node->children[++i]) {
                        current_node->children[i] = insert_helper(current_node->children[i], value);
                        return current_node;
                    }
                    if (i == current_node->key_count) {
                        current_node->keys[current_node->key_count++] = value;
                        return current_node;
                    }
                    continue; // this would be invoked when i != key_count
                }
                // if smaller
                if (value < current_node->keys[i]) {
                    if (current_node->children[i]) {
                        current_node->children[i] = insert_helper(current_node->children[i], value);
                        break;
                    }
                    shift_arr(current_node->keys, i, current_node->key_count);
                    current_node->keys[i] = value;
                    current_node->key_count++;
                    return current_node;
                }
            }
        }

        // After Insert is triggered
        if (current_node->key_count == 3) {
            // split here then insert
            current_node = insert_helper(split_node(current_node), value);
        }
        return current_node;
    }

    void shift_arr(std::array<T, 3> &arr, std::size_t begin, std::size_t end)
    {
        for (std::size_t i { end }; begin < i; i--) {
            arr[i] = arr[i - 1];
        }
    }

    Node<T> *split_node(Node<T> *left_node)
    {
        Node<T> *promoted_node = new Node<T>();
        Node<T> *right_node = new Node<T>();

        right_node->keys[right_node->key_count++] = left_node->keys[2];
        promoted_node->keys[promoted_node->key_count++] = left_node->keys[1];
        promoted_node->children[0] = left_node;
        promoted_node->children[1] = right_node;
        left_node->key_count = 1;

        return promoted_node;
    }

    void print_helper(Node<T> *current_node) const
    {
      
    }

public:
    TwoThreeFour() = default;
    // ~TwoThreeFour() { free_allocated_memory(); }

    TwoThreeFour(const TwoThreeFour &) = delete;
    TwoThreeFour &operator=(const TwoThreeFour) = delete;

    TwoThreeFour(TwoThreeFour &&) = delete;
    TwoThreeFour &operator=(TwoThreeFour &&) = delete;

    void delete_fn(const T &value) { root_node = delete_fn_helper(root_node, value); }
    void insert(const T &value) { root_node = insert_helper(root_node, value); }

    void print() const
    {
        std::print("2-3-4 Tree : ");
        if (!root_node) {
            std::print("Empty Tree !");
            return;
        }
	print_helper(root_node);
    }
};
#endif
