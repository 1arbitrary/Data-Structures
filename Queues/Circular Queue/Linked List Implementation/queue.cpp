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
    if (is_empty ())
      {
        return;
      }

    rear->next_node = nullptr;
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
      }
    if (rear != nullptr)
      {
        rear->next_node = new_node;
      }
    rear = new_node;
    rear->next_node = front;
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Queue !");
      }

    Node<T> *temp_node = nullptr;
    T deleted_data{};
    if (front == rear)
      {
        temp_node = front;
        front = nullptr;
        rear = nullptr;
        deleted_data = temp_node->data;
        delete temp_node;
        return deleted_data;
      }
    else
      {
        temp_node = front;
        front = front->next_node;
        rear->next_node = front;
        deleted_data = temp_node->data;
        delete temp_node;
        return deleted_data;
      }
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Front Of The Queue !");
      }
    return front->data;
  }

  void
  print () const
  {
    std::cout << "Queue : ";
    if (is_empty ())
      {
        std::cerr << "Empty Queue !";
        return;
      }

    Node<T> *current_node = front;
    while (true)
      {
        std::cout << current_node->data << '\t';
        current_node = current_node->next_node;
        if (current_node == front)
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
  Queue<int> q;
  q.enqueue (10);
  q.enqueue (20);
  q.enqueue (30);
  q.enqueue (40);
  std::cout << "Deleted : " << q.dequeue () << '\n';
  std::cout << "Deleted : " << q.dequeue () << '\n';
  q.enqueue (50);
  q.enqueue (60);
  q.enqueue (70);
  q.enqueue (80);
  q.enqueue (90);
  q.dequeue ();
  q.enqueue (100);
  q.enqueue (110);
  q.enqueue (120);
  q.enqueue (140);
  q.print ();
  return 0;
}
