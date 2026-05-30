#include <concepts>
#include <print>

#ifndef TWOTHREEFOUR_H
template <typename T>
    requires std::totally_ordered<T>
struct Node {
   private:
    static constexpr std::size_t keys_arr_size = 4;

   public:
    std::size_t key_count;
    T keys[keys_arr_size];
    Node<T> *children[keys_arr_size + 1];
    Node() : key_count(0), keys({}), children({}) {}
};

template <typename T>
    requires std::totally_ordered<T>
struct TwoThreeFour {
   private:
    Node<T> *root_node = nullptr;
    void free_allocated_memory_helper();
    void free_allocated_memory() {
        free_allocated_memory_helper(root_node);
        root_node = nullptr;
    }

    void delete_fn_helper(Node<T> *current_node, const T &value);
    void insert_helper(Node<T> *current_node, const T &value);
    void shift_arr(T (&arr)[4], std::size_t begin, std::size_t end);
    void compare(T (&arr)[4]);
    void split_node();

   public:
    TwoThreeFour() = default;
    ~TwoThreeFour() { free_allocated_memory(); }

    TwoThreeFour(const TwoThreeFour &) = delete;
    TwoThreeFour &operator=(const TwoThreeFour) = delete;

    TwoThreeFour(TwoThreeFour &&) = delete;
    TwoThreeFour &operator=(TwoThreeFour &&) = delete;

    void delete_fn(const T &value) { root_node = delete_fn_helper(root_node, value); }
    void insert(const T &value) { root_node = insert_helper(root_node, value); }
    void print() const {
        std::print("2-3-4 Tree : ");
        if (!root_node) {
            std::print("Empty Tree !");
            return;
        }
    }
};
#endif
