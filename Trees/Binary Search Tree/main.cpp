#include "bst.h"

int main(void) {
    BinarySearchTree<int> t;

    int arr[] = {15, 7, 20, 3, 9, 18, 25, 7, 15, 20, 3, 9, 10, 12, 10, 12, 25, 25, 1, 1};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arr_size; i++) {
        t.insert(arr[i]);
    }
    t.print();

    int tests[] = {10, 18, 1, 25, -5, 100, 3};
    int tests_size = sizeof(tests) / sizeof(tests[0]);

    std::cout << '\n';
    for (int i = 0; i < tests_size; i++) {
        std::cout << "Searching for " << tests[i] << " : " << t.search_with_duplicates(tests[i])
                  << '\n';
    }

    return 0;
}
