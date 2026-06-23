#ifndef TWOTHREEFOUR_H

#include <array>
#include <compare>
#include <concepts>
#include <print>
#include <queue>

template <typename T>
    requires std::totally_ordered<T>
struct Node {
private:
    static constexpr std::size_t keys_arr_size = 3;

public:
    std::size_t key_count = 0;
    std::array<T, keys_arr_size> keys { };
    std::array<Node<T>*, keys_arr_size + 1> children { };
};

template <typename T>
    requires std::totally_ordered<T>
struct TwoThreeFour {
private:
    using Size = std::size_t;
    Node<T>* root_node = nullptr;

    void FreeAllocatedSubtree(Node<T>* node)
    {
        Size i { 0 };
        while (i <= node->key_count) {
            bool can_descend = node->children[i];
            if (can_descend) {
                FreeAllocatedSubtree(node->children[i]);
                node->children[i] = nullptr;
            }
            if (i == node->key_count) {
                delete node;
                node = nullptr;
                return;
            }
            i++;
        }
    }

    void Free_Allocated_Memory()
    {
        FreeAllocatedSubtree(root_node);
        root_node = nullptr;
    }

    void ShiftKeysArr(std::array<T, 3>& arr, Size begin, Size end)
    {
        for (Size i { end }; begin < i; i--) {
            arr[i] = arr[i - 1];
        }
    }

    void ShiftChildrenArr(std::array<Node<T>*, 4>& arr, Size begin, Size end)
    {
        for (Size i { end }; begin < i; i--) {
            arr[i] = arr[i - 1];
        }
    }

    Node<T>* SplitNode(Node<T>* left_node)
    {
        Node<T>* subtree_root = new Node<T>();
        Node<T>* right_node = new Node<T>();

        right_node->children[0] = left_node->children[2];
        right_node->children[1] = left_node->children[3];

        left_node->children[2] = nullptr;
        left_node->children[3] = nullptr;

        right_node->keys[right_node->key_count++] = left_node->keys[--left_node->key_count];
        subtree_root->keys[subtree_root->key_count++] = left_node->keys[--left_node->key_count];

        subtree_root->children[0] = left_node;
        subtree_root->children[1] = right_node;

        return subtree_root;
    }

    void Delete_helper(Node<T>* node, const T& value);

    Node<T>* RepairNode(Node<T>* node, const T& value, Size& i)
    {
        Node<T>* splitted_node = SplitNode(node->children[i]);
        ShiftKeysArr(node->keys, i, node->key_count);

        node->keys[i] = splitted_node->keys[0];
        node->key_count++;

        ShiftChildrenArr(node->children, i, node->key_count);
        node->children[i] = splitted_node->children[0];
        node->children[i + 1] = splitted_node->children[1];

        delete splitted_node;
        splitted_node = nullptr;

        i = 0;
        while ((i < node->key_count) && value > node->keys[i]) {
            i++;
        }

        return node;
    }

    Node<T>* InsertIntoSubtree(Node<T>* node, const T& value)
    {
        if (node == root_node && root_node->key_count == 3) {
            return InsertIntoSubtree(SplitNode(node), value);
        }

        Size i { 0 };
        while ((i < node->key_count)) {
            std::strong_ordering cmp = value <=> node->keys[i];
            if (cmp == std::strong_ordering::equal) {
                return node;
            } else if (cmp == std::strong_ordering::greater) {
                i++;
            } else {
                break;
            }
        }

        bool can_descend = node->children[i];
        if (can_descend) {
            bool needs_repair = (node->children[i]) && ((node->children[i])->key_count == 3);
            if (needs_repair) {
                Node<T>* repaired_node = RepairNode(node, value, i);
                node->children[i] = InsertIntoSubtree(repaired_node->children[i], value);
            } else {
                node->children[i] = InsertIntoSubtree(node->children[i], value);
            }
            return node;
        }

        if (i == node->key_count) {
            node->keys[node->key_count++] = value;
            return node;
        }

        ShiftKeysArr(node->keys, i, node->key_count);
        node->keys[i] = value;
        node->key_count++;
        return node;
    }

public:
    TwoThreeFour() = default;
    ~TwoThreeFour() { Free_Allocated_Memory(); }

    TwoThreeFour(const TwoThreeFour&) = delete;
    TwoThreeFour& operator=(const TwoThreeFour) = delete;

    TwoThreeFour(TwoThreeFour&&) = delete;
    TwoThreeFour& operator=(TwoThreeFour&&) = delete;

    void DeleteSubtree(const T& value)
    {
        if (!root_node) {
            return;
        }
        root_node = Delete_helper(root_node, value);
    }

    void insert(const T& value)
    {
        if (!root_node) {
            root_node = new Node<T>;
            root_node->keys[root_node->key_count++] = value;
            return;
        }
        root_node = InsertIntoSubtree(root_node, value);
    }

    void print() const
    {
        std::print("2-3-4 Tree : ");
        if (!root_node) {
            std::print("Empty Tree !");
            return;
        }
        std::queue<Node<T>*> printing_queue;
        printing_queue.push(root_node);

        Size i { 0 };
        std::println("\t");
        while (!printing_queue.empty()) {
            Size units = printing_queue.size();
            std::print("[ ");
            while (units != 0) {
                Node<T>* node = printing_queue.front();
                if (node->children[i]) {
                    printing_queue.push(node->children[i]);
                }

                if (i < node->key_count) {
                    std::print("{} ", node->keys[i++]);
                } else {
                    i = 0;
                    units--;
                    printing_queue.pop();
                    std::print("]");
                }
            }
            std::println(" ]");
        }
    }
};
#endif
