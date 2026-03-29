#include "bst.h"

int main(void) {
    BinarySearchTree<int> t;
    int arr[] = {15, 7, 20, 3, 9, 18, 25, 1, 12, 10, 30};

    for (int i = 0; i < 11; i++) {
        t.insert(arr[i]);
    }

    t.print();
    int tests[] = {10, 5, 15, 3, 7, 12, 18, 6, 8, 11, 13, 17, 0, 1, 20, 25, -5, 100};

    for (int i = 0; i < 18; i++) {
        std::cout << "Searching for : " << tests[i] << " " << std::boolalpha << t.search(tests[i])
                  << std::noboolalpha << '\n';
    }

    return 0;
}
