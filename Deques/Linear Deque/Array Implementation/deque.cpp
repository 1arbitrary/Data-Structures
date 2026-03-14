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
  is_empty () const
  {
    return front > rear;
  }

  void
  enqueue (T data)
  {
    if (rear == (MAX_SIZE - 1))
      {
        throw std::out_of_range ("Attempt To Enqueue On A Filled Deque !");
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
        return;
      }

    if (front >= 1)
      {
        elements[--front] = data;
      }
    else
      {
        throw std::out_of_range ("Attempt To Insert At Invalid Front Index");
      }
  }

  T
  delete_rear ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Delete Empty Rear Position In Deque !");
      }
    return elements[rear--];
  }

  T
  dequeue ()
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Dequeue On An Empty Dequeue !");
      }
    return elements[front++];
  }

  T
  get_front () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Empty Front Element !");
      }
    return elements[front];
  }

  T
  get_rear () const
  {
    if (is_empty ())
      {
        throw std::out_of_range ("Attempt To Access Invalid Rear Element !");
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
        return;
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
  d.print ();

  std::cout << "\nFront: " << d.get_front () << '\n';
  std::cout << "Rear : " << d.get_rear () << '\n';

  std::cout << "Removed: " << d.dequeue () << '\n';
  d.print ();

  d.insert_front (5);
  d.print ();

  std::cout << "Removed: " << d.delete_rear () << '\n';
  d.print ();

  std::cout << d.dequeue () << '\n';
  std::cout << d.dequeue () << '\n';
  std::cout << d.dequeue () << '\n';

  d.print ();

  d.enqueue (99);
  d.print ();

  std::cout << "Front: " << d.get_front () << '\n';
  std::cout << "Rear : " << d.get_rear () << '\n';

  return 0;
}
