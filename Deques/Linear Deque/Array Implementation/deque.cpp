#include <iostream>
#include <stdexcept>

template <typename T> struct Deque
{
  static constexpr int MAX_SIZE = 10;
  T elements[MAX_SIZE];
  int front = 0;
  int rear = -1;

  Deque () = default;
  Deque (const Deque &) = delete;
  Deque &operator= (const Deque &) = delete;

  bool
  is_full () const
  {
    return rear == MAX_SIZE - 1;
  }

  bool
  is_empty () const
  {
    return front > rear;
  }

  void
  enqueue (T data)
  {
    if (is_full ())
      {
        throw std::out_of_range ("Attempt To Enqueue On A Filled Deque");
      }
    elements[++rear] = data;
  }

  void
  insert_front (T data)
  {
    if (is_empty ())
      {
        elements[front] = data;
        rear++;
      }
    else if (front >= 1)
      {
        elements[--front] = data;
      }
    else
      {
        throw std::out_of_range ("Invalid Index Reached for Insertion ");
      }
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Deque !");
      }

    return elements[front++];
  }

  T
  delete_rear ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Delete On Empty Rear Position !");
      }
    return elements[rear--];
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Front Position !");
      }
    return elements[front];
  }

  T
  get_rear () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Rear Position !");
      }
    return elements[rear];
  }

  void
  print () const
  {
    std::cout << "Deque : ";
    if (is_empty ())
      {
        std::cerr << "Empty Deque !" << '\n';
      }
    int i{ front };
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
  Deque<int> d;
  d.enqueue (10);
  d.enqueue (20);
  d.enqueue (30);
  d.enqueue (40);
  d.dequeue ();
  d.insert_front (50);
  d.delete_rear ();
  d.enqueue (60);
  d.print ();
  return 0;
}
