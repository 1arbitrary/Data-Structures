#include <iostream>
#include <stdexcept>

template <typename T> struct Queue
{
  static constexpr std::size_t MAX_SIZE = 10;
  T elements[MAX_SIZE];
  int front = 0;
  int rear = -1;
  std::size_t occupied_indexes = 0;

  Queue () = default;

  Queue (const Queue &) = delete;
  Queue &operator= (const Queue &) = delete;

  bool
  is_full () const
  {
    return occupied_indexes == MAX_SIZE;
  }

  bool
  is_empty () const
  {
    return occupied_indexes == 0;
  }

  void
  enqueue (T data)
  {
    if (is_full ())
      {
        throw std::out_of_range ("Attempt To Enqueue On A Full Queue !");
      }
    rear = (rear + 1) % MAX_SIZE;
    elements[rear] = data;
    occupied_indexes++;
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Queue !");
      }

    T deleted_element = elements[front];
    front = (front + 1) % MAX_SIZE;
    occupied_indexes--;

    return deleted_element;
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access An Empty Front !");
      }

    return elements[front];
  }

  void
  print ()
  {
    std::cout << "Queue : ";
    if (is_empty ())
      {
        std::cerr << "Empty Queue !";
        return;
      }

    std::size_t i{ front };
    std::size_t elements_left_to_print{ occupied_indexes };

    while (elements_left_to_print != 0)
      {
        std::cout << elements[i] << '\t';
        elements_left_to_print--;
        i = (i + 1) % MAX_SIZE;
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
