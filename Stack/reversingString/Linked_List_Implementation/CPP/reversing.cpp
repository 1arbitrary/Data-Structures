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
  std::size_t size_{ 0 };

  LinkedList () = default;
  ~LinkedList () { free_allocated_memory (); }

  LinkedList (const LinkedList &) = delete;
  LinkedList &operator= (const LinkedList &) = delete;

  void
  free_allocated_memory ()
  {
    while (head_ptr != nullptr)
      {
        Node<T> *temp_node = head_ptr;
        head_ptr = head_ptr->next_node;
        delete temp_node;
      }
  }

  bool
  is_empty () const
  {
    return head_ptr == nullptr;
  }

  void
  Push (T data)
  {
    Node<T> *new_node = new Node<T>(data);
    new_node->next_node = head_ptr;
    head_ptr = new_node;
    ++size_;
  }

  T
  Pop ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Head is empty, deleting aborted");
      }

    Node<T> *temp_node = head_ptr;
    T return_data = temp_node->data;

    head_ptr = head_ptr->next_node;
    --size_;
    delete temp_node;

    return return_data;
  }

  T
  peek () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dereference Empty List");
      }
    else
      {
        return head_ptr->data;
      }
  }

  void
  reverse ()
  {
    std::string result{};
    result.reserve (size_);

    while (!is_empty ())
      {
        result += Pop ();
      }

    std::size_t i{ 0 };
    while (i < result.length ())
      {
        Push (result[i++]);
      }
  }

  void
  print () const
  {
    Node<T> *current_node = head_ptr;
    std::cout << "List : ";
    while (current_node != nullptr)
      {
        std::cout << current_node->data << "\t";
        current_node = current_node->next_node;
      }
    std::cout << "\n";
  }
};

int
main (void)
{
  LinkedList<char> list;
  list.Push ('H');
  list.Push ('E');
  list.Push ('L');
  list.Push ('L');
  list.Push ('O');
  list.print ();

  list.reverse ();
  list.print ();
  return 0;
}
