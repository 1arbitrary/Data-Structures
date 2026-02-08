#include <iostream>

template <typename T> struct Node
{
  T data;
  Node<T>* next_node;
  Node (T d) : data (d), next_node (nullptr) {}
};

template <typename T> class LinkedList
{
private:
  Node<T>* head_ptr = nullptr;
  void
  free_allocated_memory ()
  {
    Node<T>* temp_node = nullptr;
    while (head_ptr != nullptr)
      {
        temp_node = head_ptr;
        head_ptr = head_ptr->next_node;
        delete temp_node;
      }
  }

  bool
  isEmpty () const
  {
    return head_ptr == nullptr;
  }

  Node<T>*
  check_position (std::size_t desired_position) const
  {
    if (desired_position == 0)
      return nullptr;

    Node<T>* current_node = head_ptr;
    if (desired_position == 1)
      return current_node;

    if (desired_position > 1)
      {
        std::size_t i{ 1 };
        while (i < (desired_position - 1) && current_node != nullptr)
          {
            i++;
            current_node = current_node->next_node;
          }
      }
    return (current_node != nullptr) ? current_node : nullptr;
  }

  void
  reverse_list (Node<T>* current_node)
  {
    if (current_node != nullptr)
      {
        reverse_list (current_node->next_node);
        if (current_node->next_node == nullptr)
          {
            head_ptr = current_node;
            return;
          }
        Node<T>* prev_node = current_node->next_node;
        /* make sure to break the old links first so that
         the next_node doesn't point to 2 locations.*/
        current_node->next_node = nullptr;
        prev_node->next_node = current_node;
        prev_node = current_node;
      }
  }

public:
  LinkedList () = default;
  ~LinkedList () { free_allocated_memory (); }

  LinkedList (const LinkedList&) = delete;
  LinkedList& operator= (const LinkedList&) = delete;

  void
  add_node (T data)
  {
    Node<T>* new_node = new Node<T> (data);
    new_node->next_node = head_ptr;
    head_ptr = new_node;
  }

  void
  insert_at_position (T data, std::size_t insert_position)
  {
    Node<T>* prev_node = check_position (insert_position);
    if (prev_node == nullptr && insert_position != 1)
      {
        std::cerr << "The Position " << insert_position
                  << " you were trying to insert on doesn't exist" << "\n";
        return;
      }

    Node<T>* new_node = new Node<T> (data);
    if (!isEmpty () && insert_position != 1)
      {
        if (insert_position > 1)
          {
            new_node->next_node = prev_node->next_node;
            prev_node->next_node = new_node;
          }
      }
    else if (insert_position == 1)
      {
        new_node->next_node = head_ptr;
        head_ptr = new_node;
      }
  }

  void
  delete_node ()
  {
    if (!isEmpty ())
      {
        std::cout << "Deleting Node : " << head_ptr->data << "\n";
        Node<T>* temp_node = head_ptr;
        head_ptr = head_ptr->next_node;
        delete temp_node;
      }
    else
      {
        std::cerr << "List is empty, Nothing to delete !" << "\n";
      }
  }

  void
  delete_at_position (std::size_t delete_position)
  {
    if (!isEmpty ())
      {
        Node<T>* prev_node = check_position (delete_position);
        if ((prev_node == nullptr || prev_node->next_node == nullptr)
            && delete_position != 1)
          {
            std::cerr << "Position " << delete_position << " doesn't exist"
                      << "\n";
            return;
          }

        Node<T>* temp_node = nullptr;
        if (delete_position == 1 && prev_node != nullptr)
          {
            temp_node = head_ptr;
            head_ptr = head_ptr->next_node;
            delete temp_node;
          }

        if (delete_position > 1 && prev_node)
          {
            temp_node = prev_node->next_node;
            prev_node->next_node = prev_node->next_node->next_node;
            delete temp_node;
          }
      }
    else
      {
        std::cerr << "Empty List ! Nothing to Delete at " << delete_position
                  << "\n";
      }
  }

  void
  reverse ()
  {
    Node<T>* current_node = head_ptr;
    reverse_list (current_node);
  }

  void
  print () const
  {
    Node<T>* current_node = head_ptr;
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
  LinkedList<int> list;
  list.add_node (22);
  list.add_node (23);
  list.insert_at_position (54, 1);
  list.insert_at_position (234, 2);
  list.insert_at_position (234, 5);
  list.reverse ();
  list.print ();
  return 0;
}
