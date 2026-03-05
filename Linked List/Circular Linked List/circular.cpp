#include <iostream>
#include <stdexcept>

template <typename T> struct Node
{
  T data;
  Node<T> *next_node;
  Node (T d) : data (d), next_node (nullptr) {}
};

template <typename T> struct LinkedList
{
  Node<T> *head_ptr = nullptr;
  Node<T> *last_node = nullptr;

  LinkedList () = default;
  ~LinkedList ()
  {
    free_allocated_memory ();
  }

  LinkedList (const LinkedList &) = delete;
  LinkedList &operator= (const LinkedList &) = delete;

  bool
  is_empty () const
  {
    return head_ptr == nullptr;
  }

  void
  free_allocated_memory ()
  {
    if (is_empty ())
      {
        return;
      }
    last_node->next_node = nullptr;
    while (head_ptr != nullptr)
      {
        Node<T> *temp_node = head_ptr;
        head_ptr = head_ptr->next_node;
        delete temp_node;
      }
  }

  void
  insert_node (T data)
  {
    Node<T> *new_node = new Node<T> (data);
    if (is_empty ())
      {
        last_node = new_node;
      }
    new_node->next_node = head_ptr;
    head_ptr = new_node;
    last_node->next_node = head_ptr;
  }

  void
  delete_node ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Delete On An Empty List");
      }

    Node<T> *temp_node = head_ptr;
    head_ptr = head_ptr->next_node;
    if (temp_node == head_ptr)
      {
        head_ptr = nullptr;
        last_node = nullptr;
        delete temp_node;
        return;
      }
    delete temp_node;
    last_node->next_node = head_ptr;
  }

  void
  print () const
  {
    Node<T> *current_node = head_ptr;
    std::cout << "List : ";
    if (is_empty ())
      {
        std::cerr << "Empty List" << '\n';
        return;
      }

    while (true)
      {
        std::cout << current_node->data << '\t';
        current_node = current_node->next_node;
        if (current_node == head_ptr)
          {
            break;
          }
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  LinkedList<int> s;
  s.insert_node (10);
  s.insert_node (20);
  s.insert_node (30);
  s.insert_node (40);

  s.print ();

  s.delete_node ();
  s.print ();

  s.delete_node ();
  s.delete_node ();
  s.print ();

  return 0;
}
