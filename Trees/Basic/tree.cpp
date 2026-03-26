#include <algorithm>
#include <iostream>
#include <queue>

template <typename T> struct Node
{
  T value;
  Node<T> *left;
  Node<T> *right;
  Node (T d) : value (d), left (nullptr), right (nullptr) {}
};

template <typename T> struct BinaryTree
{
  Node<T> *root_node = nullptr;
  BinaryTree () = default;
  ~BinaryTree ()
  {
    free_allocated_memory ();
  }

  BinaryTree (const BinaryTree &) = delete;
  BinaryTree &operator= (const BinaryTree &) = delete;

  bool
  is_empty () const
  {
    return root_node == nullptr;
  }

  void
  free_allocated_memory ()
  {
    if (is_empty ())
      return;

    std::queue<Node<T> *> deletionQueue;
    deletionQueue.push (root_node);

    while (!deletionQueue.empty ())
      {
        Node<T> *front_node = deletionQueue.front ();
        if (front_node->left != nullptr)
          {
            deletionQueue.push (front_node->left);
          }

        if (front_node->right != nullptr)
          {
            deletionQueue.push (front_node->right);
          }

        deletionQueue.pop ();
        delete front_node;
      }
    root_node = nullptr;
  }

  void
  insert (T value)
  {
    std::queue<Node<T> *> insertionQueue;
    Node<T> *new_node = new Node<T> (value);
    if (is_empty ())
      {
        root_node = new_node;
        return;
      }
    insertionQueue.push (root_node);
    while (!insertionQueue.empty ())
      {
        Node<T> *front_node = insertionQueue.front ();
        if (front_node->left == nullptr)
          {
            front_node->left = new_node;
            break;
          }
        insertionQueue.push (front_node->left);

        if (front_node->right == nullptr)
          {
            front_node->right = new_node;
            break;
          }
        insertionQueue.push (front_node->right);

        insertionQueue.pop ();
      }
  }

  int
  height_bfs () const
  {
    std::queue<Node<T> *> traversalQueue;
    if (is_empty ())
      {
        return -1;
      }

    traversalQueue.push (root_node);
    int levels{ 0 };
    while (!traversalQueue.empty ())
      {
        std::size_t number_of_pops = traversalQueue.size ();
        while (number_of_pops > 0)
          {
            Node<T> *front_node = traversalQueue.front ();
            if (front_node->left != nullptr)
              {
                traversalQueue.push (front_node->left);
              }

            if (front_node->right != nullptr)
              {
                traversalQueue.push (front_node->right);
              }

            traversalQueue.pop ();
            number_of_pops--;
          }
        levels++;
      }
    return levels - 1;
  }

  int
  height_dfs_helper (const Node<T> *node) const
  {
    if (node == nullptr)
      {
        return -1;
      }

    int left_height = height_dfs_helper (node->left);
    int right_height = height_dfs_helper (node->right);

    return (1 + std::max (left_height, right_height));
  }

  int
  height_dfs () const
  {
    if (is_empty ())
      {
        return -1;
      }

    return height_dfs_helper (root_node);
  }

  void
  print () const
  {
    std::cout << "Binary Tree : ";
    if (is_empty ())
      {
        std::cout << "Empty Binary Tree!" << '\n';
        return;
      }

    std::queue<Node<T> *> printingQueue;
    printingQueue.push (root_node);

    while (!printingQueue.empty ())
      {
        Node<T> *front_node = printingQueue.front ();
        if (front_node->left != nullptr)
          {
            printingQueue.push (front_node->left);
          }

        if (front_node->right != nullptr)
          {
            printingQueue.push (front_node->right);
          }

        std::cout << front_node->value << '\t';
        printingQueue.pop ();
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  BinaryTree<int> t;
  for (int i = 1; i <= 16; i++)
    {
      t.insert (i * 10);
    }
  t.print ();

  std::cout << "Tree Height(BFS) : " << t.height_bfs ();
  std::cout << '\n' << "Tree Height (DFS) : " << t.height_dfs ();

  return 0;
}
