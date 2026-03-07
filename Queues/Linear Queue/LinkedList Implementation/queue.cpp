#include <iostream>
#include <stdexcept>

template <typename T> struct Node
{
  T data;
  Node<T> *next_node;
  Node (T d) : data (d), next_node (nullptr) {}
};

template <typename T> struct Queue
{
  Node<T> *front = nullptr;
  Node<T> *rear = nullptr;

  Queue () = default;
  ~Queue ()
  {
    free_allocated_memory ();
  }

  Queue (const Queue &) = delete;
  Queue &operator= (const Queue &) = delete;

  void
  free_allocated_memory ()
  {
    while (front != nullptr)
      {
        Node<T> *temp_node = front;
        front = front->next_node;
        delete temp_node;
      }
  }

  bool
  is_empty () const
  {
    return front == nullptr;
  }

  void
  enqueue (T data)
  {
    Node<T> *new_node = new Node<T> (data);
    if (is_empty ())
      {
        front = new_node;
        rear = new_node;
        return;
      }
    rear->next_node = new_node;
    rear = new_node;
  }

  void
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Queue");
      }

    Node<T> *temp_node = front;
    front = front->next_node;
    delete temp_node;
    
    if (is_empty ())
      {
        rear = nullptr;
      }
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Front !");
      }
    return front->data;
  }

  void
  print () const
  {
    Node<T> *current_node = front;

    std::cout << "Queue : ";
    if (is_empty ())
      {
        std::cerr << "Empty Queue !" << '\n';
        return;
      }

    while (current_node != nullptr)
      {
        std::cout << current_node->data << '\t';
        current_node = current_node->next_node;
      }
    std::cout << "\n";
  }
};

int
main (void)
{
  Queue<int> q;

  q.enqueue (10);
  q.enqueue (20);
  q.enqueue (30);

  q.print ();

  std::cout << "Front: " << q.get_front () << '\n';

  q.dequeue ();
  q.print ();

  q.dequeue ();
  std::cout << "Front after dequeue: " << q.get_front () << '\n';

  q.enqueue (40);
  q.enqueue (50);
  q.print ();

  q.dequeue ();
  q.dequeue ();
  q.dequeue ();

  q.print ();
  return 0;
}
