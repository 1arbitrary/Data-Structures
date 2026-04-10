#include "bst.h"

int main(void) {
    BinarySearchTree<int> t;

    int arr[] = {15, 7, 20, 3, 9, 18, 25, 7, 15, 20, 3, 9, 10, 12, 10, 12, 25, 25, 1, 1};
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < arr_size; i++) {
      t.insert(arr[i]);
    }
    t.print();

    t.delete_func(20);
    t.delete_func(20);
    t.delete_func(7);
    t.delete_func(1);
    t.delete_func(7);
    t.delete_func(15);
    t.print();

    return 0;
}
