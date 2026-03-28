#include <algorithm>
#include <ios>
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

  bool
  search_helper (Node<T> *current_node, T value) const 
  {
    if (current_node == nullptr)
      {
        return false;
      }

    if (current_node->value == value)
      {
        return true;
      }

    bool left = search_helper (current_node->left, value);
    bool right = search_helper (current_node->right, value);

    return left || right;
  }

  bool
  search (T value) const
  {
    if (is_empty ())
      {
        std::cerr << "Not Found ! Empty Tree" << '\n';
        return false;
      }
    return search_helper (root_node, value);
  }  

  void
  print () const
  {
    std::cout << "Binary Tree : " << '\n' << '\n';
    if (is_empty ())
      {
        std::cout << "Empty Binary Tree !" << '\n';
        return;
      }

    std::queue<Node<T> *> printingQueue;
    printingQueue.push (root_node);

    while (!printingQueue.empty ())
      {
        std::size_t pops = printingQueue.size ();
        while (pops > 0)
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
            pops--;
          }
        std::cout << '\n' << '\n';
      }
  }

  std::size_t
  total_nodes_helper (const Node<T> *node) const
  {
    if (node == nullptr)
      {
        return 0;
      }

    std::size_t nodes_on_left = total_nodes_helper (node->left);
    std::size_t nodes_on_right = total_nodes_helper (node->right);

    return 1 + nodes_on_left + nodes_on_right;
  }

  std::size_t
  total_nodes () const
  {
    if (is_empty ())
      {
        return 0;
      }

    return total_nodes_helper (root_node);
  }

  int
  sum_of_nodes_helper (const Node<T> *node) const
  {
    if (node == nullptr)
      {
        return 0;
      }

    int left_sum = sum_of_nodes_helper (node->left);
    int right_sum = sum_of_nodes_helper (node->right);

    return node->value + left_sum + right_sum;
  }

  int
  sum_of_nodes () const
  {
    if (is_empty ())
      {
        return 0;
      }
    return sum_of_nodes_helper (root_node);
  }

  std::size_t
  count_leaf_nodes_helper (const Node<T> *node) const
  {
    if (node == nullptr)
      {
        return 0;
      }

    std::size_t left_leaf_nodes = count_leaf_nodes_helper (node->left);
    std::size_t right_leaf_nodes = count_leaf_nodes_helper (node->right);

    return (node->right == nullptr && node->left == nullptr)
               ? (1 + left_leaf_nodes + right_leaf_nodes)
               : left_leaf_nodes + right_leaf_nodes;
  }

  std::size_t
  count_leaf_nodes () const
  {
    if (is_empty ())
      {
        return 0;
      }
    return count_leaf_nodes_helper (root_node);
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
  std::cout << '\n' << "Total Nodes : " << t.total_nodes ();
  std::cout << '\n' << "Sum of Nodes : " << t.sum_of_nodes ();
  std::cout << '\n' << "No. of Leaf Nodes : " << t.count_leaf_nodes ();
  std::cout << "\nSearch " << 22  << " : " << std::boolalpha << t.search (22) << std::noboolalpha << '\n';
  std::cout << "Search " << 40 << " : " << std::boolalpha << t.search(40) << std::noboolalpha << '\n';  

  return 0;
}
