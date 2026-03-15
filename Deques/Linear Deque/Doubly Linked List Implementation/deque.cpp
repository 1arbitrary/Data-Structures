#include <iostream>
#include <stdexcept>

template <typename T> struct Node
{
  T data;
  Node<T> *next_node;
  Node<T> *prev_node;
  Node (T d) : data (d), next_node (nullptr), prev_node (nullptr) {}
};

template <typename T> struct Deque
{
  Node<T> *front_node = nullptr;
  Node<T> *rear_node = nullptr;

  Deque () = default;
  ~Deque ()
  {
    free_allocated_memory ();
  }

  Deque (const Deque &) = delete;
  Deque &operator= (const Deque &) = delete;

  void
  free_allocated_memory ()
  {
    while (front_node != nullptr)
      {
        Node<T> *temp_node = front_node;
        front_node = front_node->next_node;
        delete temp_node;
      }
  }

  bool
  is_empty () const
  {
    return front_node == nullptr;
  }

  void
  enqueue (T data)
  {
    Node<T> *new_node = new Node<T> (data);
    if (front_node == nullptr)
      {
        front_node = new_node;
        rear_node = front_node;
        return;
      }
    rear_node->next_node = new_node;
    new_node->prev_node = rear_node;
    rear_node = new_node;
  }

  void
  insert_front (T data)
  {
    Node<T> *new_node = new Node<T> (data);
    new_node->next_node = front_node;
    if (is_empty ())
      {
        front_node = new_node;
        rear_node = front_node;
        return;
      }

    front_node->prev_node = new_node;
    front_node = new_node;
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Deque !");
      }

    Node<T> *temp_node = nullptr;
    if (front_node->next_node == nullptr)
      {
        temp_node = front_node;
        T deleted_element = front_node->data;
        front_node = nullptr;
        rear_node = nullptr;
        delete temp_node;
        return deleted_element;
      }
    temp_node = front_node;
    T deleted_element = front_node->data;
    front_node = front_node->next_node;
    front_node->prev_node = nullptr;
    delete temp_node;
    return deleted_element;
  }

  T
  delete_rear ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Delete Empty Rear Position !");
      }

    Node<T> *temp_node = rear_node;
    T deleted_element = rear_node->data;
    if (front_node == rear_node)
      {
	front_node = nullptr;
        rear_node = nullptr;
        delete temp_node;
	return deleted_element;
      }
    rear_node = rear_node->prev_node;
    rear_node->next_node = nullptr;
    delete temp_node;
    return deleted_element;
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Front Position !");
      }
    return front_node->data;
  }

  T
  get_rear () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Rear Position !");
      }
    return rear_node->data;
  }

  void
  print () const
  {
    Node<T> *current_node = front_node;
    std::cout << "Deque : ";
    if (current_node == nullptr)
      {
        std::cerr << "Empty Deque !" << '\n';
        return;
      }

    while (current_node != nullptr)
      {
        std::cout << current_node->data << '\t';
        current_node = current_node->next_node;
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  Deque<int> d;

  d.enqueue (10);
  d.enqueue (20);
  d.print ();
  d.insert_front (30);
  d.insert_front (40);
  d.print ();

  std::cout << "Deleted : " << d.delete_rear () << '\n';
  std::cout << "Deleted : " << d.delete_rear () << '\n';

  d.enqueue (80);
  d.enqueue (90);

  std::cout << "Deleted : " << d.dequeue () << '\n';
  std::cout << "Deleted : " << d.dequeue () << '\n';
  d.print ();
  return 0;
}
