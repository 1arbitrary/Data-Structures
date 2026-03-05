#include <iostream>
#include <stdexcept>

template <typename T> struct Queue
{
  static constexpr int MAX_SIZE = 101;
  T elements[MAX_SIZE];
  int front = -1;
  int rear = -1;

  Queue () = default;

  Queue (const Queue &) = delete;
  Queue &operator= (const Queue &) = delete;

  bool
  is_full () const
  {
    return rear == (MAX_SIZE - 1);
  }

  bool
  is_empty () const
  {
    return front > rear || front == -1;
  }

  void
  enqueue (T data)
  {
    if (is_full ())
      {
        throw std::out_of_range ("Attempt To Enqueue On A Filled List !");
      }

    elements[++rear] = data;
    if (front == -1)
      {
        front++;
      }
  }

  void reset() { front = -1; rear = -1;}

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty List !");
      }
    return elements[front++];
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Non-Existent Front !");
      }
    return elements[front];
  }

  void
  print () const
  {
    std::cout << "Queue : ";
    if (is_empty ())
      {
        std::cerr << "Empty Queue" << '\n';
        return;
      }

    int i = front;
    while (i <= rear)
      {
        std::cout << elements[i++] << '\t';
      }
    std::cout << '\n';
  }
};

int
main (void)
{
  return 0;
}
