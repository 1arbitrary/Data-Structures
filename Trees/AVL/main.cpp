#include "avl.h"

int main(void) {
  AVLTree<int> t;

  t.insert(10);
  t.print();

  t.insert(12);
  t.print();
  
  t.insert(11);
  t.print();

  return 0;
}
