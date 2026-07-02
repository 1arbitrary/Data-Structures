#ifndef TWOTHREEFOUR_HPP

#include <array>
#include <cassert>
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
    std::array<T, keys_arr_size> keys {};
    std::array<Node<T>*, keys_arr_size + 1> children {};
};

template <typename T>
    requires std::totally_ordered<T>
struct TwoThreeFour {
private:
    using Size = std::size_t;
    using Strong = std::strong_ordering;
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

    void ShiftKeysArrForward(std::array<T, 3>& arr, Size begin, Size end)
    {
        for (Size i { end }; begin < i; i--) {
            arr[i] = arr[i - 1];
        }
    }

    void ShiftKeysArrBackwards(std::array<T, 3>& arr, Size begin, Size end)
    {
        for (Size i { begin }; i < (end - 1); i++) {
            arr[i] = arr[i + 1];
        }
    }

    void ShiftChildrenArrForward(std::array<Node<T>*, 4>& arr, Size begin, Size end)
    {
        for (Size i { end }; begin < i; i--) {
            arr[i] = arr[i - 1];
        }
    }

    void ShiftChildrenArrBackwards(std::array<Node<T>*, 4>& arr, Size begin, Size end)
    {
        for (Size i { begin }; i < (end - 1); i++) {
            arr[i] = arr[i + 1];
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

    bool IsLeafNode(Node<T>* node)
    {
        Size i { 0 };

        while (i <= node->key_count) {
            bool can_descend = node->children[i];
            if (can_descend) {
                return false;
            }
            i++;
        }
        return true;
    }

    Node<T>* FindSmallestNodeParent(Node<T>* node)
    {
        if (!node) {
            return node;
        }

        Node<T>* smallest_node_parent = node;
        while ((smallest_node_parent->children[1])
            && (smallest_node_parent->children[1])->children[0]) {
            smallest_node_parent = smallest_node_parent->children[1];
        }
        return smallest_node_parent;
    }

    Node<T>* GetExistingSingleChild(std::array<Node<T>*, 4>& arr, Size& i)
    {
        if ((arr[i]) && !(arr[i + 1])) {
            return arr[i];
        } else {
            i++;
            return arr[i + 1];
        }
        return nullptr;
    }

    Node<T>* DeleteFromSubtree(Node<T>* node, const T& value)
    {
        assert(node);
        Size i { 0 };
        Strong cmp { Strong::less };
        while (i < node->key_count) {
            cmp = value <=> node->keys[i];
            if (cmp == Strong::greater) {
                i++;
            } else {
                break;
            }
        }

        if (cmp == Strong::equal) {
            if (IsLeafNode(node)) {
                if (node->key_count == 1) {
                    delete node;
                    node = nullptr;
                    return node;
                }
                ShiftKeysArrBackwards(node->keys, i, node->key_count);
                node->key_count--;
                return node;
            } else if (!IsLeafNode(node)) {
                bool single_child = (node->children[i] && !node->children[i + 1])
                    || (!node->children[i] && node->children[i + 1]);
                bool multiple_children = node->children[i] && node->children[i + 1];
                if (single_child) {
                    Node<T>* existing_child = GetExistingSingleChild(node->children, i);
                    node->keys[i] = existing_child->keys[0];
                    if (IsLeafNode(existing_child) && node->children[i]->key_count == 1) {
                        delete existing_child;
                        node->children[i] = nullptr;
                        return node;
                    }
                    ShiftKeysArrBackwards(existing_child->keys, i, existing_child->key_count);
                    ShiftChildrenArrBackwards(
                        existing_child->children, i, existing_child->key_count);
                    existing_child->key_count--;
                    // make sure to cleanup
                    return node;
                } else if (multiple_children) {
                    Node<T>* smallest_node_parent = FindSmallestNodeParent(node);
                    assert(smallest_node_parent->children[1]); // redundant but okay
                    node->keys[i] = smallest_node_parent->children[1]
                                        ->keys[0]; // replacement from right subtree
                    if (IsLeafNode(smallest_node_parent->children[0])
                        && smallest_node_parent->children[0]->key_count == 1) {
                        delete smallest_node_parent->children[0];
                        smallest_node_parent->children[0] = nullptr;
                        return node;
                    }
                    ShiftKeysArrBackwards(node->keys, i, node->key_count);
                    ShiftChildrenArrBackwards(node->children, i, node->key_count);
                    node->key_count--;
                    return node;
                }
            }
        }

        if (!node->children[i]) {
            std::println("{} doesn't exist in the tree.", value);
        } else {
            node->children[i] = DeleteFromSubtree(node->children[i], value);
        }
        return node;
    }

    Node<T>* RepairNode(Node<T>* node, const T& value, Size& i)
    {
        Node<T>* splitted_node = SplitNode(node->children[i]);
        ShiftKeysArrForward(node->keys, i, node->key_count);

        node->keys[i] = splitted_node->keys[0];
        node->key_count++;

        ShiftChildrenArrForward(node->children, i, node->key_count);
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
            Strong cmp = value <=> node->keys[i];
            if (cmp == Strong::equal) {
                return node;
            } else if (cmp == Strong::greater) {
                i++;
            } else {
                break;
            }
        }

        bool can_descend = node->children[i];
        if (can_descend) {
            bool needs_repair = (node->children[i])->key_count == 3;
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

        ShiftKeysArrForward(node->keys, i, node->key_count);
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

    void Delete(const T& value)
    {
        if (!root_node) {
            return;
        }
        root_node = DeleteFromSubtree(root_node, value);
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
