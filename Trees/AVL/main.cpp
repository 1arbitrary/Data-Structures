#include "avl.h"

int main(void) {
    AVLTree<int> t;

    t.insert(80);
    t.print();

    t.insert(90);
    t.print();

    t.insert(50);
    t.print();

    t.insert(40);
    t.print();
    
    t.insert(60);
    t.print();

    t.insert(70);
    t.print();
    
    return 0;
}
